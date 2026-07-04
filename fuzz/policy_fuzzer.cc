#include "policy/policy.hpp"
#include <cstddef>
#include <cstdint>
#include <string>
extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size){
 std::string s(reinterpret_cast<const char*>(data),size); auto p=guardsight::policy::parse_policy_text(s); if(p){auto f=guardsight::policy::analyze_policy(p.value()); (void)f;}
 return 0;
}
