// Ŭnicode please

#ifndef __HK_CLASS_DICT__
#define __HK_CLASS_DICT__

#include "hk_globals.h"
#include <cassert>
#include <set>
#include <unordered_map>

#include "hk_attribute.h"

NAMESPACE_HIKARU_BEGIN

//클래스이름-attribute로 연결되니까
//중간클래스를 도입해서 복잡도를 늘리기보다
//multimap으로 적절히 때울수 잇을거같다
//이 클래스 하나로 클래스사용가능한 클래스 목록. 내부에 들어잇는 변수목록까지
//전부 때우자. 이걸 여러 클래스로 나누면 그것도 그거 나름대로 복잡해 질거같아서..
class ClassDict {
public:
	static ClassDict &getInstance()	{
		static ClassDict ctx;
		return ctx;
	}

public:
	//컴포넌트마다 버전이 잇고 버전별로 여러개의 조합이 생길수 잇으니까 이렇게 
	//사전을 하나 추가해서 데이터 관리로 쓸수 잇도록햇다
	//key : BeltHeader
	//value : pair<VeltHeader_v1, 1> 같은 식으로 되도록함
	typedef std::tr1::unordered_multimap<std::string, std::pair<std::string, int> > VersionDictType;
	typedef std::vector<ClassAttribute> ClassAttributeListType;

public:
	ClassDict() {}
	~ClassDict() {}
	void clear() {
		class_attr_list_.clear();
		version_dict_.clear();
	}

	// BeltHeader, BeltHeader_v1, 1 같이 특정 클래스에 묶이 이름을 등록해서 얻을수 잇도록하자
	// 이게 되야 버전업/다운을 할수 잇을거같다
	void setClassVersionInfo(const std::string &base_name, const std::string &class_name, int version) {
		auto version_pair = make_pair(class_name, version);
		version_dict_.insert(make_pair(base_name, version_pair));
	}

	bool isBaseClassExist(const std::string &base_name) const {
		auto found = version_dict_.find(base_name);
		return (found != version_dict_.end());
	}

	std::string getLatestClassName(const std::string &base_name) const {
		auto ret = version_dict_.equal_range(base_name);
		if (ret.first == version_dict_.end()) {
			static std::string empty;
			return empty;
		}
		std::string latest_name;
		int version = -1;
		for (auto it = ret.first; it != ret.second; ++it) {
			if (it->second.second > version) {
				latest_name = it->second.first;
				version = it->second.second;
			}
		}
		return latest_name;
	}

	bool isLatestClassName(const std::string &class_name) const {
		//version 정보에서 적절히 긁기
		auto it = version_dict_.begin();
		auto endit = version_dict_.end();
		int curr_version = -1;
		for (; it != endit; ++it) {
			if (it->second.first == class_name) {
				curr_version = it->second.second;
				break;
			}
		}
		assert(curr_version != -1);

		std::string lastest_name = getLatestClassName(it->first);
		if (lastest_name == it->second.first) {
			return true;
		}
		else {
			return false;
		}
	}

	//특정 base class에 특정 버전의 클래스 이름 얻기
	//이름 생성 규칙을 어딘가에 묶어서 할 경우
	//매크로라든가를 거칠때 귀찮을거같아서 완전히 분리함
	//못찾으면 빈 문자열
	std::string getClassName(const std::string &base_name, int version) const {
		auto ret = version_dict_.equal_range(base_name);
		if (ret.first == version_dict_.end()) {
			return std::string("");
		}
		for (auto it = ret.first; it != ret.second; ++it) {
			if (it->second.second == version) {
				return it->second.first;
			}
		}
		return std::string("");
	}


	//구현체 클래스 이름 얻기
	bool isClassExist(const std::string &class_name) const {
		auto it = version_dict_.begin();
		auto endit = version_dict_.end();
		for (; it != endit; ++it) {
			if (it->second.first == class_name) {
				return true;
			}
		}
		return false;
	}

	ClassAttribute *get(const std::string &class_name) {
		auto it = class_attr_list_.begin();
		auto endit = class_attr_list_.end();
		for (; it != endit; ++it) {
			if (it->class_name() == class_name) {
				return &(*it);
			}
		}
		return NULL;
	}

	ClassAttribute *get(unsigned int hash) {
		auto it = class_attr_list_.begin();
		auto endit = class_attr_list_.end();
		for (; it != endit; ++it) {
			if (it->hash() == hash) {
				return &(*it);
			}
		}
		return NULL;
	}

		
	const ClassAttribute *get(unsigned int hash) const {
		auto it = class_attr_list_.begin();
		auto endit = class_attr_list_.end();
		for (; it != endit; ++it) {
			if (it->hash() == hash) {
				return &(*it);
			}
		}
		return NULL;
	}

	const ClassAttribute *get(const std::string &class_name) const {
		auto it = class_attr_list_.begin();
		auto endit = class_attr_list_.end();
		for (; it != endit; ++it) {
			if (it->class_name() == class_name) {
				return &(*it);
			}
		}
		return NULL;
	}

	bool add(const ClassAttribute &class_attr) {
		auto it = class_attr_list_.begin();
		auto endit = class_attr_list_.end();
		for (; it != endit; ++it) {
			if (it->class_name() == class_attr.class_name()) {
				//같은 이름 클래스 추가 불가능
				return false;
			}
		}
		class_attr_list_.push_back(class_attr);
		//클래스 추가될때 정보를 기반으로 버전도 자체 설정
		setClassVersionInfo(class_attr.base_name(), class_attr.class_name(), class_attr.version());
		return true;
	}


	std::set<std::string> getBaseClassList() const {
		std::set<std::string> class_set;
		auto it = version_dict_.begin();
		auto endit = version_dict_.end();
		for (; it != endit; ++it) {
			class_set.insert(it->first);
		}
		return class_set;
	}

private:
	VersionDictType version_dict_;
	ClassAttributeListType class_attr_list_;
};

NAMESPACE_HIKARU_END

#endif