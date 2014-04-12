// Ŭnicode please
STRUCT_BEGIN(DemoStruct, 1)
  STRUCT_VAR(int, int_value)
STRUCT_END()

STRUCT_NEW_BEGIN(DemoStruct, 2)
  STRUCT_VAR(int, int_value)
  STRUCT_VAR(bool, bool_value)
STRUCT_END()

STRUCT_NEW_BEGIN(EnumStruct, 1)
  STRUCT_VAR_STR_ENUM_BEGIN(key_name)
    STRUCT_VAR_STR_ENUM_KEY(simple)
    STRUCT_VAR_STR_ENUM_KEY(complex)
  STRUCT_VAR_STR_ENUM_END()
STRUCT_END()
