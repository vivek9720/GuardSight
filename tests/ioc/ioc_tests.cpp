#include "ioc/ioc.hpp"
#include <cassert>
int main(){auto r=guardsight::ioc::parse_ioc_text("1.2.3.4\nexample.com\nhttps://Example.com/path\naaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\n10.0.0.0/8\n"); assert(r.value().entries.size()==5); assert(guardsight::ioc::summarize_iocs(r.value()).find("domain=1")!=std::string::npos); return 0;}
