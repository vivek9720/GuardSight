#pragma once
#include "core/bytes.hpp"
#include "core/net.hpp"
#include "core/status.hpp"
#include "core/time.hpp"
#include <optional>
#include <string>
#include <vector>
namespace guardsight::packet {
struct EthernetFrame { std::string src_mac; std::string dst_mac; uint16_t ether_type=0; core::ByteView payload; };
struct IPv4Packet { core::IPv4Address src; core::IPv4Address dst; uint8_t protocol=0; uint8_t ttl=0; uint16_t id=0; uint16_t flags_fragment=0; core::ByteView payload; bool checksum_valid=false; };
struct TransportInfo { std::string protocol; uint16_t src_port=0; uint16_t dst_port=0; uint8_t tcp_flags=0; core::ByteView payload; };
struct DnsQuestion { std::string name; uint16_t type=0; uint16_t klass=0; };
struct DnsRecord { std::string name; uint16_t type=0; uint16_t klass=0; uint32_t ttl=0; std::string data; };
struct DnsMessage { uint16_t id=0; bool response=false; uint8_t rcode=0; std::vector<DnsQuestion> questions; std::vector<DnsRecord> answers; };
struct PacketMetadata { core::Timestamp timestamp; std::string src_mac; std::string dst_mac; std::optional<core::IPv4Address> src_ip; std::optional<core::IPv4Address> dst_ip; std::string protocol; uint16_t src_port=0; uint16_t dst_port=0; std::vector<std::string> dns_names; std::vector<std::string> notices; std::size_t wire_length=0; std::string summary() const; };
struct PcapPacket { core::Timestamp timestamp; std::vector<uint8_t> bytes; uint32_t original_length=0; };
struct PcapFile { bool nanosecond=false; uint32_t snaplen=0; uint32_t network=0; std::vector<PcapPacket> packets; };
core::Result<EthernetFrame> parse_ethernet(core::ByteView bytes); core::Result<IPv4Packet> parse_ipv4_packet(core::ByteView bytes); core::Result<TransportInfo> parse_transport(const IPv4Packet& ip); core::Result<DnsMessage> parse_dns(core::ByteView bytes); core::Result<PcapFile> parse_pcap(core::ByteView bytes); core::Result<std::vector<PacketMetadata>> extract_metadata(const PcapFile& pcap); std::string summarize_packets(const std::vector<PacketMetadata>& packets);
}
