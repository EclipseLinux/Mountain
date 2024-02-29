#include "components/Window.h"
#include "SDL.h"
#include "core/Application.h"
#include "yoga/YGNodeStyle.h"

namespace Mountain::Components
{
	Window::Window(const std::string& title, int width, int height)
	{
		Width((float)width);
		Height((float)height);
		_title = title;
	}

	void Window::Present()
	{
		_running = true;

		SdlInit();

		_window = SDL_CreateWindow(_title.c_str(), SDL_WINDOWPOS_UNDEFINED,
								   SDL_WINDOWPOS_UNDEFINED, (int)Width(), (int)Height(),
								   SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE |
									   SDL_WINDOW_ALLOW_HIGHDPI);

		if (_window == nullptr)
		{
			mn_coreError("Failed to create SDL Window: {}", SDL_GetError());
			_running = false;
			return;
		}

		_context = SDL_GL_CreateContext(_window);

		int xpos;
		int ypos;

		SDL_GetWindowPosition(_window, &xpos, &ypos);

		YGNodeStyleSetPosition(YogaNode(), YGEdgeLeft, (float)xpos);
		YGNodeStyleSetPosition(YogaNode(), YGEdgeTop, (float)ypos);
	}

	void Window::Render()
	{
		SDL_GL_MakeCurrent(_window, _context);
		SDL_GL_SwapWindow(_window);
	}

	void Window::SdlInit()
	{
		if (!Application::main->_sdlInitialized)
		{
			if (SDL_Init(SDL_INIT_EVENTS | SDL_INIT_VIDEO | SDL_INIT_SENSOR) != 0)
			{
				mn_coreFatal("Error ocurred while initializing SDL: {}", SDL_GetError());
				exit(8);
				return;
			}

			Application::main->_sdlInitialized = true;
		}

		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

		SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 0);
		SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

		SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 1);
	}

	void Window::Close()
	{
		_running = false;
		SDL_DestroyWindow(_window);
		mn_coreWarn("Closing window \"{}\"!", _title);
	}

	Window::~Window()
	{
		if (!_running)
		{
			return;
		}
		Close();
	}
}