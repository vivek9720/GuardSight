#include "ioc/ioc.hpp"
#include "packet/packet.hpp"
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <vector>
static std::string read_text(const char* p){std::ifstream f(p,std::ios::binary); std::ostringstream s; s<<f.rdbuf(); return s.str();} static std::vector<uint8_t> read_bytes(const char* p){std::ifstream f(p,std::ios::binary); return {std::istreambuf_iterator<char>(f),std::istreambuf_iterator<char>()};}
int main(int argc,char** argv){if(argc<3){std::cerr<<"usage: iocmatch <ioc-file> <capture.pcap>\n"; return 2;} auto i=guardsight::ioc::parse_ioc_text(read_text(argv[1])); auto b=read_bytes(argv[2]); auto p=guardsight::packet::parse_pcap(guardsight::core::ByteView(b)); if(!p){std::cerr<<p.diagnostics().summary()<<"\n"; return 1;} auto meta=guardsight::packet::extract_metadata(p.value()); auto matches=guardsight::ioc::match_packet_metadata(i.value(),meta.value()); std::cout<<guardsight::ioc::summarize_iocs(i.value())<<"\n"<<guardsight::ioc::summarize_matches(matches); return 0;}
