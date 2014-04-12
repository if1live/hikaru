﻿// Ŭnicode please
#include "data_define.h"
#include "class_attribute.h"

using namespace std;
using namespace qb;

/// begin macro 
#undef STRUCT_BEGIN
#undef STRUCT_NEW_BEGIN
#undef STRUCT_END
#undef STRUCT_VAR_INT
#undef STRUCT_VAR_FLOAT
#undef STRUCT_VAR_STR_ENUM_BEGIN
#undef STRUCT_VAR_STR_ENUM_KEY
#undef STRUCT_VAR_STR_ENUM_END
#undef STRUCT_VAR_BOOL
#undef STRUCT_VAR_STRING
#undef STRUCT_VAR_VEC2
#undef STRUCT_VAR_STRING_LIST
#undef STRUCT_VAR_VEC2_LIST

#define CLASS_NAME(A, B) A##_v##B
#define JOIN_STR(A, B)	A##B
#define TO_STRING(A) #A

#define STRUCT_BEGIN(BASE, VERSION)	\
bool init_##BASE##_v##VERSION()	\
	{	\
	static bool run = false;	\
	if(run == true) {	\
		return false;	\
	}	\
	run = true;	\
	std::string base_name = #BASE;	\
	std::string version_str = #VERSION;	\
	std::string class_name = base_name + "_v" + version_str;	\
	qb::ClassAttribute class_attr(#BASE, class_name.c_str(), VERSION);	\
	class_attr.set_prototype(new BASE##_v##VERSION());	\
	typedef BASE##_v##VERSION DataClass;

#define STRUCT_NEW_BEGIN(BASE, VERSION)		STRUCT_BEGIN(BASE, VERSION)

#define STRUCT_END()	\
	qb::ClassDict::GetInstance().Add(class_attr);	\
	return true;	\
	}
#define STRUCT_VAR_INT(NAME)	{\
		int offset = offsetof(DataClass, NAME);	\
		qb::Attribute attr = qb::Attribute::Int(#NAME, offset);	\
		class_attr.Add(attr);	\
	}

#define STRUCT_VAR_FLOAT(NAME)	{\
		int offset = offsetof(DataClass, NAME);	\
		qb::Attribute attr = qb::Attribute::Float(#NAME, offset);	\
		class_attr.Add(attr);	\
	}

#define STRUCT_VAR_BOOL(NAME)	{\
		int offset = offsetof(DataClass, NAME);	\
		qb::Attribute attr = qb::Attribute::Bool(#NAME, offset);	\
		class_attr.Add(attr);	\
	}
#define STRUCT_VAR_STRING(NAME)	{\
		int offset = offsetof(DataClass, NAME);	\
		qb::Attribute attr = qb::Attribute::String(#NAME, offset);	\
		class_attr.Add(attr);	\
	}
#define STRUCT_VAR_VEC2(NAME)	{\
		int offset = offsetof(DataClass, NAME);	\
		qb::Attribute attr = qb::Attribute::Vec2(#NAME, offset);	\
		class_attr.Add(attr);	\
	}
#define STRUCT_VAR_STRING_LIST(NAME)	{\
		int offset = offsetof(DataClass, NAME);	\
		qb::Attribute attr = qb::Attribute::StringList(#NAME, offset);	\
		class_attr.Add(attr);	\
	}
#define STRUCT_VAR_VEC2_LIST(NAME)	{\
		int offset = offsetof(DataClass, NAME);	\
		qb::Attribute attr = qb::Attribute::Vec2List(#NAME, offset);	\
		class_attr.Add(attr);	\
	}

#define STRUCT_VAR_STR_ENUM_BEGIN(NAME) { \
	int offset = offsetof(DataClass, NAME);	\
	qb::Attribute attr = qb::Attribute::StringEnum(#NAME, offset);
#define STRUCT_VAR_STR_ENUM_KEY(KEY)	\
	attr.AddStringEnum(#KEY);
#define STRUCT_VAR_STR_ENUM_END()	class_attr.Add(attr); }


/// end macro
#include "data_file.h"

//bool init_SampleData_v1();
//bool init_SampleData_v1_result = init_SampleData_v1();
bool init_SampleData_v1()
{
	static bool run = false;
	if(run == true) {
		return false;
	}
	run = true;

	ClassAttribute class_attr("SampleData", "SampleData_v1", 1);
	typedef SampleData_v1 DataClass;

	{
		int offset = offsetof(DataClass, int_value);
		qb::Attribute attr = qb::Attribute::Int("int_value", offset);
		class_attr.Add(attr);
	}
	qb::ClassDict::GetInstance().Add(class_attr);

	return true;
}

//bool init_SampleData_v2();
//bool init_SampleData_v2_result = init_SampleData_v2();
bool init_SampleData_v2()
{
	static bool run = false;
	if(run == true) {
		return false;
	}
	run = true;

	ClassAttribute class_attr("SampleData", "SampleData_v2", 2);
	typedef SampleData_v2 DataClass;

	{
		int offset = offsetof(DataClass, float_value);
		qb::Attribute attr = qb::Attribute::Float("float_value", offset);
		class_attr.Add(attr);
	}
	{
		int offset = offsetof(DataClass, str_enum);
		qb::Attribute attr = qb::Attribute::StringEnum("str_enum", offset);
		attr.AddStringEnum("a");
		attr.AddStringEnum("b");
		class_attr.Add(attr);
	}
	qb::ClassDict::GetInstance().Add(class_attr);
	return true;
}
