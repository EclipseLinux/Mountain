#pragma once
#include "SDL_events.h"
#include "core/Application.h"
#include "core/Element.h"

namespace Mountain
{
	class Input
	{
	public:
		static auto HitTest(Element* tree) -> Element*;

	private:
		inline static float mouseX;
		inline static float mouseY;

		static void HandleInputEvents(SDL_Event* event);

		friend class Application;
	};
}