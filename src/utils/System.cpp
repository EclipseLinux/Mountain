#include "utils/System.h"
#include "SDL_timer.h"
#include "core/Logger.h"

namespace Mountain::Internals
{
	void SystemManager::Run(const std::shared_ptr<System>& system)
	{
		try
		{
			system->Init();

			auto now = SDL_GetPerformanceCounter();
			Uint64 last = 0;

			while (system->Running)
			{
				while (!system->_taskQueue.empty())
				{
					auto task = system->_taskQueue.front();
					system->_taskQueue.pop();
					(*task)();
				}

				system->Tick();

				last = now;
				now = SDL_GetPerformanceCounter();

				system->_deltaTime = (double)((double)(now - last) /
											  (double)SDL_GetPerformanceFrequency());
			}

			system->Shutdown();
		}
		catch (const std::exception& e)
		{
			mn_coreError("Error caught at system {}: {}",
						 demangle(typeid(system.get()).name()), e.what());

			throw e;
		}
	}

	void SystemManager::Shutdown()
	{
		for (const auto& system : systems)
		{
			system->Running = false;
		}
	}
}