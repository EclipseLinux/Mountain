#include "core/Application.h"

using namespace Mountain;

auto main(int argc, const char** argv) -> int
{
	auto* app = new Mountain::Application("com.eclipse.sandbox");

	auto* win = app->CreateWindow("Sandbox", 800, 600);

	app->Present();

	win->Print();

	delete app;
	return 0;
}