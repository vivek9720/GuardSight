#pragma once
#include <map>
#include <string>
#include <vector>
namespace guardsight::core {
std::string trim(std::string v); std::string lower(std::string v); std::string upper(std::string v); bool starts_with(const std::string& v,const std::string& p); bool ends_with(const std::string& v,const std::string& s); std::vector<std::string> split(const std::string& v,char d,bool keep_empty=false); std::vector<std::string> split_lines(const std::string& v); std::string join(const std::vector<std::string>& v,const std::string& d); std::string collapse_spaces(const std::string& v); bool is_decimal(const std::string& v); bool is_hex_string(const std::string& v); bool is_printable_ascii(const std::string& v); std::string strip_quotes(const std::string& v); std::string remove_comment(const std::string& line); std::map<std::string,std::string> parse_key_value_list(const std::string& text,char pair_delim,char kv_delim); std::string escape_json(const std::string& v); std::string percent_decode(const std::string& v); std::string normalize_domain(const std::string& v); std::string normalize_url(const std::string& v);
}
