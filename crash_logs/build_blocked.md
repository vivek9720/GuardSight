Fuzz build attempt summary
==========================

Repository: F:\Projects\Fenrir\GuardSight
Targets discovered: packet_fuzzer, ioc_fuzzer, rules_fuzzer, policy_fuzzer
Build script: .clusterfuzzlite/build.sh
Corpus directories: fuzz/corpus/packet_fuzzer, fuzz/corpus/ioc_fuzzer, fuzz/corpus/rules_fuzzer, fuzz/corpus/policy_fuzzer

Attempted build command:
wsl bash -lc 'cd /mnt/f/Projects/Fenrir/GuardSight && mkdir -p out pocs crash_logs && SRC="$PWD" OUT="$PWD/out" .clusterfuzzlite/build.sh && ls -la out'

Result:
/bin/sh: bash: not found

Correct WSL mount discovered:
/mnt/host/f/Projects/Fenrir/GuardSight

Toolchain check in WSL:
clang++: not found
g++: not found
cc: not found
bash: not found
cmake: not found

Native Windows toolchain check:
cmake: not found
g++: not found
clang++: not found
cl: not found

Docker check:
docker.exe exists, but daemon connection failed at npipe:////./pipe/dockerDesktopLinuxEngine.

Conclusion:
No fuzz target binaries could be built in this environment, so no sanitizer-backed fuzzing run or deterministic PoC validation could be performed locally.
