// Ŭnicode please
#include "hikaru_test_stdafx.h"
#include "data_define.h"

#include "data_init.h"

int main(int argc, char *argv[]) {
  // init rtti data
  init_SampleData_1();
  init_SampleData_2();

  //auto gen function
  //bool a = init_DemoStruct_1();
  //bool b = init_DemoStruct_2();
  //bool c = init_EnumStruct_1();
  hikaru::init_generated_struct_data();

  ::testing::InitGoogleTest(&argc, argv);
	int result = RUN_ALL_TESTS();

  getchar();
	return result;
}
