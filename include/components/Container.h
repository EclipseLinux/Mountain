#pragma once
#include "core/Element.h"
#include "core/Filter.h"
#include "utils/ThemeManager.h"

namespace Mountain::Components
{
	class Container : public Element
	{
	public:
		using Element::Element;

		void Init() override
		{
			AddFilter<Filters::BackgroundColor>(ThemeManager::SurfaceContainer());
			AddFilter<Filters::BorderRadius>(15);
		}
	};
}