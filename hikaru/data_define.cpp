// Ŭnicode please
#include "hikaru_stdafx.h"
#include "data_define.h"
#include "class_dict.h"
#include "class_attribute.h"

using namespace hikaru;
using namespace std;

bool init_SampleData_1() {
  static bool run = false;
  if(run == true) {
    return false;
  }
  run = true;
  
  typedef SampleData_family<1> DataClass;
  auto typeinfo = TypeInfo<DataClass>();
  ClassAttribute *class_attr = new ClassAttribute(typeinfo);

  {
    int offset = offsetof(DataClass, int_value);
    MemberAttribute attr = MemberAttribute::Create("int_value", offset, MemberType2Type<int>());
    class_attr->AddMember(attr);
  }

  ClassDict::GetInstance().Register(class_attr);
  return true;
}

bool init_SampleData_2()
{
  static bool run = false;
  if(run == true) {
    return false;
  }
  run = true;
  

  typedef SampleData_family<2> DataClass;
  auto typeinfo = TypeInfo<DataClass>();
  ClassAttribute *class_attr = new ClassAttribute(typeinfo);
  bool is_latest = true;

  {
    int offset = offsetof(DataClass, float_value);
    MemberAttribute attr = MemberAttribute::Create("float_value", offset, MemberType2Type<float>());
    class_attr->AddMember(attr);
  }
  {
    int offset = offsetof(DataClass, str_enum);
    MemberAttribute attr = MemberAttribute::StringEnum("str_enum", offset);
    attr.AddStringEnum("a");
    attr.AddStringEnum("b");
    class_attr->AddMember(attr);
  }
  ClassDict::GetInstance().Register(class_attr);
  if(is_latest) {
    ClassDict::GetInstance().SetLatestVersion(class_attr->family_name(), class_attr->version());
  }
  return true;
}

//기존매크로 해제
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

//매크로 재정의
#define DEFINE_BEGIN(NAME, VERSION) \
  bool init_##NAME##_##VERSION() { \
  static bool run = false;  \
  if(run == true) { return false; } \
  run = true; \
  typedef NAME##_family<VERSION> DataClass; \
  auto typeinfo = TypeInfo<DataClass>(); \
  ClassAttribute *class_attr = new ClassAttribute(typeinfo); \
  bool is_latest = false; \


#define DEFINE_NEW_BEGIN(NAME, VERSION) \
  bool init_##NAME##_##VERSION() { \
  static bool run = false;  \
  if(run == true) { return false; } \
  run = true; \
  typedef NAME##_family<VERSION> DataClass; \
  auto typeinfo = TypeInfo<DataClass>(); \
  ClassAttribute *class_attr = new ClassAttribute(typeinfo); \
  bool is_latest = true; \

#define DEFINE_VAR(TYPE, NAME)  \
  { \
    int offset = offsetof(DataClass, NAME); \
    MemberAttribute attr = MemberAttribute::Create(#NAME, offset, MemberType2Type<TYPE>()); \
    class_attr->AddMember(attr); \
  }

#define DEFINE_END()  \
  ClassDict::GetInstance().Register(class_attr);  \
  if(is_latest) { \
    ClassDict::GetInstance().SetLatestVersion(class_attr->family_name(), class_attr->version()); \
  } \
  return true; \
  }

#define DEFINE_VAR_STR_ENUM_BEGIN(NAME) \
  { \
    int offset = offsetof(DataClass, NAME); \
    MemberAttribute attr = MemberAttribute::StringEnum(#NAME, offset); 
    

#define DEFINE_VAR_STR_ENUM_KEY(KEY)    attr.AddStringEnum(#KEY);

#define DEFINE_VAR_STR_ENUM_END()   class_attr->AddMember(attr); }


//매크로 다시 연결
#define STRUCT_BEGIN    DEFINE_BEGIN
#define STRUCT_NEW_BEGIN    DEFINE_NEW_BEGIN
#define STRUCT_VAR    DEFINE_VAR
#define STRUCT_END    DEFINE_END
#define STRUCT_VAR_STR_ENUM_BEGIN   DEFINE_VAR_STR_ENUM_BEGIN
#define STRUCT_VAR_STR_ENUM_KEY   DEFINE_VAR_STR_ENUM_KEY
#define STRUCT_VAR_STR_ENUM_END   DEFINE_VAR_STR_ENUM_END

#include "data_file.h"