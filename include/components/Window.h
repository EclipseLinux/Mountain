#pragma once
#include "SDL_video.h"
#include "core/Element.h"
#include "core/SkRefCnt.h"
#include "core/SkSurface.h"
#include "gpu/GrDirectContext.h"

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
		sk_sp<SkSurface> _surface;
		sk_sp<GrDirectContext> _skiaCtx;
		std::string _title;
		bool _running;
	};
}