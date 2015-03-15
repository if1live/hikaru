// Ŭnicode please

#define CATCH_CONFIG_MAIN  

#include "catch.hpp"
#include "hikaru.h"
#include "hk_struct_define.h"

using namespace hikaru;

TEST_CASE("Access BASE_VERSION, [Hikaru]") {
	BASE_VERSION obj;
	obj.INT_NAME = 1;
	obj.FLOAT_NAME = 2.3f;
	obj.BOOL_NAME = true;
	obj.STRING_NAME = "hello world";
}

TEST_CASE("DefaultType", "[Attribute]")
{
	//int형에 대한 기본 테스트
	Attribute attr1 = Attribute::createInt("name", 1);
	REQUIRE(attr1.name() == "name");
	REQUIRE(1 == attr1.offset());
	REQUIRE(HK_ATTRIBUTE_INT == attr1.type());
}

TEST_CASE("test", "[ClassAttribute]")
{
	ClassAttribute class_attr("sample1", "sample1", 0);
	class_attr.add(Attribute::createInt("a", 1));
	class_attr.add(Attribute::createInt("b", 1));

	REQUIRE(class_attr.isAttributeExist("a") == true);
	REQUIRE(class_attr.isAttributeExist("cc") == false);

	Attribute *attr = NULL;
	attr = class_attr.get("a");
	REQUIRE(attr != NULL);
	REQUIRE(attr->name() == "a");

	//올바르지 않은 데이터 이름
	attr = class_attr.get("sdffsdb");
	REQUIRE(NULL == attr);
}

TEST_CASE("isClassExist_IsAttributeExist_ETC", "[ClassDict]")
{
	ClassDict dict;
	ClassAttribute sample1("sample", "sample1", 1);
	sample1.add(Attribute::createInt("a", 1));
	REQUIRE(dict.add(sample1) == true);

	ClassAttribute sample2("sample", "sample2", 2);
	sample2.add(Attribute::createInt("b", 1));
	sample2.add(Attribute::createInt("c", 1));
	REQUIRE(dict.add(sample2) == true);

	REQUIRE(dict.isClassExist("sample1") == true);
	REQUIRE(dict.isClassExist("sample2") == true);
	REQUIRE(dict.isClassExist("not_exist") == false);
	
	//없는 클래스 이름
	ClassAttribute *attr = NULL;
	attr = dict.get("safdsfdmple1");
	REQUIRE(attr == NULL);

	//잇는거 찾기
	attr = dict.get("sample1");
	REQUIRE(attr != NULL);
	REQUIRE(attr->class_name() == "sample1");
}

TEST_CASE("VersionInfo", "[ClassDict]")
{
	ClassDict dict;
	dict.setClassVersionInfo("class", "class_v1", 1);
	dict.setClassVersionInfo("class", "class_v2", 2);
	dict.setClassVersionInfo("base", "base_v2", 2);

	//기반이름으로 검색
	REQUIRE(dict.isBaseClassExist("class") == true);
	REQUIRE(dict.isBaseClassExist("clasfdsfds") == false);

	//최신버전의 클래스 이름 얻기
	REQUIRE(dict.getLatestClassName("class") == "class_v2");
	REQUIRE(dict.getLatestClassName("fdjsl") == "");

	//특정 버전의 클래스 이름 얻기
	REQUIRE(dict.getClassName("class", 2) == "class_v2");
	REQUIRE(dict.getClassName("class", 3) == "");
	REQUIRE(dict.getClassName("fsdfd", 3) == "");

	//기반 클래스 목록
	std::set<std::string> base_name_set = dict.getBaseClassList();
	REQUIRE(base_name_set.size() == 2);
	REQUIRE(base_name_set.find("class") != base_name_set.end());
	REQUIRE(base_name_set.find("base") != base_name_set.end());

	//해당 이름이 최신 버전인가
	REQUIRE(dict.isLatestClassName("class_v2") == true);
	REQUIRE(dict.isLatestClassName("class_v1") == false);
}
