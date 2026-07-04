#include "ioc/ioc.hpp"
#include <cstddef>
#include <cstdint>
#include <string>
extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size){
 std::string s(reinterpret_cast<const char*>(data),size); auto r=guardsight::ioc::parse_ioc_text(s); (void)r;
 return 0;
}
