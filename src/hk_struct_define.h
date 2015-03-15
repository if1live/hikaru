// Ŭnicode please

#ifndef __HK_STRUCT_DEFINE_H__
#define __HK_STRUCT_DEFINE_H__

#include "hikaru.h"

NAMESPACE_HIKARU_BEGIN

#undef STRUCT_NEW_BEGIN
#undef STRUCT_BEGIN
#undef STRUCT_END
#undef STRUCT_VAR_INT
#undef STRUCT_VAR_FLOAT
#undef STRUCT_VAR_BOOL
#undef STRUCT_VAR_STRING

#define STRUCT_NEW_BEGIN(BASE, VERSION)	\
	struct		BASE##_##VERSION;	\
	typedef		BASE##_##VERSION	BASE;	\
	STRUCT_BEGIN(BASE, VERSION)

/**{{ STRUCT_BEGIN(BASE, VERSION) */
bool init_BASE_VERSION();

struct BASE_VERSION : public BaseStruct {
	BASE_VERSION() {
		class_hash_ = ClassHash();
		base_hash_ = BaseHash();
	}
	~BASE_VERSION() {}
	virtual BaseStruct *clone() const {
		return new BASE_VERSION();
	}
	static unsigned int ClassHash() {
		static bool init = false;
		static unsigned int hash_value = 0;
		if (init == false) {
			init = true;
			std::string base_name = "BASE";
			std::string version_str = "VERSION";
			std::string class_name = base_name + "_" + version_str;
			hash_value = BaseStruct::HashFunc::Hash(class_name.data());
		}
		return hash_value;
	}
	static unsigned int BaseHash() {
		static bool init = false;
		static unsigned int hash_value = 0;
		if (init == false) {
			init = true;
			hash_value = BaseStruct::HashFunc::Hash("BASE");
		}
		return hash_value;
	}
/**}} */

/**{{ STRUCT_VAR_INT(INT_NAME) */
	int INT_NAME;
/**}} */

/**{{ STRUCT_VAR_FLOAT(FLOAT_NAME) */
	float FLOAT_NAME;
/**}} */

/**{{ STRUCT_VAR_BOOL(BOOL_NAME) */
	bool BOOL_NAME;
/**}} */

/**{{ STRUCT_VAR_STRING(STRING_NAME) */
	std::string STRING_NAME;
/**}} */

/**{{ STRUCT_END() */
};
/**}} */

NAMESPACE_HIKARU_END

#endif