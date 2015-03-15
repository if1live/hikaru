// Ŭnicode please

#ifndef __HK_ATTRIBUTE_H__
#define __HK_ATTRIBUTE_H__

#include "hk_globals.h"
#include <cstring>
#include <string>
#include <memory>
#include <vector>

NAMESPACE_HIKARU_BEGIN

class Attribute {
	public:
		Attribute(const char *name, attribute_t type, int offset)
			: name_(name), type_(type), offset_(offset) { }
		Attribute() : name_(""), type_(HK_ATTRIBUTE_NONE), offset_(0) {}

		~Attribute() {}

		const std::string &name() const { return name_; }
		int offset() const { return offset_; }
		attribute_t type() const { return type_; }

	private:
		int offset_;
		attribute_t type_;
		std::string name_;

		// factory
	public:
#define ATTRIBUTE_FACTORY(NAME, TYPE) \
	static Attribute NAME(const char *name, int offset) {	\
		return Attribute(name, TYPE, offset);	\
		}

		ATTRIBUTE_FACTORY(createInt, HK_ATTRIBUTE_INT)
		ATTRIBUTE_FACTORY(createBool, HK_ATTRIBUTE_BOOL)
		ATTRIBUTE_FACTORY(createFloat, HK_ATTRIBUTE_FLOAT)
		ATTRIBUTE_FACTORY(createString, HK_ATTRIBUTE_STRING)

#undef ATTRIBUTE_FACTORY

};



class ClassAttribute {
public:
	typedef std::vector<Attribute> attribute_list_t;
	typedef attribute_list_t::iterator iterator;
	typedef attribute_list_t::const_iterator const_iterator;
public:
	ClassAttribute(const char *base_name, const char *class_name, int version)
		: base_name_(base_name),
		class_name_(class_name),
		version_(version) {	}

	~ClassAttribute() {
		//class dict에 등록된 다음에는 소멸자/생성자가 추적 불가능하니까 해제를 하지 말자
		//어차피 클래스는 1회 등록된 다음에 안생길테니까 큰 문제는 없을것이다
	}

	unsigned int hash() const {
		return RSHash::Hash(class_name_.data());
	}
		
	void set_prototype(BaseStruct *data) {
		prototype_.reset(data);
	}

	const std::string &base_name() const { return base_name_; }
	const std::string &class_name() const { return class_name_; }
	int version() const { return version_; }

	BaseStruct *clone() const {
		if (prototype_.get() != NULL) {
			return prototype_->clone();
		}
		return NULL;
	}

	//attribute등록 + 검색
	bool add(const Attribute &attr) {
		if (isAttributeExist(attr.name()) == false) {
			attr_list_.push_back(attr);
			return true;
		}
		else {
			return false;
		}
	}

	bool isAttributeExist(const std::string &attr_name) const {
		auto it = attr_list_.begin();
		auto endit = attr_list_.end();
		for (; it != endit; ++it) {
			if (it->name() == attr_name) {
				return true;
			}
		}
		return false;
	}

	Attribute *get(const std::string &attr_name) {
		auto it = attr_list_.begin();
		auto endit = attr_list_.end();
		for (; it != endit; ++it) {
			if (it->name() == attr_name) {
				return &(*it);
			}
		}
		return NULL;
	}
	int count() const { return attr_list_.size(); }

	const_iterator begin() const { return attr_list_.begin(); }
	const_iterator end() const { return attr_list_.end(); }
	iterator begin() { return attr_list_.begin(); }
	iterator end() { return attr_list_.end(); }

private:
	std::string base_name_;
	std::string class_name_;
	int version_;

	std::shared_ptr<BaseStruct> prototype_;

	attribute_list_t attr_list_;
};

NAMESPACE_HIKARU_END

#endif