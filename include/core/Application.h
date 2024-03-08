#pragma once
#include "SDL_events.h"
#include "components/Window.h"
#include "core/Element.h"
#include "core/SignalEmitter.h"
#include "utils/SystemDefinition.h"
#include <string>
#include <vector>

namespace Mountain
{
	/**
	 * @brief Main starting point of every application built on top of Mountain
	 *
	 */
	class Application : public SignalEmitter<Application>
	{
	public:
		/**
		 * @brief Unique instance of an Application
		 *
		 * There can only be one instance globally (singleton)
		 */
		inline static Application* main{nullptr};

		/**
		 * @brief Simple RegEx describing Application Identifiers
		 *
		 * Used for internal purposes, but meh
		 */
		inline const static std::string AppIdRegex =
			"[a-zA-Z0-9_-]+\\.[a-zA-Z0-9_-]+(\\.[a-zA-Z0-9_-]+)?";

		/**
		 * @brief Construct a new Application
		 *
		 * @param appId Application Identifier, must match the @see AppIdRegex
		 */
		Application(const std::string& appId);

		/**
		 * @brief Destroy the Application object
		 */
		~Application();

		/**
		 * @brief Actually does all the heavy-lifting, such as creating windows and stuff
		 *
		 * Call this after creating every main element in your application,
		 * or whenever you feel like creating a window and stuff
		 */
		void Present();

		/**
		 * @brief Makes the application close any existing Windows and stuff
		 *
		 */
		void Quit();

		/**
		 * @brief Attaches an element into an application so it can be presented
		 *
		 * @param element Element to attach
		 */
		inline void Attach(Element* element)
		{
			_trees.push_back(element);
		}

		inline auto CreateWindow(const std::string& title, int width, int height)
			-> Components::Window*
		{
			auto* win = new Components::Window(title, width, height);
			if (_mainWindow == nullptr)
			{
				_mainWindow = win;
			}

			Attach(win);
			return win;
		}

#ifdef DEBUG
		/**
		 * @brief Resets the application back to it's original state, used in testing
		 *
		 */
		inline static void Reset()
		{
			main->_presented = false;

			for (auto& tree : main->_trees)
			{
				delete tree;
			}

			main->_trees.clear();
		}
#endif

		/**
		 * @brief Get whether the Present() method has been called
		 *
		 * @return true If it has been called before
		 * @return false If it has not been called before, or if there is no application
		 * running
		 */
		[[nodiscard]] inline static auto Presented() -> bool
		{
			return main != nullptr ? main->_presented : false;
		}

	private:
		const char* _appId;
		const char* _appName;
		const char* _appOrg;
		const char* _appDomain{""};

		void _run();
		static void RegisterSignals();

		void _handleEvents(SDL_Event* event);

		bool _sdlInitialized;

		std::vector<Element*> _trees;
		bool _presented;

		Components::Window* _mainWindow{nullptr};

		friend class Components::Window;
		friend class Internals::RenderSystem;
		friend class Internals::TickSystem;
		friend class Input;
	};
}