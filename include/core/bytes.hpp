#pragma once
#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>
#include "core/status.hpp"
namespace guardsight::core {
class ByteView { const uint8_t* data_=nullptr; std::size_t size_=0; public: ByteView()=default; ByteView(const uint8_t* d,std::size_t s):data_(d),size_(s){} explicit ByteView(const std::vector<uint8_t>& b):data_(b.data()),size_(b.size()){} std::size_t size() const{return size_;} bool empty() const{return size_==0;} const uint8_t* data() const{return data_;} uint8_t operator[](std::size_t i) const{return i<size_?data_[i]:0;} ByteView slice(std::size_t o,std::size_t n) const; std::vector<uint8_t> to_vector() const; std::string ascii_lossy() const; };
class ByteReader { ByteView view_; std::size_t offset_=0; Diagnostics* diagnostics_=nullptr; void fail(std::size_t n); public: ByteReader(ByteView v,Diagnostics* d=nullptr):view_(v),diagnostics_(d){} std::size_t offset() const{return offset_;} std::size_t remaining() const{return offset_<=view_.size()?view_.size()-offset_:0;} bool can_read(std::size_t n) const{return n<=remaining();} bool seek(std::size_t o); bool skip(std::size_t n); bool read_u8(uint8_t& v); bool read_u16_be(uint16_t& v); bool read_u16_le(uint16_t& v); bool read_u32_be(uint32_t& v); bool read_u32_le(uint32_t& v); bool read_i32_le(int32_t& v); bool read_bytes(std::size_t n,ByteView& out); ByteView tail() const{return view_.slice(offset_,remaining());} };
uint16_t read_u16_be(const uint8_t* d); uint16_t read_u16_le(const uint8_t* d); uint32_t read_u32_be(const uint8_t* d); uint32_t read_u32_le(const uint8_t* d); uint16_t internet_checksum(ByteView v); std::string hex_encode(ByteView v,bool spaced=false); std::vector<uint8_t> hex_decode_relaxed(const std::string& s);
}
