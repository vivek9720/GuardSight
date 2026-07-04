#include "packet/packet.hpp"
#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>
static std::vector<uint8_t> read_file(const char* path){std::ifstream f(path,std::ios::binary); return {std::istreambuf_iterator<char>(f),std::istreambuf_iterator<char>()};}
int main(int argc,char** argv){if(argc<2){std::cerr<<"usage: packetscan <capture.pcap>\n"; return 2;} auto b=read_file(argv[1]); auto p=guardsight::packet::parse_pcap(guardsight::core::ByteView(b)); if(!p){std::cerr<<p.diagnostics().summary()<<"\n"; return 1;} auto m=guardsight::packet::extract_metadata(p.value()); std::cout<<guardsight::packet::summarize_packets(m.value()); if(!p.diagnostics().empty())std::cerr<<p.diagnostics().summary()<<"\n"; return m.diagnostics().has_errors()?1:0;}
