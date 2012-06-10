// Ŭnicode please
#include "hikaru_test_stdafx.h"
#include "data_helper.h"
#include "class_dict.h"
#include "class_attribute.h"

using namespace std;
using namespace hikaru;

TEST(DataHelper, MemberAttributeDesc) {
  hikaru::MemberAttribute attr1 = hikaru::MemberAttribute::Create("asdf", 4, hikaru::MemberType2Type<int>());
  DataHelper::DumpMemberAttribute(attr1);
  
  //string enum test
  hikaru::MemberAttribute attr2 = hikaru::MemberAttribute::StringEnum("asdf", 10);
  attr2.AddStringEnum("a");
  attr2.AddStringEnum("b");
  attr2.AddStringEnum("c");
  DataHelper::DumpMemberAttribute(attr2);
  
}