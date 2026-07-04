#pragma once
#include "core/net.hpp"
#include "core/status.hpp"
#include <map>
#include <string>
#include <vector>
namespace guardsight::policy {
struct FirewallRule { std::string family="inet"; std::string chain; std::string action; std::string protocol="any"; std::string source="any"; std::string destination="any"; uint16_t dport=0; bool any_dport=true; std::string raw; std::map<std::string,std::string> attributes; };
struct PolicyFile { std::vector<FirewallRule> rules; std::map<std::string,std::string> settings; };
struct PolicyFinding { std::string severity; std::string message; std::size_t line=0; };
core::Result<PolicyFile> parse_policy_text(const std::string& text); std::vector<PolicyFinding> analyze_policy(const PolicyFile& policy); std::string summarize_policy(const PolicyFile& policy,const std::vector<PolicyFinding>& findings); std::string normalize_firewall_rule(const FirewallRule& rule);
}
