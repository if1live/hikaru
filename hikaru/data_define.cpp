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