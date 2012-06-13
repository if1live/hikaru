// Ŭnicode please
#include "hikaru_test_stdafx.h"
#include "class_dict.h"
#include "data_define.h"

using namespace std;
using namespace hikaru;

TEST(ClassDict, test) {
  ClassDict class_dict;

  auto typeinfo1 = TypeInfo< SampleData_family<1> >();
  ClassAttribute *attr_1 = new ClassAttribute(typeinfo1);

  auto typeinfo2 = TypeInfo< SampleData_family<2> >();
  ClassAttribute *attr_2 = new ClassAttribute(typeinfo2);

  EXPECT_EQ(true, class_dict.Register(attr_1));
  EXPECT_EQ(false, class_dict.Register(attr_1));
  EXPECT_EQ(true, class_dict.Register(attr_2));

  EXPECT_EQ(2, class_dict.GetLatestVersion(SampleData::FamilyName()));

  EXPECT_EQ(false, class_dict.SetLatestVersion(SampleData::FamilyName(), -1));
  EXPECT_EQ(true, class_dict.SetLatestVersion(SampleData::FamilyName(), 1));
  EXPECT_EQ(1, class_dict.GetLatestVersion(SampleData::FamilyName()));
  EXPECT_EQ(true, class_dict.SetLatestVersion(SampleData::FamilyName(), 2));
  EXPECT_EQ(2, class_dict.GetLatestVersion(SampleData::FamilyName()));
}

TEST(ClassAttribute, GetClassAttribute) {
  ClassDict &class_dict = ClassDict::GetInstance();
  ClassAttribute *class_attr = class_dict.GetLatestVersionClassAttribute("SampleData");
  EXPECT_EQ(2, class_attr->version());
  EXPECT_STREQ("SampleData", class_attr->family_name().c_str());

  ClassAttribute *class_attr_1 = class_dict.GetClassAttribute("SampleData", 1);
  EXPECT_EQ(1, class_attr_1->version());
  EXPECT_STREQ("SampleData", class_attr_1->family_name().c_str());
}