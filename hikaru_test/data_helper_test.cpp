// Ŭnicode please
#include "hikaru_test_stdafx.h"
#include "data_helper.h"
#include "class_dict.h"
#include "class_attribute.h"
#include "data_define.h"

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

TEST(DataHelper, ClassAttributeDesc) {
  /*
  typedef SampleData_family<1> DataType;
  auto type_info = TypeInfo<DataType>();
  ClassAttribute class_attr(type_info);
  DataHelper::DumpClassAttribute(class_attr);
  */

  ClassDict &class_dict = ClassDict::GetInstance();
  ClassAttribute *class_attr = class_dict.GetLatestVersionClassAttribute("SampleData");
  DataHelper::DumpClassAttribute(*class_attr);

  ClassAttribute *class_attr_1 = class_dict.GetClassAttribute("SampleData", 1);
  DataHelper::DumpClassAttribute(*class_attr_1);
}