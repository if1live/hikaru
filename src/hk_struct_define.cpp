// Ŭnicode please

#include "hk_struct_define.h"


using namespace hikaru;

#undef STRUCT_NEW_BEGIN
#undef STRUCT_BEGIN
#undef STRUCT_END
#undef STRUCT_VAR_INT
#undef STRUCT_VAR_FLOAT
#undef STRUCT_VAR_BOOL
#undef STRUCT_VAR_STRING

/**{{ STRUCT_BEGIN(BASE, VERSION) */
#ifndef VERSION
// class attribute need integer version
#define VERSION 1
#endif

bool init_BASE_VERSION()
{
	static bool run = false;
	if (run == true) {
		return false;
	}
	run = true;
	std::string base_name = "BASE";
	std::string version_str = "VERSION";
	std::string class_name = base_name + "_" + version_str;
	ClassAttribute class_attr(base_name.data(), class_name.data(), VERSION);
	class_attr.set_prototype(new BASE_VERSION());
	typedef BASE_VERSION DataStruct;
/**}} */

/**{{ STRUCT_VAR_INT(INT_NAME) */
	{
		int offset = offsetof(DataStruct, INT_NAME);
		Attribute attr = Attribute::createInt("INT_NAME", offset);
		class_attr.add(attr);
	}
/**}} */

/**{{ STRUCT_VAR_FLOAT(FLOAT_NAME) */
	{
		int offset = offsetof(DataStruct, FLOAT_NAME);
		Attribute attr = Attribute::createFloat("FLOAT_NAME", offset);
		class_attr.add(attr);
	}
/**}} */

/**{{ STRUCT_VAR_BOOL(BOOL_NAME) */
	{
		int offset = offsetof(DataStruct, BOOL_NAME);
		Attribute attr = Attribute::createBool("BOOL_NAME", offset);
		class_attr.add(attr);
	}
/**}} */

/**{{ STRUCT_VAR_STRING(STRING_NAME) */
	{
		int offset = offsetof(DataStruct, STRING_NAME);
		Attribute attr = Attribute::createString("STRING_NAME", offset);
		class_attr.add(attr);
	}
/**}} */

/**{{ STRUCT_END() */
	ClassDict::getInstance().add(class_attr);
	return true;
}
/**}} */
