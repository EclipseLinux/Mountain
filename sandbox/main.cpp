#include "components/Image.h"
#include "core/Application.h"
#include "core/Filter.h"
#include "core/LayoutEnums.h"
#include "utils/ThemeManager.h"

using namespace Mountain;

auto main(int argc, const char** argv) -> int
{
	auto* app = new Mountain::Application("com.eclipse.sandbox");

	auto* win = app->CreateWindow("Sandbox", 800, 600)
					->BackgroundColor(ThemeManager::Background())
					->JustifyContent(Layout::JustifyContent::Center)
					->AlignItems(Layout::AlignItems::Center);

	auto* btn =
		win->AddChild<Components::Image>()
			->Content("ts.png")
			->Width(300)
			->Height(50)
			->AddFilter<Filters::BackgroundColor>(ThemeManager::Primary())
			->AddFilter<Filters::BorderRadius>(25)
			->AddFilter<Filters::BackdropShadow>(4, 4, 24, Color(0, 0, 0, 128));

	app->Present();

	delete app;
	return 0;
}