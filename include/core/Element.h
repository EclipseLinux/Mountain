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
	 * Also emits signals
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

			InsertChild(child);
			EmitSignal("childNew", child);

			return this;
		}

		inline auto ChildrenCount() -> unsigned long
		{
			return _children.size();
		}

#ifdef DEBUG
		auto ToString() -> std::string;
#endif

		virtual ~Element();

	protected:
		/**
		 * @brief Called when the Element is created
		 *
		 */
		virtual void Init(){};

		/**
		 * @brief Called when the Element is being destroyed
		 *
		 */
		virtual void Destroy(){};

		/**
		 * @brief Called when a child has to be inserted into the Element, useful for
		 * custom layouts
		 *
		 * @param child Pointer to the child to insert
		 */
		virtual void InsertChild(Element* child);

	private:
		Element* _parent;
		std::vector<Element*> _children;
		YGNodeRef _node{YGNodeNew()};

		void _init();
	};
}