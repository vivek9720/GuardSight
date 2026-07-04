#pragma once
#include "core/status.hpp"
#include "packet/packet.hpp"
#include <map>
#include <string>
#include <vector>
namespace guardsight::rules {
struct PortSpec { bool any=true; uint16_t first=0; uint16_t last=0; bool contains(uint16_t p) const; std::string str() const; };
struct Rule { std::string action; std::string protocol; std::string source; PortSpec source_port; std::string direction; std::string destination; PortSpec destination_port; std::map<std::string,std::vector<std::string>> options; std::string normalized; };
struct RuleMatch { Rule rule; std::string packet_summary; };
core::Result<std::vector<Rule>> parse_rules_text(const std::string& text); std::vector<std::string> validate_rule(const Rule& rule); std::string normalize_rule(const Rule& rule); std::vector<RuleMatch> match_rules(const std::vector<Rule>& rules,const std::vector<packet::PacketMetadata>& packets); std::string summarize_rules(const std::vector<Rule>& rules);
}
