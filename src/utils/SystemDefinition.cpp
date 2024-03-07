#include "utils/SystemDefinition.h"
#include "core/Application.h"

namespace Mountain::Internals
{
	void RenderSystem::Init()
	{
		for (auto& tree : Application::main->_trees)
		{
			tree->EmitSignal("presentRender");
			tree->InitRender();
		}
	}

	void RenderSystem::Tick()
	{
		for (auto& tree : Application::main->_trees)
		{
			tree->Render();
		}
	}

	void TickSystem::Tick()
	{
		for (auto& tree : Application::main->_trees)
		{
			tree->Tick();
		}
	}
}