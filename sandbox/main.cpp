#include "core/Application.h"
#include "core/Element.h"

auto main(int argc, const char** argv) -> int
{
	auto* app = new Mountain::Application("com.eclipse.sandbox");

	auto* ele = (new Mountain::Element())->Width(900)->Height(900);
	ele->AddChild<Mountain::Element>()->Width(300)->Height(300);
	ele->AddChild<Mountain::Element>()->Width(300)->Height(300);
	ele->AddChild<Mountain::Element>()->Width(300)->Height(300);

	app->Attach(ele);
	app->Present();

	ele->Print();

	delete app;
	return 0;
}