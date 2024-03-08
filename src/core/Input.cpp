#include "core/Input.h"
#include "core/Application.h"

namespace Mountain
{
	auto Input::HitTest(Element* tree) -> Element*
	{
		auto contains = tree->GetPath().contains(mouseX, mouseY);

		if (!contains)
		{
			return nullptr;
		}

		if (contains)
		{
			auto* result = tree;

			for (auto& child : tree->Children)
			{
				auto* childRresult = HitTest(child);

				if (childRresult != nullptr)
				{
					result = childRresult;
				}
			}

			return result;
		}

		return nullptr;
	}

	void Input::HandleInputEvents(SDL_Event* event)
	{
		switch (event->type)
		{
		case SDL_MOUSEBUTTONDOWN:
		{
			Input::mouseX = (float)event->button.x;
			Input::mouseY = (float)event->button.y;

			auto window = std::find_if(
				Application::main->_trees.begin(), Application::main->_trees.end(),
				[=](auto tree) {
					return ((Components::Window*)tree)->WindowID() ==
						   event->button.windowID;
				});

			if (window == Application::main->_trees.end())
			{
				break;
			}

			auto* element = Input::HitTest(*window);

			if (element == nullptr)
			{
				break;
			}

			if (event->button.clicks == 1)
			{
				switch (event->button.button)
				{
				case SDL_BUTTON_LEFT:
					element->EmitSignal("click", element);
					break;

				case SDL_BUTTON_RIGHT:
					element->EmitSignal("contextClick", element);
					break;

				case SDL_BUTTON_MIDDLE:
					element->EmitSignal("middleClick", element);
					break;

				default:
					break;
				}
			}
			else
			{
				switch (event->button.button)
				{
				case SDL_BUTTON_LEFT:
					element->EmitSignal("doubleClick", element);
					break;

				case SDL_BUTTON_RIGHT:
					element->EmitSignal("doubleContextClick", element);
					break;

				case SDL_BUTTON_MIDDLE:
					element->EmitSignal("doubleMiddleClick", element);
					break;

				default:
					break;
				}
			}
		}
		break;

		case SDL_MOUSEMOTION:
			mouseX = (float)event->motion.x;
			mouseY = (float)event->motion.y;
			break;

		default:
			break;
		}
	}
}