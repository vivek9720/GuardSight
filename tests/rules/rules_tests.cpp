#include "rules/rules.hpp"
#include <cassert>
int main(){auto r=guardsight::rules::parse_rules_text("alert tcp any any -> 10.0.0.0/8 80 (msg:\"web\"; content:\"GET\"; sid:1; rev:1;)\n"); assert(r.value().size()==1); assert(r.value()[0].destination_port.contains(80)); assert(r.value()[0].normalized.find("sid")!=std::string::npos); return 0;}
