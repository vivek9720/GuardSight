# GuardSight

GuardSight is an offline defensive cybersecurity toolkit for inspecting packet captures, IOC lists, IDS-style signatures, and local firewall or policy exports. It is designed for security engineers and system administrators who need deterministic local analysis without sending artifacts to a service.

## Use Cases

- Summarize local PCAP files and extract IPv4, TCP, UDP, and DNS metadata.
- Normalize IOC files containing IP addresses, CIDR ranges, domains, URLs, and file hashes.
- Match IOC collections against packet metadata from local captures.
- Inspect Snort/Suricata-like IDS signature subsets for normalization and validation issues.
- Audit iptables-style and nftables-style firewall rules for duplicates, broad accepts, and shadowing.
- Reuse the C++17 parsing library from other offline defensive tools.

## Supported Artifacts

- Classic PCAP files with Ethernet link-layer captures.
- Ethernet, IPv4, TCP, UDP, and DNS packet data.
- IOC text, CSV-like, and key/value files.
- IDS rules with action, protocol, source, destination, ports, msg, content, sid, 
ev, and classtype fields.
- iptables-style rules, nftables-style rules, INI-like settings, and simple JSON/CSV-style policy lines.

## Architecture

- core: byte readers, endian helpers, diagnostics, string utilities, timestamps, checksum support, IPv4 and CIDR helpers.
- packet: PCAP, Ethernet, IPv4, TCP, UDP, DNS parsing, metadata extraction, and summaries.
- ioc: IOC normalization, duplicate detection, allowlist/blocklist handling, and packet metadata matching.
- 
ules: IDS-style lexer/parser, normalization, validation, and packet metadata matching helpers.
- policy: firewall and local policy parsing, duplicate detection, ordering analysis, and summary generation.
- 	ools: command-line programs that call the reusable library.

## Build

`sh
cmake -S . -B build
cmake --build build --config Release
`

The build uses only the C++17 standard library and local source files.

## CLI Usage

`sh
packetscan capture.pcap
iocmatch indicators.txt capture.pcap
rulecheck signatures.rules
policyaudit firewall.txt
`

Each command reads local files only and writes deterministic text output.

## Tests

`sh
ctest --test-dir build --output-on-failure
`

The tests cover valid and invalid parsing paths across core helpers, DNS parsing, IOC normalization, IDS rule parsing, and policy analysis.

## Developer Robustness QA

The uzz/ directory contains libFuzzer entry points for packet, IOC, rule, and policy parsers. They exercise the same project code used by the CLI tools.

Example local build commands on a Clang/libFuzzer environment:

`sh
mkdir -p out
CXX=clang++ CXXFLAGS="-O1 -g -fsanitize=fuzzer-no-link,address,undefined" LIB_FUZZING_ENGINE="-fsanitize=fuzzer" OUT="$PWD/out" .clusterfuzzlite/build.sh
./out/packet_fuzzer fuzz/corpus/packet_fuzzer -max_total_time=30
./out/ioc_fuzzer fuzz/corpus/ioc_fuzzer -max_total_time=30
./out/rules_fuzzer fuzz/corpus/rules_fuzzer -max_total_time=30
./out/policy_fuzzer fuzz/corpus/policy_fuzzer -max_total_time=30
`

## Seed Corpus

The seed corpus includes small valid captures, TCP and UDP/DNS captures, near-valid malformed PCAP data, representative IOC lists, IDS rules, and firewall policy examples. The dictionary contains protocol, IOC, IDS, firewall, and structured-text tokens that help robustness tests reach deeper parser states quickly.

## Manual Review Checklist

- Confirm parsers reject truncated inputs without undefined behavior.
- Review diagnostics for clarity and stable wording.
- Check that CLI tools never use network access or credentials.
- Verify normalization does not hide materially different security artifacts.
- Review firewall shadowing findings against local operational policy before acting.
- Keep third-party code out of the repository unless it is intentionally added through a reviewed dependency process.
