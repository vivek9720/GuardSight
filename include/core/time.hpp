#pragma once
#include <cstdint>
#include <optional>
#include <string>
namespace guardsight::core { struct Timestamp { int64_t seconds=0; int32_t micros=0; std::string iso8601() const; }; std::optional<Timestamp> parse_unix_timestamp(const std::string& v); std::optional<Timestamp> parse_iso8601_utc(const std::string& v); std::string format_duration_ms(uint64_t millis); }
