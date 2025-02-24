#!/usr/bin/python3
import sys
import struct
import wrapper
import threading
import time
from wrapper import (recv_from_any_link, send_to_link, get_switch_mac,
                     get_interface_name)

# used for bpdu sturcture
from dataclasses import dataclass

# global variables
mac_table = {}
vlan_table = {}
interfaces = {}

# interface states
in_states = {}


# BPDU structure - kept only the necessary fields
@dataclass
class BPDU:
    root_bridge_id: int
    root_path_cost: int
    bridge_id: int
    root_id: int = -1
    is_root_bridge: bool = False


# parse the Ethernet header
def parse_ethernet_header(data):
    # unpack the header fields from the byte array
    # dest_mac, src_mac, ethertype = struct.unpack('!6s6sH', data[:14])
    dest_mac = data[0:6]
    src_mac = data[6:12]

    # extract ethertype. Under 802.1Q, this may be the bytes from the VLAN TAG
    ether_type = (data[12] << 8) + data[13]

    vlan_id = -1
    # check for VLAN tag (0x8100 in network byte order is b'\x81\x00')
    if ether_type == 0x8200:
        vlan_tci = int.from_bytes(data[14:16], byteorder='big')
        vlan_id = vlan_tci & 0x0FFF  # extract the 12-bit VLAN ID
        ether_type = (data[16] << 8) + data[17]

    return dest_mac, src_mac, ether_type, vlan_id


# create a VLAN tag
def create_vlan_tag(vlan_id):
    # 0x8100 for the Ethertype for 802.1Q
    # vlan_id & 0x0FFF ensures that only the last 12 bits are used
    return struct.pack('!H', 0x8200) + struct.pack('!H',
                                                   vlan_id & 0x0FFF)


# Create a BPDU
def create_bpdu():
    # uses struct to pack the BPDU fields into a byte array, same as with
    # ethernet headers destination_mac = network byte order, 6 bytes (char),
    # source_mac = 6 bytes (char), root_bridge_id = 4 bytes (int),
    # root_path_cost = 4 bytes (int), bridge_id = 4 bytes (int)
    bpdu_format = "!6s6siii"
    dest_mac = b"\x01\x80\xc2\x00\x00\x00"
    return struct.pack(bpdu_format, dest_mac, get_switch_mac(),
                       BPDU.root_bridge_id, BPDU.root_path_cost,
                       BPDU.bridge_id)


# send BPDU every second
# if switch is root bridge, send BPDU on trunk interfaces
def send_bpdu_every_sec():
    while True:
        if BPDU.is_root_bridge:
            bpdu_packet = create_bpdu()
            for i in interfaces:
                if vlan_table[get_interface_name(i)] == "T":
                    send_to_link(i, len(bpdu_packet), bpdu_packet)
        time.sleep(1)


# check if MAC is unicast to determine if frame is broadcast or unicast
def is_unicast(mac):
    first_byte = int(mac.split(":")[0], 16)
    return first_byte % 2 == 0


# check if MAC is the BPDU MAC
def is_bpdu(mac):
    if mac == "01:80:c2:00:00:00":
        return True
    return False


# get the interface type (trunk or access)
def get_interface_type(interface_name):
    if vlan_table[interface_name] == "T":
        return "trunk"
    return "access"


# used for MAC table and VLAN packet forwarding
def forward_frame(interface, data, length, vlan_id):
    # if interface is trunk, add VLAN tag to packet
    if get_interface_type(get_interface_name(interface)) == "trunk":
        data = data[0:12] + create_vlan_tag(vlan_id) + data[12:]
        length += 4
    in_name = get_interface_name(interface)
    if in_states[in_name] != "blocking":
        # if interface is access and is not blocked because of STP,
        # check if packet has VLAN tag
        if vlan_table[in_name] == vlan_id or vlan_table[in_name] == "T":
            send_to_link(interface, length, data)


def main():
    global interfaces
    switch_id = sys.argv[1]

    # initialize the switch
    num_interfaces = wrapper.init(sys.argv[2:])
    interfaces = range(0, num_interfaces)

    # read the switch configuration file
    fin = open("./configs/switch{}.cfg".format(switch_id), "r")
    file_lines = fin.readlines()
    fin.close()

    # sets switch initially as root bridge
    BPDU.bridge_id = int(file_lines[0])
    BPDU.root_bridge_id = BPDU.bridge_id
    BPDU.root_path_cost = 0
    BPDU.is_root_bridge = True
    file_lines.pop(0)

    # parse the switch configuration file
    for line in file_lines:
        line = line.split()
        # add numbers as integers, leave "T" as string
        line_id = int(line[1]) if line[1] != "T" else line[1]
        vlan_table[line[0]] = line_id

    # create and start a new thread that deals with sending BDPU
    t = threading.Thread(target=send_bpdu_every_sec)
    t.start()

    # initialize the interface states
    # set all trunk interfaces to blocking state
    for i in interfaces:
        if vlan_table[get_interface_name(i)] == "T":
            in_states[get_interface_name(i)] = "blocking"
        else:
            in_states[get_interface_name(i)] = "listening"

    # Send Hello BPDU
    bpdu_packet = create_bpdu()
    for i in interfaces:
        send_to_link(i, len(bpdu_packet), bpdu_packet)

    while True:
        interface, data, length = recv_from_any_link()

        dest_mac, src_mac, ethertype, vlan_id = parse_ethernet_header(data)

        # print the MAC src and MAC dst in human-readable format
        dest_mac = ':'.join(f'{b:02x}' for b in dest_mac)
        src_mac = ':'.join(f'{b:02x}' for b in src_mac)

        in_name = get_interface_name(interface)
        # if VLAN ID is not set, set it to the VLAN ID of the interface
        if vlan_id == -1 and get_interface_type(in_name) == "access":
            vlan_id = vlan_table[in_name]
        # if interface is trunk and packet has VLAN tag, remove it
        elif get_interface_type(in_name) == "trunk" and not is_bpdu(dest_mac):
            data = data[0:12] + data[16:]
            length -= 4

        # update MAC table
        mac_table[src_mac] = interface

        # check if the destination MAC is in the MAC table
        if is_unicast(dest_mac) and dest_mac in mac_table:
            forward_frame(mac_table[dest_mac], data, length, vlan_id)
        # check for STP BPDU
        elif is_bpdu(dest_mac):
            # parse the BPDU
            bpdu_format = "!6s6siii"
            (dest_mac, bpdu_src, root_bridge_id,
             sender_path_cost, sender_bridge_id) = struct.unpack(bpdu_format,
                                                                 data[0:24])
            # if the root bridge id is smaller than the current root bridge id
            # update the root bridge id and path cost
            if root_bridge_id < BPDU.root_bridge_id:
                BPDU.root_bridge_id = root_bridge_id
                BPDU.root_path_cost = sender_path_cost + 10
                BPDU.root_id = interface

                # if the switch is root bridge, update the interface states
                if BPDU.is_root_bridge:
                    BPDU.is_root_bridge = False

                    for i in interfaces:
                        if i == interface:
                            in_states[get_interface_name(i)] = "listening"
                        elif vlan_table[get_interface_name(i)] == "T":
                            in_states[get_interface_name(i)] = "blocking"

                # Send Hello BPDU
                bpdu_packet = create_bpdu()
                for i in interfaces:
                    send_to_link(i, len(bpdu_packet), bpdu_packet)

            # if the root bridge id is the same as the current root bridge id
            # and the path cost is smaller than the current path cost, update
            # the path cost and the root id
            elif BPDU.root_bridge_id == root_bridge_id:
                if (interface == BPDU.root_id and
                        BPDU.root_path_cost > sender_path_cost + 10):
                    BPDU.root_path_cost = sender_path_cost + 10
                elif (interface != BPDU.root_id and
                      BPDU.root_path_cost < sender_path_cost):
                    if in_states[get_interface_name(interface)] == "blocking":
                        in_states[get_interface_name(interface)] = "listening"
            # if the packet is not from the root bridge, update the interface
            elif sender_bridge_id == BPDU.bridge_id:
                in_states[get_interface_name(interface)] = "blocking"
            # if the packet is from the root bridge,
            # update the interface states
            if BPDU.bridge_id == root_bridge_id:
                for i in interfaces:
                    in_states[get_interface_name(i)] = "listening"
        else:
            # flood & broadcast for uni/broadcast frames
            for i in interfaces:
                if i != interface:
                    forward_frame(i, data, length, vlan_id)


if __name__ == "__main__":
    main()
