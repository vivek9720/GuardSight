#!/bin/bash -eu
ROOT="${SRC:-$(pwd)}"
cd "$ROOT"
COMMON_SRC="src/core/status.cpp src/core/bytes.cpp src/core/strings.cpp src/core/net.cpp src/core/time.cpp src/core/security_catalog.cpp src/packet/packet.cpp src/ioc/ioc.cpp src/rules/rules.cpp src/policy/policy.cpp"
mkdir -p "$OUT"
for target in packet_fuzzer ioc_fuzzer rules_fuzzer policy_fuzzer; do
  "$CXX" $CXXFLAGS -std=c++17 -Iinclude "fuzz/${target}.cc" $COMMON_SRC $LIB_FUZZING_ENGINE -o "$OUT/${target}"
done
