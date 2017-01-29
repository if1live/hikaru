#ifndef __HK_DEFINITION_H__
#define __HK_DEFINITION_H__

// HIKARU_DEV

#ifdef HK_STRUCT_NEW_BEGIN
#undef HK_STRUCT_NEW_BEGIN
#undef HK_STRUCT_BEGIN
#undef HK_STRUCT_VAR_INT
#undef HK_STRUCT_VAR_FLOAT
#undef HK_STRUCT_END
#endif


#define HK_STRUCT_NEW_BEGIN(BASE, VERSION)  HK_STRUCT_BEGIN(BASE, VERSION)

#if HIKARU_DEV 
{ 
typedef HKDemoStruct cls;
hikaru::ClassAttribute class_attr("HKDemoStruct", "HKDemoStruct", 1);
#endif
#define HK_STRUCT_BEGIN(BASE, VERSION)  {   \
    typedef BASE##_##VERSION cls;   \
    hikaru::ClassAttribute class_attr(#BASE, #BASE "_" #VERSION, VERSION);
#if HIKARU_DEV
    class_attr.add(hikaru::FieldAttribute::createInt("int_val", offsetof(cls, int_val)));
#endif
#define HK_STRUCT_VAR_INT(NAME) \
    class_attr.add(hikaru::FieldAttribute::createInt(#NAME, offsetof(cls, NAME)));

#if HIKARU_DEV
    class_attr.add(hikaru::FieldAttribute::createFloat("float_val", offsetof(cls, float_val)));
#endif
#define HK_STRUCT_VAR_FLOAT(NAME)   \
    class_attr.add(hikaru::FieldAttribute::createFloat(#NAME, offsetof(cls, NAME)));

#if HIKARU_DEV 
    hikaru::ClassDict::getInstance().add(class_attr);
}
#endif
#define HK_STRUCT_END() \
    hikaru::ClassDict::getInstance().add(class_attr);   \
}

#endif  // __HK_DEFINITION_H__
