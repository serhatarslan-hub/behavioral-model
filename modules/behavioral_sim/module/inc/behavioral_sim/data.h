#ifndef _BM_DATA_H_
#define _BM_DATA_H_

#include <iostream>
#include <cstring>

#include "bignum.h"

using bignum::Bignum;

class Data
{  
public:
  Data() {}

  Data(unsigned i)
    : value(i) {}

  Data(const char *bytes, int nbytes) {
    bignum::import_bytes(value, bytes, nbytes);
  }

  Data(const std::string hexstring) {
    std::vector<char> bytes;
    for (char c : hexstring) {
      if(c >= '0' && c <= '9')
	bytes.push_back(c - '0');
      if(c >= 'A' && c <= 'F')
	bytes.push_back(c - 'A' + 10);
      if(c >= 'a' && c <= 'f')
	bytes.push_back(c - 'a' + 10);
    }
    bignum::import_bytes(value, bytes.data(), bytes.size());
  }

  void set(unsigned int i) {
    value = i;
  }

  void set(const char *bytes, int nbytes) {
    bignum::import_bytes(value, bytes, nbytes);
  }

  void set(const Data &data) {
    value = data.value;
  }

  unsigned int get_ui() const {
    assert(arith);
    // Bad ?
    return (unsigned) value;
  }

  void add(const Data &src1, const Data &src2) {
    assert(src1.arith && src2.arith);
    value = src1.value + src2.value;
  }

  friend bool operator==(const Data &lhs, const Data &rhs) {
    assert(lhs.arith && rhs.arith);
    return lhs.value == rhs.value;
  }

  friend bool operator!=(const Data &lhs, const Data &rhs) {
    assert(lhs.arith && rhs.arith);
    return !(lhs == rhs);
  }

  friend std::ostream& operator<<( std::ostream &out, const Data &d ) {
    assert(d.arith);
    out << d.value;
    return out;
  }

protected:
  Bignum value;
  bool arith{true};
};

#endif