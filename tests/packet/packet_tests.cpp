#include "packet/packet.hpp"
#include <cassert>
int main(){const unsigned char dns[]={0x12,0x34,0x01,0x00,0x00,0x01,0,0,0,0,0,0,7,'e','x','a','m','p','l','e',3,'c','o','m',0,0,1,0,1}; auto r=guardsight::packet::parse_dns(guardsight::core::ByteView(dns,sizeof(dns))); assert(r); assert(r.value().questions.size()==1); assert(r.value().questions[0].name=="example.com"); return 0;}
