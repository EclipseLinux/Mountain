#include "_deps/googletest-src/googletest/include/gtest/gtest.h"
#include "core/Application.h"
#include "core/LayoutEnums.h"

using namespace Mountain;

TEST(Layout, HandlesVerticalLayout)
{
	auto* ele = (new Element())->Width(900)->Height(900);
	ele->AddChild<Element>()->Width(300)->Height(300);
	ele->AddChild<Element>()->Width(300)->Height(300);
	ele->AddChild<Element>()->Width(300)->Height(300);

	Application::main->Attach(ele);
	Application::main->Present();

	EXPECT_EQ(ele->ToSExpression(),
			  "(Mountain::Element 900x900 0,0 (Mountain::Element 300x300 0,0) "
			  "(Mountain::Element 300x300 0,300) (Mountain::Element 300x300 0,600))")
		<< "Expected vertical layouts to be properly organized";

	Application::Reset();
}

TEST(Layout, HandlesLeftPadding)
{
	auto* ele = (new Element())->Width(900)->Height(900)->PaddingLeft(25);
	ele->AddChild<Element>();

	Application::main->Attach(ele);
	Application::main->Present();

	EXPECT_EQ(ele->ToSExpression(),
			  "(Mountain::Element 900x900 0,0 (Mountain::Element 875x0 25,0))")
		<< "Expected left padding to be respected";

	Application::Reset();
}

TEST(Layout, HandlesTopPadding)
{
	auto* ele = (new Element())->Width(900)->Height(900)->PaddingTop(25);
	ele->AddChild<Element>();

	Application::main->Attach(ele);
	Application::main->Present();

	EXPECT_EQ(ele->ToSExpression(),
			  "(Mountain::Element 900x900 0,0 (Mountain::Element 900x0 0,25))")
		<< "Expected top padding to be respected";

	Application::Reset();
}

TEST(Layout, HandlesNestedFlexboxes)
{
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

	Application::main->Attach(ele);
	Application::main->Present();

	EXPECT_EQ(ele->ToSExpression(),
			  "(Mountain::Element 900x900 0,0 (Mountain::Element 400x235 250,195 "
			  "(Mountain::Element 75x75 413,195) (Mountain::Element 400x100 250,330)) "
			  "(Mountain::Element 400x75 250,630))")
		<< "Expected Flexbox nesting to be respected";

	Application::Reset();
}