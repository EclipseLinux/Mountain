#pragma once
#include "core/SignalEmitter.h"
#include "yoga/YGConfig.h"
#include <vector>

namespace Mountain
{
	/**
	 * @brief Base class for the whole Mountain project, allowing you to create UI objects
	 * Also emits singlas
	 */
	class Element : SignalEmitter<Element>
	{
	public:
	protected:
		YGNodeRef Node;

		/**
		 * @brief Children of the Element, to make a tree
		 */
		std::vector<Element*> Children;
	};
}