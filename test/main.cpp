// Ŭnicode please 
#include <gtest/gtest.h>
#include "data_init.h"

int main(int argc, char *argv[])
{
	init_generated_data();

	::testing::InitGoogleTest(&argc, argv);
	int result = RUN_ALL_TESTS();
	getchar();
	return result;
}
