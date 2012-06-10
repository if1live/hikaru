// Ŭnicode please
#include "hikaru_test_stdafx.h"
#include "class_attribute.h"

#include "data_define.h"

using namespace hikaru;
using namespace std;

TEST(MemberAttribute, Constructor) {
  hikaru::MemberAttribute attr1 = hikaru::MemberAttribute::Create("asdf", 4, hikaru::MemberType2Type<int>());
  EXPECT_EQ(hikaru::kMemberAttributeInt, attr1.type());
  EXPECT_STREQ("asdf", attr1.name().c_str());
  EXPECT_EQ(4, attr1.offset());

  //string enum test
  hikaru::MemberAttribute attr2 = hikaru::MemberAttribute::StringEnum("asdf", 10);
  EXPECT_EQ(true, attr2.AddStringEnum("a"));
  EXPECT_EQ(true, attr2.AddStringEnum("b"));
  EXPECT_EQ(true, attr2.AddStringEnum("c"));
  EXPECT_EQ(false, attr2.AddStringEnum("c"));
  EXPECT_EQ(3, attr2.GetEnumCount());
  EXPECT_EQ(true, attr2.IsValidStrEnum("a"));
  EXPECT_EQ(false, attr2.IsValidStrEnum("xxx"));
  EXPECT_STREQ("a", attr2.GetDefaultStrEnum().c_str());
}


TEST(ClassAttribute, testing) {
  {
    typedef SampleData_family<1> DataType;
    auto type_info = TypeInfo<DataType>();
    ClassAttribute class_attr(type_info);
    EXPECT_EQ(1, class_attr.version());

    auto_ptr<BaseData> obj(class_attr.Create());
    EXPECT_EQ(DataType::ClassCode(), obj->class_code());
    EXPECT_EQ(DataType::FamilyCode(), obj->family_code());
    EXPECT_EQ(DataType::ClassCode(), class_attr.ClassCode());
    EXPECT_EQ(DataType::FamilyCode(), class_attr.FamilyCode());
  }
}