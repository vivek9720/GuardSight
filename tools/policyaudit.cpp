#include "policy/policy.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
static std::string read_text(const char* p){std::ifstream f(p,std::ios::binary); std::ostringstream s; s<<f.rdbuf(); return s.str();}
int main(int argc,char** argv){if(argc<2){std::cerr<<"usage: policyaudit <policy-file>\n"; return 2;} auto p=guardsight::policy::parse_policy_text(read_text(argv[1])); auto f=guardsight::policy::analyze_policy(p.value()); std::cout<<guardsight::policy::summarize_policy(p.value(),f)<<"\n"; if(!p.diagnostics().empty())std::cerr<<p.diagnostics().summary()<<"\n"; return 0;}
