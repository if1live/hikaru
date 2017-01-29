#ifndef __HK_DECLARATION_H__
#define __HK_DECLARATION_H__

// HIKARU_DEV

// 하나라도 정의되어있다는건 나머지도 있다는거겠지
#ifdef HK_STRUCT_NEW_BEGIN
#undef HK_STRUCT_NEW_BEGIN
#undef HK_STRUCT_BEGIN
#undef HK_STRUCT_VAR_INT
#undef HK_STRUCT_VAR_FLOAT
#undef HK_STRUCT_END
#endif


#define HK_STRUCT_NEW_BEGIN(BASE, VERSION)	\
	struct		BASE##_##VERSION;	\
	typedef		BASE##_##VERSION	BASE;	\
	HK_STRUCT_BEGIN(BASE, VERSION)


#if HIKARU_DEV
struct HKDemoStruct : public hikaru::BaseStruct {
    HKDemoStruct() {
        class_hash_ = ClassHash();
        base_hash_ = BaseHash();
    }
    ~HKDemoStruct() {}
    virtual BaseStruct *clone() const { return new HKDemoStruct(); }
    static unsigned int ClassHash() {
        static bool init = false;
        static unsigned int hash_value = 0;
        if (init == false) {
            init = true;
            const std::string base_name("BASE");
            const std::string version_str("VERSION");
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
#endif

#define HK_STRUCT_BEGIN(BASE, VERSION)  \
    struct BASE##_##VERSION : public hikaru::BaseStruct {   \
    BASE##_##VERSION() {    \
        class_hash_ = ClassHash();  \
        base_hash_ = BaseHash();    \
    }   \
    ~BASE##_##VERSION() {}  \
    virtual BASE##_##VERSION *clone() const { return new BASE##_##VERSION(); }  \
    static unsigned int ClassHash() { \
        static bool init = false;   \
        static unsigned int hash_value = 0; \
        if (init == false) { \
            init = true;    \
            const std::string base_name(#BASE);    \
            const std::string version_str(#VERSION);   \
            std::string class_name = base_name + "_" + version_str; \
            hash_value = hikaru::BaseStruct::HashFunc::Hash(class_name.data()); \
        }   \
       return hash_value;  \
    }   \
    static unsigned int BaseHash() {    \
        static bool init = false;   \
        static unsigned int hash_value = 0; \
        if (init == false) { \
            init = true;    \
            hash_value = hikaru::BaseStruct::HashFunc::Hash(#BASE);    \
        }   \
        return hash_value;  \
    }

#if HIKARU_DEV
    /**{{ STRUCT_VAR_INT(INT_NAME) */
    int int_val;
    /**}} */
#endif
#define HK_STRUCT_VAR_INT(NAME) int NAME;

#if HIKARU_DEV
    /**{{ STRUCT_VAR_FLOAT(FLOAT_NAME) */
    float float_val;
    /**}} */
#endif
#define HK_STRUCT_VAR_FLOAT(NAME) float NAME;

#if HIKARU_DEV
    /**{{ STRUCT_VAR_BOOL(BOOL_NAME) */
    bool bool_val;
    /**}} */
#endif
#define HK_STRUCT_VAR_BOOL(NAME) bool NAME;

#if HIKARU_DEV
    /**{{ STRUCT_END() */
    };
    /**}} */
#endif
#define HK_STRUCT_END() };


#endif
