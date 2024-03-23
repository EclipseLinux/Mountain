#include "components/Text.h"
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

	win->AddChild<Components::Text>()
		->Content("Hello world!")
		->FontSize(48)
		->GetFilter<Filters::BackgroundColor>()
		->BgColor(ThemeManager::Primary());

	app->Present();

	delete app;
	return 0;
}