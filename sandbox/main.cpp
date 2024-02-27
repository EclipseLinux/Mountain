#include "core/Application.h"
#include "core/Element.h"

auto main(int argc, const char** argv) -> int
{
	auto* app = new Mountain::Application("com.eclipse.sandbox");

	auto* ele = new Mountain::Element();
	ele->AddChild<Mountain::Element>();

	delete app;
	return 0;
}