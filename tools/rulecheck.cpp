#include "rules/rules.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
static std::string read_text(const char* p){std::ifstream f(p,std::ios::binary); std::ostringstream s; s<<f.rdbuf(); return s.str();}
int main(int argc,char** argv){if(argc<2){std::cerr<<"usage: rulecheck <rules-file>\n"; return 2;} auto r=guardsight::rules::parse_rules_text(read_text(argv[1])); std::cout<<guardsight::rules::summarize_rules(r.value())<<"\n"; for(auto& x:r.value())std::cout<<x.normalized<<"\n"; if(!r.diagnostics().empty())std::cerr<<r.diagnostics().summary()<<"\n"; return r.diagnostics().has_errors()?1:0;}
