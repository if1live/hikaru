// Ŭnicode please
#include "hikaru_stdafx.h"
#include "util.h"

namespace hikaru {;
unsigned int RSHash::Hash(const std::string &str) {
  unsigned int b    = 378551;
  unsigned int a    = 63689;
  unsigned int hash = 0;

  for(std::size_t i = 0; i < str.length(); i++) {
    hash = hash * a + str[i];
    a    = a * b;
  }

  return (hash & 0x7FFFFFFF);
}
}