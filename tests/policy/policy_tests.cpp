#include "policy/policy.hpp"
#include <cassert>
int main(){auto p=guardsight::policy::parse_policy_text("default_policy=DROP\n-A INPUT -p tcp --dport 22 -s 10.0.0.0/8 -j ACCEPT\n-A INPUT -p tcp -j ACCEPT\n"); auto f=guardsight::policy::analyze_policy(p.value()); assert(p.value().rules.size()==2); assert(!f.empty()); return 0;}
