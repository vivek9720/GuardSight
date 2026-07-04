#include "rules/rules.hpp"
#include <cstddef>
#include <cstdint>
#include <string>
extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size){
 std::string s(reinterpret_cast<const char*>(data),size); auto r=guardsight::rules::parse_rules_text(s); (void)r;
 return 0;
}
