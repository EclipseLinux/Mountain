#include "core/Application.h"
#include "SDL.h"
#include "components/Window.h"
#include "core/Canvas.h"
#include "core/Element.h"
#include "core/Input.h"
#include "core/Logger.h"
#include "utils/StringUtils.h"
#include "utils/System.h"
#include "utils/SystemDefinition.h"
#include <regex>
#include <spdlog/spdlog.h>

namespace Mountain
{
	Application::Application(const std::string& appId)
	{
		Mountain::Logger::Init();

		if (main != nullptr)
		{
			mn_coreError("There is another instance of Mountain::Application!");
			return;
		}

#ifdef DEBUG
		if (!std::regex_match(appId, std::regex(AppIdRegex)))
		{
			mn_coreFatal("App ID is invalid. It must contain 1 to 3 segments, delimited "
						 "by dots (.). Regex: \"{}\"",
						 AppIdRegex);

			exit(6);
		}
#endif

		main = this;

		_appId = appId.c_str();

		auto segments = stringSplit(appId, ".");

		// we're going to assume it matches the regex, but still make some checks
		mn_coreAssert(!segments.empty(), "Expected at least one segment");
		mn_coreAssert(segments.size() <= 3, "Expected at most three segments");

		if (segments.size() == 3)
		{
			// best case
			_appDomain = segments[0].c_str();
			_appOrg = segments[1].c_str();
			_appName = segments[2].c_str();
		}
		else
		{
			_appOrg = segments[0].c_str();
			_appName = segments[1].c_str();
		}

		spdlog::set_default_logger(spdlog::default_logger()->clone(_appName));

		mn_renderSys = Internals::SystemManager::AddSystem<Internals::RenderSystem>();
		mn_tickSys = Internals::SystemManager::AddSystem<Internals::TickSystem>();
		mn_workerSys = Internals::SystemManager::AddSystem<Internals::System>();

		Enqueue(Internals::createFontMgr);

		mn_coreInfo("Initializing \"{}\", by \"{}\"", _appName, _appOrg);
	}

	void Application::Present()
	{
		if (_trees.empty())
		{
			mn_coreTrace(
				"There are no main UI trees existing, are they attached to \"{}\"?",
				_appId);

			return;
		}

		_presented = true;

		for (auto& element : _trees)
		{
			element->Tick();
			element->Present();
		}

		EmitSignal("present");

		// that means we have windows created and that we need to go into event loop and
		// shi
		if (_sdlInitialized && _mainWindow != nullptr)
		{
			Internals::SystemManager::RunAll();

			_run();
		}
	}

	void Application::_run()
	{
		SDL_Event event;

		while (main->_mainWindow != nullptr)
		{
			if (!main->_mainWindow->Running())
			{
				break;
			}

			while (SDL_WaitEvent(&event) != 0)
			{
				_handleEvents(&event);
			}
		}
	}

	void Application::_handleEvents(SDL_Event* event)
	{
		switch (event->type)
		{
		case SDL_QUIT:
		case SDL_APP_TERMINATING:
			Quit();
			break;

		case SDL_MOUSEBUTTONDOWN:
		case SDL_MOUSEMOTION:
			Input::HandleInputEvents(event);
			break;

		default:
			break;
		}
	}

	void Application::Quit()
	{
		if (!_presented)
		{
			return;
		}

		Internals::SystemManager::Shutdown();

		for (auto& element : _trees)
		{
			delete element;
		}

		_trees.clear();

		if (_sdlInitialized)
		{
			SDL_Quit();
			_sdlInitialized = false;
		}
	}

	Application::~Application()
	{
		Quit();
		Reset();
	}
}