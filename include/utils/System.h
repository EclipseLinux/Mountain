#pragma once
#include "core/Logger.h"
#include "utils/Demangler.h"
#include <algorithm>
#include <functional>
#include <memory>
#include <queue>
#include <thread>

namespace Mountain::Internals
{
	class System
	{
	public:
		bool Running{true};
		virtual ~System() = default;

		virtual void Init(){};
		virtual void Tick(){};
		virtual void Shutdown(){};

		template <typename Func, typename... Args>
		void Enqueue(Func&& func, Args&&... args)
		{
			auto task = std::make_shared<std::function<void()>>(
				std::bind(std::forward<Func>(func), std::forward<Args>(args)...));
			_taskQueue.push(task);
		}

		[[nodiscard]] inline auto GetDelta() const -> double
		{
			return _deltaTime;
		}

	private:
		std::queue<std::shared_ptr<std::function<void()>>> _taskQueue;
		double _deltaTime{0};

		friend class SystemManager;
	};

	class SystemManager
	{
	public:
		template <typename T> static auto AddSystem() -> std::shared_ptr<T>
		{
			if (currentSystems > std::thread::hardware_concurrency())
			{
				mn_coreWarn(
					"Registering a system exceeds hardware threads, this "
					"can lead to inefficient performance. ({} systems registered)",
					currentSystems);
			}

			auto system = std::make_shared<T>();

			systems.push_back(system);
			threads.emplace_back(&SystemManager::Run, system).detach();

			currentSystems++;
			mn_coreTrace("Allocating new thread for system {} ({} currently allocated)",
						 demangle(typeid(*system).name()), (threads.size() - 1) + 1);

			return system;
		}

		template <typename T> static void RemoveSystem(std::shared_ptr<T> system)
		{
			auto sys = std::find(systems.begin(), systems.end(), system);

			systems.erase(sys);
			threads.erase(threads.begin() + (sys - systems.begin()));
		}

		template <typename T> static auto GetSystem() -> std::shared_ptr<T>
		{
			auto sys = std::find_if(systems.begin(), systems.end(),
									[](const auto& ptr)
									{ return dynamic_cast<T*>(ptr.get()) != nullptr; });

			return std::dynamic_pointer_cast<T>(*sys);
		}

		static void Shutdown();

		inline static std::vector<std::shared_ptr<System>> systems;
		inline static std::vector<std::thread> threads;

	private:
		inline static unsigned int currentSystems;
		static void Run(const std::shared_ptr<System>& system);
	};
}