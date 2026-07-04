#include "core/net.hpp"
#include "core/strings.hpp"
#include <cassert>
int main(){auto ip=guardsight::core::parse_ipv4("192.168.1.20"); assert(ip&&ip->is_private()); auto c=guardsight::core::parse_cidr("192.168.1.0/24"); assert(c&&c->contains(*ip)); assert(guardsight::core::normalize_domain("Example.COM.")=="example.com"); assert(!guardsight::core::parse_ipv4("999.1.1.1")); return 0;}
