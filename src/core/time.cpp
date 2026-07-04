#include "core/time.hpp"
#include "core/strings.hpp"
#include <ctime>
#include <iomanip>
#include <sstream>
namespace guardsight::core {
static int64_t days_from_civil(int y,unsigned m,unsigned d){y-=m<=2; const int era=(y>=0?y:y-399)/400; const unsigned yoe=static_cast<unsigned>(y-era*400); const unsigned doy=(153*(m+(m>2?-3:9))+2)/5+d-1; const unsigned doe=yoe*365+yoe/4-yoe/100+doy; return era*146097+static_cast<int>(doe)-719468;}
std::string Timestamp::iso8601() const{std::time_t t=std::time_t(seconds); std::tm tm{};
#ifdef _WIN32
gmtime_s(&tm,&t);
#else
gmtime_r(&t,&tm);
#endif
std::ostringstream o; o<<std::put_time(&tm,"%Y-%m-%dT%H:%M:%S"); if(micros>0)o<<'.'<<std::setw(6)<<std::setfill('0')<<micros; o<<'Z'; return o.str();} std::optional<Timestamp> parse_unix_timestamp(const std::string& v){auto s=trim(v); if(s.empty())return std::nullopt; bool neg=s.front()=='-'; if(neg)s.erase(s.begin()); if(!is_decimal(s))return std::nullopt; auto sec=std::stoll(s); return Timestamp{neg?-sec:sec,0};} std::optional<Timestamp> parse_iso8601_utc(const std::string& v){if(v.size()<20||v[4]!='-'||v[7]!='-'||v[10]!='T'||v[13]!=':'||v[16]!=':'||v.back()!='Z')return std::nullopt; std::tm tm{}; try{tm.tm_year=std::stoi(v.substr(0,4))-1900; tm.tm_mon=std::stoi(v.substr(5,2))-1; tm.tm_mday=std::stoi(v.substr(8,2)); tm.tm_hour=std::stoi(v.substr(11,2)); tm.tm_min=std::stoi(v.substr(14,2)); tm.tm_sec=std::stoi(v.substr(17,2));}catch(...){return std::nullopt;}
int64_t e=days_from_civil(tm.tm_year+1900,unsigned(tm.tm_mon+1),unsigned(tm.tm_mday))*86400+tm.tm_hour*3600+tm.tm_min*60+tm.tm_sec;
if(e<0)return std::nullopt; return Timestamp{e,0};} std::string format_duration_ms(uint64_t m){std::ostringstream o; uint64_t s=m/1000,ms=m%1000,min=s/60; s%=60; if(min)o<<min<<"m"; o<<s<<'.'<<std::setw(3)<<std::setfill('0')<<ms<<"s"; return o.str();}
}
