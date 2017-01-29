#include <cassert>

#include "hikaru.h"
#include "hk_declaration.h"
#include "struct_data.txt"

int main() {
    {
        // Access BASE_VERSION
        HKDemoStruct obj;
        obj.int_val = 1;
        obj.float_val = 2.3f;
    }

    {
        // DefaultType, [Attribute]
        //int형에 대한 기본 테스트
        auto attr1 = hikaru::FieldAttribute::createInt("name", 1);
        assert(attr1.name() == "name");
        assert(1 == attr1.offset());
        assert(hikaru::AttributeType::Int == attr1.type());
    }

    {
        // ClassAttribute
        hikaru::ClassAttribute class_attr("sample1", "sample1", 0);
        class_attr.add(hikaru::FieldAttribute::createInt("a", 1));
        class_attr.add(hikaru::FieldAttribute::createInt("b", 1));

        assert(class_attr.isAttributeExist("a") == true);
        assert(class_attr.isAttributeExist("cc") == false);

        auto attr1 = class_attr.get("a");
        assert(attr1 != nullptr);
        assert(attr1->name() == "a");

        //올바르지 않은 데이터 이름
        auto attr2 = class_attr.get("sdffsdb");
        assert(nullptr == attr2);
    }

    {
        // VersionInfo [ClassDict]
        hikaru::ClassDict dict;
        dict.setClassVersionInfo("class", "class_v1", 1);
        dict.setClassVersionInfo("class", "class_v2", 2);
        dict.setClassVersionInfo("base", "base_v2", 2);

        //기반이름으로 검색
        assert(dict.isBaseClassExist("class") == true);
        assert(dict.isBaseClassExist("clasfdsfds") == false);

        //최신버전의 클래스 이름 얻기
        assert(dict.getLatestClassName("class") == "class_v2");
        assert(dict.getLatestClassName("fdjsl") == "");

        //특정 버전의 클래스 이름 얻기
        assert(dict.getClassName("class", 2) == "class_v2");
        assert(dict.getClassName("class", 3) == "");
        assert(dict.getClassName("fsdfd", 3) == "");

        //기반 클래스 목록
        std::set<std::string> base_name_set = dict.getBaseClassList();
        assert(base_name_set.size() == 2);
        assert(base_name_set.find("class") != base_name_set.end());
        assert(base_name_set.find("base") != base_name_set.end());

        //해당 이름이 최신 버전인가
        assert(dict.isLatestClassName("class_v2") == true);
        assert(dict.isLatestClassName("class_v1") == false);
    }

    printf("test pass!\n");
	return 0;
}

