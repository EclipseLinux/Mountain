#pragma once
#include "SDL_video.h"
#include "core/Element.h"
#include "core/SkRefCnt.h"
#include "core/SkSurface.h"
#include "gpu/GrDirectContext.h"
#include "utils/Color.h"

namespace Mountain::Components
{
	class Window : public Element
	{
	public:
		Window(const std::string& title, int width, int height);

		~Window();

		void Present() override;
		void Render() override;
		void Draw() override;
		void Close();

		[[nodiscard]] inline auto BackgroundColor() const -> Color*
		{
			return _bgColor;
		}

		inline auto BackgroundColor(Color* newColor) -> Window*
		{
			_bgColor = newColor;
			return this;
		}

		void InitRender() override;

		inline auto Running() const -> bool
		{
			return _running;
		}

		inline auto WindowID() -> unsigned long
		{
			return _window != nullptr ? SDL_GetWindowID(_window) : 0;
		}

	private:
		static void SdlInit();

		SDL_Window* _window{nullptr};
		SDL_GLContext _context;
		sk_sp<SkSurface> _surface;
		sk_sp<GrDirectContext> _skiaCtx;
		Color* _bgColor = new Color();
		std::string _title;
		bool _running;
	};
}