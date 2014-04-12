// Ŭnicode please
#include "hikaru_stdafx.h"
#include "data_init.h"
#include "data_define.h"

using namespace std;

//매크로 해제
#ifdef STRUCT_BEGIN
#undef STRUCT_BEGIN
#endif

#ifdef STRUCT_NEW_BEGIN
#undef STRUCT_NEW_BEGIN
#endif

#ifdef STRUCT_VAR
#undef STRUCT_VAR
#endif

#ifdef STRUCT_END
#undef STRUCT_END
#endif

#ifdef STRUCT_VAR_STR_ENUM_BEGIN
#undef STRUCT_VAR_STR_ENUM_BEGIN
#endif

#ifdef STRUCT_VAR_STR_ENUM_KEY
#undef STRUCT_VAR_STR_ENUM_KEY
#endif

#ifdef STRUCT_VAR_STR_ENUM_END
#undef STRUCT_VAR_STR_ENUM_END
#endif

#define INIT_FUNC_CALL(NAME, VERSION)   init_##NAME##_##VERSION();

#define STRUCT_BEGIN(NAME, VERSION)   INIT_FUNC_CALL(NAME, VERSION)
#define STRUCT_NEW_BEGIN(NAME, VERSION) INIT_FUNC_CALL(NAME, VERSION)
#define STRUCT_VAR(A, B)
#define STRUCT_END()
#define STRUCT_VAR_STR_ENUM_BEGIN(A)
#define STRUCT_VAR_STR_ENUM_KEY(A)
#define STRUCT_VAR_STR_ENUM_END()

namespace hikaru {;
void init_generated_struct_data() {
#include "data_file.h"
}
}