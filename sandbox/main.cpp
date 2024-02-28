#include "core/Application.h"
#include "core/Element.h"

using namespace Mountain;

auto main(int argc, const char** argv) -> int
{
	auto* app = new Mountain::Application("com.eclipse.sandbox");

	auto* ele = (new Element())
					->Width(900)
					->Height(900)
					->Gap(200)
					->FlexDirection(Layout::FlexDirection::Column)
					->JustifyContent(Layout::JustifyContent::Center)
					->AlignItems(Layout::AlignItems::Center);

	auto* first = ele->AddChild<Element>()
					  ->FlexDirection(Layout::FlexDirection::Column)
					  ->Gap(60)
					  ->Width(0)
					  ->Height(0)
					  ->JustifyContent(Layout::JustifyContent::Center)
					  ->AlignItems(Layout::AlignItems::Center);

	ele->AddChild<Element>()->Width(400)->Height(75);

	first->AddChild<Element>()->Width(75)->Height(75);
	first->AddChild<Element>()->Width(400)->Height(100);

	app->Attach(ele);
	app->Present();

	ele->Print();

	delete app;
	return 0;
}