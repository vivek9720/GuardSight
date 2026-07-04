#include "packet/packet.hpp"
#include <cstddef>
#include <cstdint>
#include <string>
extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size){
 auto p=guardsight::packet::parse_pcap(guardsight::core::ByteView(data,size)); if(p){auto m=guardsight::packet::extract_metadata(p.value()); (void)m;}
 return 0;
}
