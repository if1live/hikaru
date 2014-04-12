// Ŭnicode please
#include <gtest/gtest.h>
#include "class_attribute.h"

using namespace std;
using namespace qb;

TEST(Attribute, DefaultType)
{
	//int형에 대한 기본 테스트
	Attribute attr1 = Attribute::Int("name", 1);
	EXPECT_STREQ("name", attr1.name().c_str());
	EXPECT_EQ(1, attr1.offset());
	EXPECT_EQ(kAttributeInt, attr1.type());
	EXPECT_EQ(false, attr1.IsUseEnum());
	EXPECT_EQ(0, attr1.GetEnumCount());
}

TEST(Attribute, StrEnumType)
{
	Attribute attr = Attribute::StringEnum("name", 1);
	EXPECT_EQ(kAttributeStringEnum, attr.type());
	EXPECT_EQ(true, attr.IsUseEnum());

	EXPECT_EQ(0, attr.GetEnumCount());
	attr.AddStringEnum("a");
	EXPECT_EQ(1, attr.GetEnumCount());
	attr.AddStringEnum("b");
	EXPECT_EQ(2, attr.GetEnumCount());
	//중복 추가는 무시
	attr.AddStringEnum("a");
	EXPECT_EQ(2, attr.GetEnumCount());

	EXPECT_EQ(true, attr.IsValidStrEnum("a"));
	EXPECT_EQ(false, attr.IsValidStrEnum("xx"));
}

TEST(ClassAttribute, test)
{
	ClassAttribute class_attr("sample1", "sample1", 0);
	class_attr.Add(Attribute::Int("a", 1));
	class_attr.Add(Attribute::Int("b", 1));

	EXPECT_EQ(true, class_attr.IsAttributeExist("a"));
	EXPECT_EQ(false, class_attr.IsAttributeExist("cc"));

	Attribute *attr = NULL;
	attr = class_attr.Get("a");
	ASSERT_EQ(true, attr != NULL);
	EXPECT_STREQ("a", attr->name().c_str());

	//올바르지 않은 데이터 이름
	attr = class_attr.Get("sdffsdb");
	EXPECT_EQ(NULL, attr);	
}