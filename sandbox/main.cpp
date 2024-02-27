#include "core/Application.h"
#include "core/Logger.h"
auto main(int argc, const char** argv) -> int
{
	auto* app = new Mountain::Application("com.eclipse.sandbox");

	mn_coreDebug("Hi");
	delete app;

	return 0;
}