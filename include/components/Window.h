#pragma once
#include "SDL_video.h"
#include "core/Element.h"

namespace Mountain::Components
{
	class Window : public Element
	{
	public:
		Window(const std::string& title, int width, int height);

		~Window();

		void Present() override;
		void Render() override;
		void Close();

		inline auto Running() const -> bool
		{
			return _running;
		}

	private:
		static void SdlInit();

		SDL_Window* _window;
		SDL_GLContext _context;
		std::string _title;
		bool _running;
	};
}