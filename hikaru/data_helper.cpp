﻿// Ŭnicode please
#include "hikaru_stdafx.h"
#include "data_helper.h"

#include "class_dict.h"
#include "class_attribute.h"

using namespace std;

namespace hikaru {;
std::string DataHelper::MemberAttributeDesc(const MemberAttribute &attr) {
  //sample str
  //Attribute:(Int)IntValue / 4
  //Attribute:(StrEnum)str_enum / 8 / a|b|c
  
  //타입 자체를 문자열로 보는거
  static vector<string> attr_type_str_list;
  if(attr_type_str_list.empty()) {
    attr_type_str_list.resize(kMemberAttributeCount);
    attr_type_str_list[kMemberAttributeNone] = "None";
    attr_type_str_list[kMemberAttributeBool] = "Bool";
    attr_type_str_list[kMemberAttributeString] = "String";
    attr_type_str_list[kMemberAttributeInt] = "Int";
    attr_type_str_list[kMemberAttributeFloat] = "Float";
    attr_type_str_list[kMemberAttributeStringList] = "StrList";
    attr_type_str_list[kMemberAttributeStringEnum] = "StrEnum";
  }

  bool is_enum = attr.IsUseEnum();
  HKASSERT((int)attr_type_str_list.size() > (int)attr.type());
  const string &type_name = attr_type_str_list[attr.type()];
  int offset = attr.offset();

  string result;
  char buf[256];
  sprintf(buf, "Attribute:(%s)%s / %d", type_name.c_str(), attr.name().c_str(), offset);
  result = buf;

  if(is_enum) {
    ostringstream oss;
    oss << " / ";
    const vector<string> &enum_list = attr.str_enum_list();
    for(size_t i = 0 ; i < enum_list.size() ; i++) {
      oss << enum_list[i];
      if(i != enum_list.size()-1) {
        oss << "|";
      }
    }
    result += oss.str();
  }
  return result;
}
void DataHelper::DumpMemberAttribute(const MemberAttribute &attr) {
  string str = MemberAttributeDesc(attr);
  std::cout << str << std::endl;
}

std::string DataHelper::ClassAttributeDesc(const ClassAttribute &attr) {
  ostringstream oss;
  //name version
  oss << attr.family_name() << ":" << attr.version() << "\n";
  auto it = attr.begin();
  auto endit = attr.end();
  for( ; it != endit ; ++it) {
    string str = MemberAttributeDesc(*it);
    oss << "  " << str << "\n";
  }
  return oss.str();
}

void DataHelper::DumpClassAttribute(const ClassAttribute &attr) {
  string str = ClassAttributeDesc(attr);
  std::cout << str << std::endl;
}

std::string DataHelper::ClassDictDesc(const ClassDict &dict) {
  ostringstream oss;
  vector<ClassAttribute*> class_attr_list = dict.GetTotalData();
  auto it = class_attr_list.begin();
  auto endit = class_attr_list.end();
  for( ; it != endit ; ++it) {
    ClassAttribute *class_attr = *it;
    oss << ClassAttributeDesc(*class_attr);
  }
  return oss.str();
}

void DataHelper::DumpClassDict(const ClassDict &dict) {
  string str = ClassDictDesc(dict);
  std::cout << str << std::endl;
}
} //namespace hikaru
