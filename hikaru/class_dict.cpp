﻿// Ŭnicode please
#include "hikaru_stdafx.h"
#include "class_dict.h"
#include "class_attribute.h"

using namespace std;

namespace hikaru {;
ClassDict &ClassDict::GetInstance() {
  static ClassDict ctx;
  return ctx;
}
ClassDict::ClassDict() {
}
ClassDict::~ClassDict() {
  auto it = class_attr_dict_.begin();
  auto endit = class_attr_dict_.end();
  for( ; it != endit ; ++it) {
    delete(it->second);
  }
}

bool ClassDict::Register(ClassAttribute *class_attr) {
  //같은버전에 같은형식으로 등록된거 있으면 false
  auto equal_range = class_attr_dict_.equal_range(class_attr->family_name());
  auto it = equal_range.first;
  auto endit = equal_range.second;
  for( ; it != endit ; it++) {
    if(it->second->version() == class_attr->version()
      && it->second->FamilyCode() == class_attr->FamilyCode()) {
        return false;
    }
  }

  class_attr_dict_.insert(make_pair(class_attr->family_name(), class_attr));
  return true;
}

int ClassDict::GetLatestVersion(const std::string &family_name) const {
  auto found = latest_version_dict_.find(family_name);
  if(found != latest_version_dict_.end()) {
    return found->second;
  }
  //등록된거중 최고버전을 최신이라고 치자
  auto equal_range = class_attr_dict_.equal_range(family_name);
  auto it = equal_range.first;
  auto endit = equal_range.second;
  int high_version = -99999;
  for( ; it != endit ; it++) {
    if(it->second->version() > high_version) {
      high_version = it->second->version();
    }
  }
  return high_version;
}

bool ClassDict::SetLatestVersion(const std::string &family_name, int version) {
  //이미 존재하는 객체일 경우에만 최고버전이라고 정의 가능
  auto equal_range = class_attr_dict_.equal_range(family_name);
  auto it = equal_range.first;
  auto endit = equal_range.second;
  bool is_exist = false;
  for( ; it != endit ; ++it) {
    if(it->second->version() == version) {
      is_exist = true;
      break;
    }
  }
  if(is_exist == false) {
    return false;
  }

  latest_version_dict_[family_name] = version;
  return true;
}
} //namespace hikaru