// Ŭnicode please
#include <gtest/gtest.h>
#include "data_define.h"
#include "data_init.h"

using namespace qb;
using namespace std;

bool init_SampleData_v1_run = init_SampleData_v1();
bool init_SampleData_v2_run = init_SampleData_v2();

TEST(BaseData, test) {
	ClassDict &dict = ClassDict::GetInstance();
	
	//코드로 수동생성한거 적절히 연결
	ClassAttribute *data_a = dict.Get("SampleData_v1");
	ASSERT_EQ(true, data_a != NULL);
	EXPECT_STREQ("SampleData", data_a->base_name().c_str());
	EXPECT_STREQ("SampleData_v1", data_a->class_name().c_str());
	EXPECT_EQ(1, data_a->version());
	//int 1개
	EXPECT_EQ(1, data_a->Count());
	auto it = data_a->Begin();
	auto endit = data_a->End();
	for( ; it != endit ; ++it) {
		const Attribute &attr = *it;
		if(attr.name() == "int_value") {
			EXPECT_EQ(kAttributeInt, attr.type());
		}
	}

	ClassAttribute *data_b = dict.Get(dict.GetLatestClassName("SampleData"));
	EXPECT_STREQ("SampleData", data_b->base_name().c_str());
	EXPECT_STREQ("SampleData_v2", data_b->class_name().c_str());
	EXPECT_EQ(2, data_b->version());
	//float + string enum
	EXPECT_EQ(2, data_b->Count());
	it = data_b->Begin();
	endit = data_b->End();
	for( ; it != endit ; ++it) {
		const Attribute &attr = *it;
		if(attr.name() == "float_value") {
			EXPECT_EQ(kAttributeFloat, attr.type());
		} else if(attr.name() == "str_enum") {
			EXPECT_EQ(kAttributeStringEnum, attr.type());
			EXPECT_EQ(2, attr.GetEnumCount());
			EXPECT_EQ(true, attr.IsValidStrEnum("a"));
			EXPECT_EQ(true, attr.IsValidStrEnum("b"));
			EXPECT_EQ(false, attr.IsValidStrEnum("c"));
		}
	}
}


TEST(BaseData, macro_gen)
{
	//bool init_DemoStruct_v1_run = init_DemoStruct_v1();
	//bool init_DemoStruct_v2_run = init_DemoStruct_v2();
	init_generated_data();

	//매크로 기반으로 생성된거 적절히 잇나 테스트
	ClassDict &dict = ClassDict::GetInstance();

	ClassAttribute *data_a = dict.Get("DemoStruct_v1");
	ASSERT_EQ(true, data_a != NULL);
	EXPECT_STREQ("DemoStruct", data_a->base_name().c_str());
	EXPECT_STREQ("DemoStruct_v1", data_a->class_name().c_str());
	EXPECT_EQ(1, data_a->version());
	//int
	Attribute *int_var = data_a->Get("a");
	ASSERT_EQ(true, int_var != NULL);
	EXPECT_EQ(kAttributeInt, int_var->type());

	//float
	Attribute *float_var = data_a->Get("b");
	ASSERT_EQ(true, float_var != NULL);
	EXPECT_EQ(kAttributeFloat, float_var->type());

	//bool
	Attribute *bool_var = data_a->Get("c");
	ASSERT_EQ(true, bool_var != NULL);
	EXPECT_EQ(kAttributeBool, bool_var->type());

	//string
	Attribute *string_var = data_a->Get("d");
	ASSERT_EQ(true, string_var != NULL);
	EXPECT_EQ(kAttributeString, string_var->type());

	//vec2
	Attribute *vec2_var = data_a->Get("e");
	ASSERT_EQ(true, vec2_var != NULL);
	EXPECT_EQ(kAttributeVec2, vec2_var->type());

	//string list
	Attribute *str_list_var = data_a->Get("f");
	ASSERT_EQ(true, str_list_var != NULL);
	EXPECT_EQ(kAttributeStringList, str_list_var->type());
	
	//vec2 list
	Attribute *vec2_list_var = data_a->Get("g");
	ASSERT_EQ(true, vec2_list_var != NULL);
	EXPECT_EQ(kAttributeVec2List, vec2_list_var->type());


	ClassAttribute *data_b = dict.Get(dict.GetLatestClassName("DemoStruct"));
	ASSERT_EQ(true, data_b != NULL);
	EXPECT_STREQ("DemoStruct", data_b->base_name().c_str());
	EXPECT_STREQ("DemoStruct_v2", data_b->class_name().c_str());
	EXPECT_EQ(2, data_b->version());

	//string enum
	Attribute *str_enum_var = data_b->Get("c");
	ASSERT_EQ(true, str_enum_var != NULL);
	EXPECT_EQ(kAttributeStringEnum, str_enum_var->type());
	EXPECT_EQ(3, str_enum_var->GetEnumCount());
	EXPECT_EQ(true, str_enum_var->IsValidStrEnum("1"));
	EXPECT_EQ(true, str_enum_var->IsValidStrEnum("2"));
	EXPECT_EQ(true, str_enum_var->IsValidStrEnum("3"));
}

TEST(BaseData, constuct)
{
	init_generated_data();
	
	DemoStruct_v1 data_a;
	EXPECT_EQ(BaseData::HashFunction::Hash("DemoStruct_v1"), data_a.class_hash);
	EXPECT_EQ(BaseData::HashFunction::Hash("DemoStruct"), data_a.base_hash);
	EXPECT_EQ(DemoStruct_v1::ClassHash(), data_a.class_hash);
	EXPECT_EQ(DemoStruct_v1::BaseHash(), data_a.base_hash);
	ClassAttribute *attr = ClassDict::GetInstance().Get(data_a.class_hash);
	EXPECT_STREQ("DemoStruct_v1", attr->class_name().c_str());
}
