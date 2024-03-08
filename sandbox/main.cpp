#include "core/Application.h"
#include "core/Filter.h"
#include "core/LayoutEnums.h"

using namespace Mountain;

auto main(int argc, const char** argv) -> int
{
	auto* app = new Mountain::Application("com.eclipse.sandbox");

	auto* win = app->CreateWindow("Sandbox", 800, 600)
					->BackgroundColor(Color())
					->JustifyContent(Layout::JustifyContent::Center)
					->AlignItems(Layout::AlignItems::Center);

	auto* btn = win->AddChild<Element>()
					->Width(300)
					->Height(50)
					->AddFilter<Filters::BackgroundColor>(0x9e54f7ff)
					->AddFilter<Filters::BorderRadius>(25)
					->AddFilter<Filters::BackdropShadow>(4, 4, 24, Color(0, 0, 0, 128))
					->On("click", [=](auto element) { mn_info("Hi!"); });

	app->Present();

	delete app;
	return 0;
}