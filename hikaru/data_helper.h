// Ŭnicode please
#pragma once

#include <string>

namespace hikaru {;

class MemberAttribute;
class ClassAttribute;

struct DataHelper {
  static std::string MemberAttributeDesc(const MemberAttribute &attr);
  static void DumpMemberAttribute(const MemberAttribute &attr);
};
}