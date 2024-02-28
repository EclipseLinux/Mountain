#include "_deps/googletest-src/googletest/include/gtest/gtest.h"
#include "core/Application.h"

TEST(Layout, HandlesVerticalLayout)
{
	auto* ele = (new Mountain::Element())->Width(900)->Height(900);
	ele->AddChild<Mountain::Element>()->Width(300)->Height(300);
	ele->AddChild<Mountain::Element>()->Width(300)->Height(300);
	ele->AddChild<Mountain::Element>()->Width(300)->Height(300);

	Mountain::Application::main->Attach(ele);
	Mountain::Application::main->Present();

	EXPECT_EQ(ele->ToSExpression(),
			  "(Mountain::Element 900x900 0,0 (Mountain::Element 300x300 0,0) "
			  "(Mountain::Element 300x300 0,300) (Mountain::Element 300x300 0,600))")
		<< "Expected vertical layouts to be properly organized";

	Mountain::Application::Reset();
}

TEST(Layout, HandlesLeftPadding)
{
	auto* ele = (new Mountain::Element())->Width(900)->Height(900)->PaddingLeft(25);
	ele->AddChild<Mountain::Element>();

	Mountain::Application::main->Attach(ele);
	Mountain::Application::main->Present();

	EXPECT_EQ(ele->ToSExpression(),
			  "(Mountain::Element 900x900 0,0 (Mountain::Element 875x0 25,0))")
		<< "Expected left padding to be respected";

	Mountain::Application::Reset();
}

TEST(Layout, HandlesTopPadding)
{
	auto* ele = (new Mountain::Element())->Width(900)->Height(900)->PaddingTop(25);
	ele->AddChild<Mountain::Element>();

	Mountain::Application::main->Attach(ele);
	Mountain::Application::main->Present();

	EXPECT_EQ(ele->ToSExpression(),
			  "(Mountain::Element 900x900 0,0 (Mountain::Element 900x0 0,25))")
		<< "Expected top padding to be respected";

	Mountain::Application::Reset();
}