#include "_deps/googletest-src/googletest/include/gtest/gtest.h"
#include "core/Application.h"

int main(int argc, const char** argv)
{
	testing::InitGoogleTest();
	auto* app = new Mountain::Application("internal.tests");
	auto result = RUN_ALL_TESTS();

	delete app;

	return result;
}