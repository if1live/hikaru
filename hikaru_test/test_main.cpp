// Ŭnicode please
#include "hikaru_test_stdafx.h"
#include "data_define.h"

int main(int argc, char *argv[]) {
  // init rtti data
  init_SampleData_1();
  init_SampleData_2();

  ::testing::InitGoogleTest(&argc, argv);
	int result = RUN_ALL_TESTS();

  getchar();
	return result;
}
