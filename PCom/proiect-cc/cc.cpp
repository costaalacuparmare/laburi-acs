// -*- c-basic-offset: 4; indent-tabs-mode: nil -*- 
#include <math.h>
#include <iostream>
#include <algorithm>
#include "cc.h"
#include "queue.h"
#include <stdio.h>
#include "switch.h"
#include "ecn.h"
using namespace std;

// LOSS PACKAGES LIMIT
#define RETX_RESET_THRESHOLD 3

int CCSrc::_global_node_count = 0;

CCSrc::CCSrc(EventList &eventlist)
    : EventSource(eventlist,"cc"), _flow(NULL)
{
    _mss = Packet::data_packet_size();
    _acks_received = 0;
    _nacks_received = 0;

    _highest_sent = 0;
    _next_decision = 0;
    _flow_started = false;
    _sink = 0;

    _node_num = _global_node_count++;
    _nodename = "CCsrc " + to_string(_node_num);

    _cwnd = 27\\ * _mss;
    _ssthresh = 0xFFFFFFFFFF;
    _flightsize = 0;
    _flow._name = _nodename;
    setName(_nodename);

    // Swift init
    ai = 120;  // aditive increase
    retransmit_cnt = 0;  // package retransmit counter
    target_delay = 2;  // target delay for the flow
    t_last_decrease = eventlist.now();  // last time when the congestion window was decreased
    max_mdf = 0.005;  // maximum multiplicative decrease factor
    base_target = 4;  // base target delay
    fs_min_cwnd = _mss; // minimum congestion window
    fs_max_cwnd = 1000 * _mss; // maximum congestion window
    can_dec = false;  // can decrease congestion window
}

/* Start the flow */
void CCSrc::startflow(){
    cout << "Start flow " << _flow._name << " at " << timeAsSec(eventlist().now()) << "s" << endl;
    _flow_started = true;
    _highest_sent = 0;
    _packets_sent = 0;

    while (_flightsize + _mss < _cwnd)
        send_packet();
}

/* Init connection */
void CCSrc::connect(Route* routeout, Route* routeback, CCSink& sink, simtime_picosec starttime) {
    assert(routeout);
    _route = routeout;

    _sink = &sink;
    _flow._name = _name;
    _sink->connect(*this, routeback);

    eventlist().sourceIsPending(*this,starttime);
}

// Calculates the target delay for the flow
double CCSrc::targetDelay() {
    return (base_target + max(0.0, min((alpha / sqrt(_cwnd)) + beta, fs_range)));
}

// Process a NACK
void CCSrc::processNack(const CCNack& nack){
    _nacks_received ++;
    _flightsize -= _mss;

    retransmit_cnt++;
    double rtt = timeAsMs(eventlist().now() - nack.ts());
    can_dec = ((eventlist().now() - t_last_decrease) / 1e9) >= rtt;
    if (retransmit_cnt >= RETX_RESET_THRESHOLD) {
        _cwnd = fs_min_cwnd;
    } else if (can_dec) {
        _cwnd = (1 - max_mdf) * _cwnd;
    }
}

/* Process an ACK.  Mostly just housekeeping*/
void CCSrc::processAck(const CCAck& ack) {
    _acks_received++;
    _flightsize -= _mss;

    retransmit_cnt = 0;
    target_delay = targetDelay();
    double rtt = timeAsMs(eventlist().now() - ack.ts());
    double ts = eventlist().now();
    double delay = rtt * 0.5;
    can_dec = ((ts - t_last_decrease) / 1e9) >= rtt;

    if (delay < target_delay) {
        if (_cwnd >= 1)
            _cwnd = _cwnd + (ai / _cwnd) * _acks_received;
        else
            _cwnd = _cwnd + ai * _acks_received;
    } else if (can_dec) {
            _cwnd = max(1 - (-beta) * ((delay - target_delay) / delay), 1 - max_mdf) * _cwnd;
            t_last_decrease = ts;
    }
}


/* receive a packet */
void CCSrc::receivePacket(Packet& pkt)
{
    if (!_flow_started){
        return;
    }

    fs_range = 4 - (_cwnd / fs_max_cwnd * 2);
    alpha = fs_range / ((1 / (sqrt(fs_min_cwnd))) - (1 / (sqrt(fs_max_cwnd))));
    beta = -alpha / sqrt(fs_max_cwnd);

    switch (pkt.type()) {
    case CCNACK:
        processNack((const CCNack&)pkt);
        pkt.free();
        break;
    case CCACK:
        processAck((const CCAck&)pkt);
        pkt.free();
        break;
    default:
        cout << "Got packet with type " << pkt.type() << endl;
        abort();
    }

    _cwnd = max(fs_min_cwnd, min(fs_max_cwnd, _cwnd));

    //now send packets!
    while (_flightsize + _mss < _cwnd)
        send_packet();
}

// Note: the data sequence number is the number of Byte1 of the packet, not the last byte.
/* Send a packet */
void CCSrc::send_packet() {
    CCPacket* p = NULL;

    assert(_flow_started);

    p = CCPacket::newpkt(*_route,_flow, _highest_sent+1, _mss, eventlist().now());

    _highest_sent += _mss;
    _packets_sent++;

    _flightsize += _mss;

    p->sendOn();
}

void CCSrc::doNextEvent() {
    if (!_flow_started){
      startflow();
      return;
    }
}

/* Only use this constructor when there is only one for to this receiver */
CCSink::CCSink()
    : Logged("CCSINK"), _total_received(0)
{
    _src = 0;

    _nodename = "CCsink";
    _total_received = 0;
}

/* Connect a src to this sink. */
void CCSink::connect(CCSrc& src, Route* route)
{
    _src = &src;
    _route = route;
    setName(_src->_nodename);
}


// Receive a packet.
// seqno is the first byte of the new packet.
void CCSink::receivePacket(Packet& pkt) {
    switch (pkt.type()) {
    case CC:
        break;
    default:
        abort();
    }

    CCPacket *p = (CCPacket*)(&pkt);
    CCPacket::seq_t seqno = p->seqno();

    simtime_picosec ts = p->ts();

    if (pkt.header_only()){
        send_nack(ts,seqno);

        p->free();

        return;
    }

    _total_received += Packet::data_packet_size();;

    bool ecn = (bool)(pkt.flags() & ECN_CE);

    send_ack(ts,seqno,ecn);
    // have we seen everything yet?
    pkt.free();
}

void CCSink::send_ack(simtime_picosec ts,CCPacket::seq_t ackno,bool ecn) {
    CCAck *ack = 0;
    ack = CCAck::newpkt(_src->_flow, *_route, ackno,ts,ecn);
    ack->sendOn();
}

void CCSink::send_nack(simtime_picosec ts, CCPacket::seq_t ackno) {
    CCNack *nack = NULL;
    nack = CCNack::newpkt(_src->_flow, *_route, ackno,ts);
    nack->sendOn();
}
