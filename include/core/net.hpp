#pragma once
#include <cstdint>
#include <optional>
#include <string>
#include <vector>
namespace guardsight::core {
struct IPv4Address { uint32_t value=0; std::string str() const; bool is_private() const; bool is_multicast() const; bool is_loopback() const; };
struct CidrBlock { IPv4Address network; uint8_t prefix=32; bool contains(IPv4Address a) const; std::string str() const; };
std::optional<IPv4Address> parse_ipv4(const std::string& t); std::optional<CidrBlock> parse_cidr(const std::string& t); bool is_domain_label(const std::string& l); bool is_domain_name(const std::string& d); bool is_url_like(const std::string& v); bool is_hash_like(const std::string& v); std::string protocol_name(uint8_t p); std::string service_name(uint16_t port,uint8_t proto=0); std::string dns_type_name(uint16_t t); std::string dns_class_name(uint16_t c); std::vector<std::string> suspicious_tlds();
}
