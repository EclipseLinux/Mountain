#pragma once
#include "utils/System.h"

namespace Mountain::Internals
{
	class RenderSystem : public System
	{
	public:
		void Init() override;
		void Tick() override;
	};

	class TickSystem : public System
	{
	public:
		void Tick() override;
	};
}