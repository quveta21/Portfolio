import socket
import struct

# NOTE: 0x0003 = ETH_P_ALL
# network -> BIG-ENDIAN     computer -> LITTLE-ENDIAN
# ntohs safely reformats the 16-bit numeric representation of 0x0003 to match my local computer's processor layout
sniffer = socket.socket(socket.AF_PACKET, socket.SOCK_RAW, socket.ntohs(0x0003))

sniffer.bind(("eth0", 0))

try:
    while True:
        packet, address = sniffer.recvfrom(65565)

        # Primii 14 bytes: Ethernet Header (MAC addresses + EtherType)
        eth_header = packet[:14]

        mac_dest, mac_src, ether_type = struct.unpack("!6s6sH", eth_header)

        # IPv4
        if ether_type != 0x0800:
            continue

        ip_header = packet[14:34]

        version_ihl, tos, length, identification, flags_fragment, \
            ttl, protocol, checksum, src, dest = struct.unpack("!BBHHHBBH4s4s", ip_header)

        # Protocol 6 = TCP
        if protocol != 6:
            continue

        src_ip = socket.inet_ntoa(src)
        dest_ip = socket.inet_ntoa(dest)

        # Extracting the IHL (last 4 bits)
        ihl = version_ihl & 0xF
        tcp_offset = 14 + ihl * 4
        tcp_data = packet[tcp_offset:]

        src_port, dest_port = struct.unpack_from("!HH", tcp_data)

        print("TCP packet caught!")
        print(f"Source -> {src_ip}:{src_port}")
        print(f"Destination -> {dest_ip}:{dest_port}")
        print(f"TTL: {ttl}\n")
except KeyboardInterrupt:
    print("Sniffer stopped...")
finally:
    sniffer.close()
