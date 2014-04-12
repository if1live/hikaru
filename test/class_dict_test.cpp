// Ŭnicode please
#include <gtest/gtest.h>
#include "class_dict.h"

using namespace std;
using namespace qb;

TEST(ClassDict, IsClassExist_IsAttributeExist_ETC)
{
	ClassDict dict;
	ClassAttribute sample1("sample", "sample1", 1);
	sample1.Add(Attribute::Int("a", 1));
	EXPECT_EQ(true, dict.Add(sample1));

	ClassAttribute sample2("sample", "sample2", 2);
	sample2.Add(Attribute::Int("b", 1));
	sample2.Add(Attribute::Int("c", 1));
	EXPECT_EQ(true, dict.Add(sample2));

	EXPECT_EQ(true, dict.IsClassExist("sample1"));
	EXPECT_EQ(true, dict.IsClassExist("sample2"));
	EXPECT_EQ(false, dict.IsClassExist("not_exist"));

	//없는 클래스 이름
	ClassAttribute *attr = NULL;
	attr = dict.Get("safdsfdmple1");
	EXPECT_EQ(NULL, attr);

	//잇는거 찾기
	attr = dict.Get("sample1");
	EXPECT_EQ(true, attr != NULL);
	EXPECT_STREQ("sample1", attr->class_name().c_str());
}

TEST(ClassDict, VersionInfo)
{
	ClassDict dict;
	dict.SetClassVersionInfo("class", "class_v1", 1);
	dict.SetClassVersionInfo("class", "class_v2", 2);
	dict.SetClassVersionInfo("base", "base_v2", 2);

	//기반이름으로 검색
	EXPECT_EQ(true, dict.IsBaseClassExist("class"));
	EXPECT_EQ(false, dict.IsBaseClassExist("clasfdsfds"));

	//최신버전의 클래스 이름 얻기
	EXPECT_STREQ("class_v2", dict.GetLatestClassName("class").c_str());
	EXPECT_STREQ("", dict.GetLatestClassName("fdjsl").c_str());

	//특정 버전의 클래스 이름 얻기
	EXPECT_STREQ("class_v2", dict.GetClassName("class", 2).c_str());
	EXPECT_STREQ("", dict.GetClassName("class", 3).c_str());
	EXPECT_STREQ("", dict.GetClassName("fsdfd", 3).c_str());

	//기반 클래스 목록
	set<string> base_name_set = dict.GetBaseClassList();
	EXPECT_EQ(2, base_name_set.size());
	EXPECT_EQ(true, base_name_set.find("class") != base_name_set.end());
	EXPECT_EQ(true, base_name_set.find("base") != base_name_set.end());

	//해당 이름이 최신 버전인가
	EXPECT_EQ(true, dict.IsLatestClassName("class_v2"));
	EXPECT_EQ(false, dict.IsLatestClassName("class_v1"));
	

}

