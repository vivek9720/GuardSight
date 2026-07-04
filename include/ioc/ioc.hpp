#pragma once
#include "core/net.hpp"
#include "core/status.hpp"
#include "packet/packet.hpp"
#include <set>
#include <string>
#include <vector>
namespace guardsight::ioc {
enum class IocType { ip, cidr, domain, url, hash, unknown };
struct IocEntry { IocType type=IocType::unknown; std::string raw; std::string value; std::string severity="medium"; double confidence=0.5; bool allow=false; std::string source; };
struct IocSet { std::vector<IocEntry> entries; std::vector<std::string> duplicates; };
struct IocMatch { IocEntry entry; std::string field; std::string observed; std::string packet_summary; };
std::string ioc_type_name(IocType t); IocEntry normalize_ioc_line(const std::string& line, core::Diagnostics& d, std::size_t line_no=0); core::Result<IocSet> parse_ioc_text(const std::string& text); std::vector<IocMatch> match_packet_metadata(const IocSet& set,const std::vector<packet::PacketMetadata>& packets); std::string summarize_iocs(const IocSet& set); std::string summarize_matches(const std::vector<IocMatch>& matches);
}
