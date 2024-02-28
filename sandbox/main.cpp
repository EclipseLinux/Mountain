#include "core/Application.h"
#include "core/Element.h"

auto main(int argc, const char** argv) -> int
{
	auto* app = new Mountain::Application("com.eclipse.sandbox");

	auto* ele = new Mountain::Element();
	auto* ele2 = ele->AddChild<Mountain::Element>();

	ele2->AddChild<Mountain::Element>();

	ele->Print();
	mn_info(ele->ToSExpression());

	delete app;
	return 0;
}