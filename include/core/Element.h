#pragma once
#include "core/SignalEmitter.h"
#include "yoga/YGConfig.h"
#include "yoga/YGNode.h"
#include <type_traits>
#include <vector>

namespace Mountain
{
	/**
	 * @brief Base class for the whole Mountain project, allowing you to create UI objects
	 * Also emits singlas
	 */
	class Element : public SignalEmitter<Element>
	{
	public:
		template <typename T, typename... Args> auto AddChild(Args&&... args) -> Element*
		{
			static_assert(std::is_base_of<Element, T>::value,
						  "Expected T to be of type, or derived from Element");

			auto child = new T(args...);
			child->_parent = this;
			child->_init();
			_children.push_back(child);

			YGNodeInsertChild(_node, child->_node, YGNodeGetChildCount(_node));
			EmitSignal("childNew", child);

			return this;
		}

	protected:
		virtual void Init(){};

	private:
		Element* _parent;
		std::vector<Element*> _children;
		YGNodeRef _node;

		void _init()
		{
			_node = YGNodeNew();
			Init();
		}
	};
}