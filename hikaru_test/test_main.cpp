// Ŭnicode please
#include "hikaru_test_stdafx.h"

int main(int argc, char *argv[]) {
  // init rtti data

  ::testing::InitGoogleTest(&argc, argv);
	int result = RUN_ALL_TESTS();

  getchar();
	return result;
}
