// Ŭnicode please
#pragma once

#include "util.h"
#include <string>
#include <vector>
#include "class_attribute.h"

namespace hikaru {;
struct BaseData {
  typedef hikaru::RSHash HashFunction;
  BaseData(unsigned int class_code)
    : class_code_(class_code) {}
  virtual ~BaseData() {}

  unsigned int class_code() const { return class_code_; }

private:
  unsigned int class_code_;
};
}

//매크로에 의해서 풀어진 결과클래스를 풀어서 쓴 형태
//매크로에 의해서 생성되는 클래스는 <Name>_family이다
//<Name>이라고 바로 쓰지 않은 이유는 가장 최신버전의 클래스에 대해서
//typedef가 걸리는 이름과 충돌되기때문
template<int> struct SampleData_family;
bool init_SampleData_1();

template<>
struct SampleData_family<1> : public hikaru::BaseData {
  //클래스 생성하면 같이 생성되는 부분
  static const char *FamilyName() { static const char *name = "SampleData"; return name; }
  enum { version = 1 };
  static unsigned int ClassCode() { static const char *name = "SampleData""1"; return (unsigned int)name; }

  SampleData_family() : BaseData(ClassCode()) {}
  ~SampleData_family() {}
  
  int int_value;
};

bool init_SampleData_2();
template<> struct SampleData_family<2>;
typedef SampleData_family<2> SampleData;

template<> 
struct SampleData_family<2> : public hikaru::BaseData {
  static const char *FamilyName() { static const char *name = "SampleData"; return name; }
  enum { version = 2 };
  static unsigned int ClassCode() { static const char *name = "SampleData""2"; return (unsigned int)name; }

  SampleData_family() : BaseData(ClassCode()) {}
  ~SampleData_family() {}
  
  float float_value;
  std::string str_enum;
};

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


//실제로 쓰이는 매크로
#define DECLARE_BEGIN(NAME, VERSION) \
  bool init_##NAME##_##VERSION(); \
  template<int> struct NAME##_family; \
  template<> struct NAME##_family<VERSION>; \
  template<> struct NAME##_family<VERSION> : public hikaru::BaseData { \
  static const char *FamilyName() { static const char *name = #NAME; return name; } \
    enum { version = VERSION }; \
    static unsigned int ClassCode() { static const char *name = #NAME; return (unsigned int)name; } \
    NAME##_family() : BaseData(ClassCode()) {} \
    ~NAME##_family() {}

#define DECLARE_NEW_BEGIN(NAME, VERSION) \
  template<int> struct NAME##_family; \
  template<> struct NAME##_family<VERSION>; \
  typedef NAME##_family<VERSION> NAME;  \
  DECLARE_BEGIN(NAME, VERSION)
  
#define DECLARE_VAR(TYPE, NAME)   TYPE NAME;
#define DECLARE_END() };
#define DECLARE_VAR_STR_ENUM_BEGIN(NAME)  std::string NAME;

//재정의한거 서로 연결
#define STRUCT_BEGIN    DECLARE_BEGIN
#define STRUCT_NEW_BEGIN    DECLARE_NEW_BEGIN
#define STRUCT_VAR    DECLARE_VAR
#define STRUCT_END    DECLARE_END
#define STRUCT_VAR_STR_ENUM_BEGIN   DECLARE_VAR_STR_ENUM_BEGIN
#define STRUCT_VAR_STR_ENUM_KEY(NAME)
#define STRUCT_VAR_STR_ENUM_END()

#include "data_file.h"