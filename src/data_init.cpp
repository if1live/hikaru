// Ŭnicode please
#include "data_init.h"

#include "data_define.h"

//자동생성 데이터를 초기화하는데 쓰는매크로
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

#define STRUCT_BEGIN(BASE, VERSION)	\
	bool run_##BASE##_v##VERSION = init_##BASE##_v##VERSION();
#define STRUCT_NEW_BEGIN(BASE, VERSION)	STRUCT_BEGIN(BASE, VERSION)
#define STRUCT_END()
#define STRUCT_VAR_INT(NAME)
#define STRUCT_VAR_FLOAT(NAME)
#define STRUCT_VAR_STR_ENUM_BEGIN(NAME)
#define STRUCT_VAR_STR_ENUM_KEY(KEY)
#define STRUCT_VAR_STR_ENUM_END()

#define STRUCT_VAR_BOOL(NAME)
#define STRUCT_VAR_STRING(NAME)
#define STRUCT_VAR_VEC2(NAME)
#define STRUCT_VAR_STRING_LIST(NAME)
#define STRUCT_VAR_VEC2_LIST(NAME)

void init_generated_data()
{
	#include "data_file.h"
}
