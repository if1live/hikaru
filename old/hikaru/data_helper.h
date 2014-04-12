// Ŭnicode please
#pragma once

#include <string>

namespace hikaru {;

class ClassDict;
class MemberAttribute;
class ClassAttribute;

struct DataHelper {
  static std::string MemberAttributeDesc(const MemberAttribute &attr);
  static void DumpMemberAttribute(const MemberAttribute &attr);

  static std::string ClassAttributeDesc(const ClassAttribute &attr);
  static void DumpClassAttribute(const ClassAttribute &attr);

  static std::string ClassDictDesc(const ClassDict &dict);
  static void DumpClassDict(const ClassDict &dict);
};
}