#include <cstdio>

#include "hikaru.h"
#include "hk_declaration.h"
#include "struct_data.txt"

int init_hikaru() {
    #include "hk_definition.h"
    #include "struct_data.txt"
    return 0;
}
static int initialized_hikaru = init_hikaru();

void demo_access_latest_class() {
    unsigned char data[256];
    auto dict = hikaru::ClassDict::getInstance();
    auto classname = dict.getLatestClassName("HKDemoStruct");
    auto classattr = dict.get(classname);
    for (auto it = classattr->begin(); it != classattr->end(); it++) {
        if (it->type() == hikaru::AttributeType::Int) {
            int int_val = 12;
            memcpy(data + it->offset(), &int_val, sizeof(int_val));
        }
        if (it->type() == hikaru::AttributeType::Float) {
            float float_val = 3.4f;
            memcpy(data + it->offset(), &float_val, sizeof(float_val));
        }
    }

    auto foo = reinterpret_cast<HKDemoStruct*>(data);
    printf("%d %f\n", foo->int_val, foo->float_val);
}

void demo_rtti() {
    auto dict = hikaru::ClassDict::getInstance();
    auto classname = dict.getClassName("HKDemoStruct", 1);
    auto classattr = dict.get(classname);

    printf("class name : %s\n", classattr->class_name().data());
    printf("base name : %s\n", classattr->base_name().data());
    printf("class version : %d\n", classattr->version());
    for (auto it = classattr->begin(); it != classattr->end(); it++) {
        printf("field : name=%s type=%d offset=%d\n", it->name().data(), it->type(), it->offset());
    }
}

int main() {
    demo_access_latest_class();
    demo_rtti();

    return 0;
}
