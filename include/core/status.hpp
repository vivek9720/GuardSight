#pragma once
#include <cstddef>
#include <ostream>
#include <string>
#include <utility>
#include <vector>
namespace guardsight::core {
enum class Severity { info, warning, error };
struct Diagnostic { Severity severity=Severity::info; std::string code; std::string message; std::size_t offset=0; };
class Diagnostics {
public:
 void add(Severity s,std::string c,std::string m,std::size_t o=0); void info(std::string c,std::string m,std::size_t o=0); void warn(std::string c,std::string m,std::size_t o=0); void error(std::string c,std::string m,std::size_t o=0);
 bool has_errors() const; bool empty() const; std::size_t size() const; const std::vector<Diagnostic>& items() const; std::string summary() const;
private: std::vector<Diagnostic> items_;
};
template<class T> class Result { bool ok_=false; T value_{}; Diagnostics diagnostics_; public: Result(T v,Diagnostics d):ok_(true),value_(std::move(v)),diagnostics_(std::move(d)){} Result(Diagnostics d):diagnostics_(std::move(d)){} bool ok() const{return ok_&&!diagnostics_.has_errors();} explicit operator bool() const{return ok();} T& value(){return value_;} const T& value() const{return value_;} Diagnostics& diagnostics(){return diagnostics_;} const Diagnostics& diagnostics() const{return diagnostics_;}};
std::string severity_name(Severity s); std::ostream& operator<<(std::ostream& os,const Diagnostic& d);
}
