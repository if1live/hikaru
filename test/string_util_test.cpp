// Ŭnicode please
#include <gtest/gtest.h>
#include "string_util.h"

using namespace std;
using namespace qb;

TEST(StringUtil, split)
{
	string s1 = "1,2";
	vector<string> result1;
	StringUtil::Split(s1, result1, string(","));
	EXPECT_EQ(2, result1.size());
	EXPECT_STREQ("1", result1[0].c_str());
	EXPECT_STREQ("2", result1[1].c_str());

	string s2 = "1,2,3,4";
	vector<string> result2;
	StringUtil::Split(s2, result2, string(","));
	EXPECT_EQ(4, result2.size());
	EXPECT_STREQ("1", result2[0].c_str());
	EXPECT_STREQ("2", result2[1].c_str());
	EXPECT_STREQ("3", result2[2].c_str());
	EXPECT_STREQ("4", result2[3].c_str());
}

TEST(StringUtil, ToUpper)
{
	string s1 = "asdf";
	string s2 = StringUtil::ToUpper(s1);
	EXPECT_STREQ("ASDF", s2.c_str());
}
TEST(StringUtil, ToLower)
{
	string s1 = "ASdf";
	string s2 = StringUtil::ToLower(s1);
	EXPECT_STREQ("asdf", s2.c_str());
}

TEST(StringUtil, SplitLine)
{
	vector<char*> line_list;

	//널 문자열
	line_list = StringUtil::SplitLine((char*)NULL);
	EXPECT_EQ(0, line_list.size());

	//빈 문자열
	line_list = StringUtil::SplitLine((char*)"");
	EXPECT_EQ(0, line_list.size());

	//한줄
	line_list = StringUtil::SplitLine((char*)"12");
	ASSERT_EQ(1, line_list.size());
	ASSERT_STREQ("12", line_list[0]);

	//한줄+마지막에 개행 여러개
	char str1[] = "12\n\r\n";
	line_list = StringUtil::SplitLine(str1);
	ASSERT_EQ(1, line_list.size());
	ASSERT_STREQ("12", line_list[0]);

	//여러줄+개행섞기
	char str2[] = "12\n\r\nabc\n\ref";
	line_list = StringUtil::SplitLine(str2);
	ASSERT_EQ(3, line_list.size());
	ASSERT_STREQ("12", line_list[0]);
	ASSERT_STREQ("abc", line_list[1]);
	ASSERT_STREQ("ef", line_list[2]);
}