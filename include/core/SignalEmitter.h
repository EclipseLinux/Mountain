#pragma once
#include "Logger.h"
#include "utils/StringUtils.h"
#include <functional>
#include <string>
#include <unordered_map>
#include <vector>

namespace Mountain
{
	// yes it is against the type checking to do void* but cmon

	/**
	 * @brief Simple wrapper around a function pointer that can take in a void pointer as
	 * data
	 */
	using SignalHandler = std::function<void(void*)>;

	template <typename T> class SignalEmitter
	{
	public:
		/**
		 * @brief Attaches a signal handler to a specific signal so it gets called
		 * everytime it's emitted
		 *
		 * @param signal Signal to attach the handler to
		 * @param handler Callback function that must take data based on the event (some
		 * have data, others nullptr)
		 * @return T* Same instance of the class, for chaining
		 */
		auto On(std::string& signal, const SignalHandler& handler) -> T*
		{
			_handlers[stringToLower(signal)].push_back(handler);
			return (T*)this;
		}

		/**
		 * @brief Tries to remove every handler for a specific signal
		 *
		 * @param signal Signal to remove the handlers from
		 * @return T* Same instance of the class, for chaining
		 */
		auto Remove(std::string& signal) -> T*
		{
			signal = stringToLower(signal);

			if (!_handlers.contains(signal))
			{
				mn_coreWarn("Tried to remove handlers of signal \"{}\", but no handlers "
							"of that signal could be found",
							signal);

				return (T*)this;
			}

			_handlers[signal].clear();
		}

		/**
		 * @brief Remove a specific signal handler from a signal
		 *
		 * @param signal Signal to remove the handler from
		 * @param handler Handler to remove
		 * @return T* Same instance of the class, for chaining
		 */
		auto Remove(std::string& signal, SignalHandler& handler) -> T*
		{
			signal = stringToLower(signal);

			if (!_handlers.contains(signal))
			{
				mn_coreWarn("Tried to remove a handler of signal \"{}\", but no handlers "
							"of that signal could be found",
							signal);

				return (T*)this;
			}

			std::remove_if(_handlers[signal].begin(), _handlers[signal].end(),
						   [=](auto itr) { return itr = handler; });

			return (T*)this;
		}

		/**
		 * @brief Removes *every* signal and their handlers
		 *
		 * @return T* Same instance of the class, for chaining
		 */
		auto RemoveAll() -> T*
		{
			_handlers.clear();
			return (T*)this;
		}

	protected:
		/**
		 * @brief Emit a signal, calling every attached callback function for that signal
		 *
		 * @param signal Signal to emit
		 * @param data Data to pass to the handler, can be nullptr
		 */
		void EmitSignal(std::string& signal, void* data)
		{
			signal = stringToLower(signal);

			if (!_handlers.contains(signal))
			{
				mn_coreWarn("Tried to emit signal \"{}\", but no handlers of that signal "
							"could be found",
							signal);
				return;
			}

			for (const auto& handler : _handlers[signal])
			{
				try
				{
					handler(data);
				}
				catch (const std::exception& e)
				{
					mn_coreError("Exception ocurred while handling signal \"{}\": {}",
								 signal, e.what());
				}
				catch (...)
				{
					mn_coreFatal("An unknown exception ocurred while handling signal "
								 "\"{}\" that will be re-throwed.");
					throw "Unknown";
				}

				// just to be sure lol
			}
		}

	private:
		std::unordered_map<std::string, std::vector<SignalHandler>> _handlers;
	};
}