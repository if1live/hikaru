// Ŭnicode please
#include "hikaru_stdafx.h"
#include "class_attribute.h"
#include "util.h"

using namespace std;

namespace hikaru {;

MemberAttribute MemberAttribute::StringEnum(const std::string &name, int offset) {
  return MemberAttribute(name, kMemberAttributeStringEnum, offset);
}

MemberAttribute::MemberAttribute(const std::string &name, MemberAttributeType type, int offset)
: name_(name), type_(type), offset_(offset) {
}
MemberAttribute::MemberAttribute() {}
MemberAttribute::~MemberAttribute() {}

bool MemberAttribute::IsUseEnum() const {
  return (type_ == kMemberAttributeStringEnum);
}

bool MemberAttribute::AddStringEnum(const std::string &key) {
  auto found = find(str_enum_list_.begin(), str_enum_list_.end(), key);
  if(found == str_enum_list_.end()) {
    str_enum_list_.push_back(key);
    return true;
  } else {
    return false;
  }
}

bool MemberAttribute::IsValidStrEnum(const std::string &name) const {
  auto found = find(str_enum_list_.begin(), str_enum_list_.end(), name);
  return (found != str_enum_list_.end());
}
const std::string &MemberAttribute::GetDefaultStrEnum() const {
  if(str_enum_list_.empty()) {
    static string empty;
    return empty;
  } else {
    return str_enum_list_[0];
  }
}

///////////////////////////////////////////

bool ClassAttribute::AddMember(const MemberAttribute &attr) {
  auto it = mem_attr_list_.begin();
  auto endit = mem_attr_list_.end();
  for( ; it != endit ; ++it) {
    if(it->name() == attr.name()) {
      return false;
    }
  }
  mem_attr_list_.push_back(attr);
  return true;
}
} //namespace hikaru