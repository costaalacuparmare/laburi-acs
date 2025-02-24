1 2 3

# Local Networks - 1st Homework

### Constantinescu Vlad 333CB

### Functions
- `parse_ethernet_header`: - parses the ethernet header
    - Parses the destination MAC address
    - Parses the source MAC address
    - Parses the type of the ethernet frame
  
  
- `create_vlan_tag`: - creates the VLAN tag
    - Adds the priority to the VLAN tag
    - Adds the CFI to the VLAN tag
    - Adds the VLAN ID to the VLAN tag
    - Adds the type to the VLAN tag


- `create_bpdu`: - creates BPDU packet
    - Uses struct to pack the BPDU fields into a byte array
    - Ethernet headers destination_mac = network byte order, 6 bytes (char)
    - Source_mac = 6 bytes (char)
    - Root_bridge_id = 4 bytes (int)
    - Root_path_cost = 4 bytes (int)


- `send_bpdu_every_second`: - sends BPDU packet every second
    - Creates and sends the BPDU packet if switch is root
    - Sleeps for 1 second


- `is_unicast`: Determines if the MAC address is a unicast address.
  - Uses the first byte of the MAC address to check its unicast or multicast nature.


- `is_bpdu`: Checks if the given MAC address corresponds to a BPDU.
  - The BPDU MAC address is `01:80:c2:00:00:00`.


- `get_interface_type`: Retrieves the interface type (either "access" or "trunk") based on the VLAN configuration.
  - Returns "trunk" for trunk interfaces, "access" for access interfaces.


- `forward_frame`: Forwards a frame to the appropriate interface.
  - Adds a VLAN tag if the interface is trunk.
  - Forwards the frame based on the current interface state (e.g., blocking, listening).
  - Filters traffic based on VLAN configuration.

### Tasks and Implementation Details

1. **Forwarding and Learning Switch**:  
   - The switch forwards frames based on the MAC address table.
   - It learns MAC addresses by associating them with incoming interfaces.
   - When a frame is received, the switch checks if the destination MAC is unicast. If so, it looks up the destination in the MAC table and forwards the frame to the correct interface.
   - If the MAC address is not in the table, the switch floods the frame to all interfaces except the one it was received on.

2. **VLAN Integration**:  
   - VLANs are implemented by tagging frames on trunk interfaces and filtering frames based on the VLAN ID on access interfaces.
   - The `create_vlan_tag` function is used to insert VLAN tags into frames for trunk interfaces.
   - Frames are forwarded only if they belong to the correct VLAN for access interfaces.

3. **STP Integration**:  
   - The Spanning Tree Protocol (STP) is integrated to prevent loops in the network. The switch participates in STP by exchanging BPDUs with other switches.
   - The root bridge election process is implemented by comparing root bridge IDs and updating the root path cost.
   - If the switch becomes the root bridge, it adjusts the interface states (e.g., puts trunk interfaces into a blocking state and access interfaces into a listening state).