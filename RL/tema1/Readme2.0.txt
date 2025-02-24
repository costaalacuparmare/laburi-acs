Here's a completed README based on the provided source code and tasks. The content is structured to explain the context, tasks, and the functions in the code:

---

# Local Networks - 1st Homework

### Constantinescu Vlad 333CB

### Overview

This project implements a basic networking switch in Python that supports **forwarding and learning**, **VLAN integration**, and **Spanning Tree Protocol (STP)**. The switch operates over Ethernet frames, processes VLAN tags, and utilizes the BPDU (Bridge Protocol Data Units) to determine the root bridge and prevent loops in the network.

The primary tasks implemented in this project are:

1. **Forwarding and Learning Switch**: The switch forwards Ethernet frames based on a learned MAC address table. It updates its MAC address table dynamically based on incoming frames.
2. **VLAN Integration**: The switch supports 802.1Q VLAN tags, allowing it to process traffic for multiple VLANs. The switch can distinguish between trunk and access ports and adds or removes VLAN tags accordingly.
3. **Spanning Tree Protocol (STP) Integration**: The switch implements STP to prevent loops in the network by dynamically adjusting port states based on BPDUs. The switch will choose a root bridge and block redundant paths.

---

### Functions

- **`parse_ethernet_header`**:
  Parses the Ethernet frame header to extract:
  - Destination MAC address
  - Source MAC address
  - EtherType (type of the Ethernet frame)
  - VLAN ID (if present)

- **`create_vlan_tag`**:
  Creates a VLAN tag (802.1Q) for a given VLAN ID.
  - Adds the priority (set to default)
  - Adds the CFI (Canonical Format Indicator)
  - Adds the VLAN ID (12 bits)

- **`create_bpdu`**:
  Creates a BPDU packet. This packet includes fields such as the root bridge ID, the root path cost, and the bridge ID. It is used in the Spanning Tree Protocol to advertise and discover the root bridge and prevent loops in the network.

- **`send_bpdu_every_second`**:
  Sends a BPDU packet every second on trunk interfaces if the switch is the root bridge. It checks if the switch is the root and sends the BPDU accordingly to maintain the tree structure in the network.

- **`is_unicast`**:
  Checks if a given MAC address is a unicast address (even first byte indicates unicast).

- **`is_bpdu`**:
  Checks if the incoming frame is a BPDU (used for STP).

- **`get_interface_type`**:
  Returns the type of interface (either trunk or access), determining how VLANs are handled on that interface.

- **`forward_frame`**:
  Forwards a frame from one interface to another. If the interface is a trunk, it adds a VLAN tag. It also checks the interface state (blocking or listening) and forwards the frame only if the state allows it.

---

### Tasks and Implementation Details

#### Task 1: Forwarding and Learning Switch
The forwarding and learning functionality is handled by the MAC address table (`mac_table`), which maps MAC addresses to their respective interfaces. Upon receiving a frame, the switch extracts the destination MAC address and checks if it exists in the table. If it does, the frame is forwarded to the corresponding interface. If it doesn't, the switch will broadcast the frame on all interfaces (except the incoming interface) to learn the destination MAC.

#### Task 2: VLAN Integration
The switch supports VLANs by tagging frames with VLAN identifiers using the IEEE 802.1Q standard. The code differentiates between trunk and access ports:

- **Access ports**: Only accept frames that match the configured VLAN.
- **Trunk ports**: Allow frames from multiple VLANs and include a VLAN tag in the Ethernet frame.

When the switch receives a frame on a trunk port with a VLAN tag, it removes the tag before processing the frame. If the frame lacks a VLAN tag, it is assumed to belong to the VLAN associated with the interface.

The VLAN table (`vlan_table`) maps each interface to its VLAN configuration, where `"T"` indicates a trunk port and integer values represent access VLAN IDs.

#### Task 3: Spanning Tree Protocol (STP) Integration
STP is implemented to prevent network loops by dynamically adjusting port states. The switch generates BPDUs that contain information about the root bridge, path costs, and bridge IDs. The BPDUs are sent every second from the root bridge (or potential root bridges) to advertise the network topology.

When the switch receives a BPDU, it compares the root bridge ID with its own and updates the topology information. If a better (lower) root bridge ID is found, the switch updates its root path cost and may change the state of certain ports to "blocking" or "listening" to prevent loops.

The `in_states` dictionary tracks the state of each interface (either "blocking" or "listening").

---

### Example Configuration

The switch configuration file (e.g., `switch1.cfg`) contains the switch ID, root bridge ID, and the VLAN configuration for each interface. An example configuration might look like this:

```
1
T 1
10 2
```

- `1` - The switch ID (used to load the correct configuration).
- `T 1` - Port 1 is a trunk port.
- `10 2` - Port 2 is an access port for VLAN 10.

---

### Running the Code

To run the program, use the following command:

```bash
python3 switch.py <switch_id> <interfaces>
```

- `<switch_id>`: The ID of the switch (e.g., `1`, `2`, etc.).
- `<interfaces>`: A list of interfaces (e.g., `eth0`, `eth1`, etc.).

---

### Dependencies

- Python 3.x
- `struct` module (standard Python library)
- `time` module (standard Python library)
- `threading` module (standard Python library)

Make sure to install the required dependencies by setting up the Python environment.

---

### Conclusion

This project demonstrates a basic software switch with VLAN and STP support. It provides a foundational understanding of Ethernet networking, VLAN tagging, and loop prevention mechanisms. The switch can forward frames, dynamically learn MAC addresses, and maintain a loop-free network topology using Spanning Tree Protocol.

---

This README provides a comprehensive overview of the implementation, detailing the functionality of each part of the code and its interaction with the tasks specified.