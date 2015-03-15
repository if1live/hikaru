// Ŭnicode please

#ifndef __HK_BASE_STRUCT_H__
#define __HK_BASE_STRUCT_H__

#include "hk_globals.h"
#include <string>

NAMESPACE_HIKARU_BEGIN

struct RSHash {
	static unsigned int Hash(const char *str) {
		unsigned int b = 378551;
		unsigned int a = 63689;
		unsigned int hash = 0;

		size_t length = strlen(str);
		for (size_t i = 0; i < length; i++) {
			hash = hash * a + str[i];
			a = a * b;
		}

		return (hash & 0x7FFFFFFF);
	}
};

class BaseStruct {
public:
	typedef hikaru::RSHash HashFunc;

	BaseStruct() : class_hash_(0), base_hash_(0) {}
	virtual ~BaseStruct() {}

	virtual BaseStruct *clone() const = 0;

protected:
	unsigned int class_hash_;	// class name based hash. unique value
	unsigned int base_hash_;	// parent hash. If group is same, parent hash are same.
};


NAMESPACE_HIKARU_END

#endif

