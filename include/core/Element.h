#pragma once
#include "core/SignalEmitter.h"
#ifdef DEBUG
#	include "utils/Demangler.h"
#endif
#include "yoga/YGNode.h"
#include <algorithm>
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

		/**
		 * @brief Checks whether an element contains another Element, only used in
		 * testing, really
		 *
		 * @tparam T Element type to compare against
		 * @return true If it does contain T
		 * @return false If it does not contain any instance of T
		 */
		template <typename T> auto Has() -> bool
		{
			static_assert(std::is_base_of<Element, T>::value,
						  "Expected T to be of type, or derived from Element");

			return std::ranges::any_of(_children, [=](auto child)
									   { return typeid(T) == typeid(*child); });

			return false;
		}

		/**
		 * @brief Returns the amount of children the Element has
		 *
		 * @return unsigned long Amount of children
		 */
		inline auto ChildrenCount() -> unsigned long
		{
			return _children.size();
		}

#ifdef DEBUG
		/**
		 * @brief Prints the element and it's children to the console
		 */
		inline void Print()
		{
			_print();
		}

		inline auto ToSExpression() -> std::string
		{
			std::string str;
			return _toSExpr(str);
		}

		/**
		 * @brief Makes up a string representation of the Element (C# inspired)
		 *
		 * @return std::string String representation of the Element
		 */
		virtual inline auto ToString() -> std::string
		{
			return demangle(typeid(*this).name()) + " " + std::to_string(Width()) + "x" +
				   std::to_string(Height()) + " " + std::to_string(X()) + ", " +
				   std::to_string(Y());
		}
#endif

		/**
		 * @brief Destroy the Element object
		 */
		virtual ~Element();

		virtual void Update(){};
		virtual void Draw(){};

		void Tick();
		virtual void Render();

#pragma region Layout related stuff
		/*
		 * Layout stuff
		 */

		/**
		 * @brief Gets the current Width of the Element
		 *
		 * @return float Width
		 */
		auto Width() -> float;

		/**
		 * @brief Gets the current Height of the Element
		 *
		 * @return float Height
		 */
		auto Height() -> float;

		/**
		 * @brief Gets the current X Position of the Element, re-calculating the layout if
		 * needed
		 *
		 * @return float X Position
		 */
		auto X() -> float;

		/**
		 * @brief Gets the current Y Position of the Element, re-calculating the layout if
		 * needed
		 *
		 * @return float Y Position
		 */
		auto Y() -> float;
#pragma endregion

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

		/**
		 * @brief Called when the Element is requested to update it's layout, useful for
		 * custom layouts
		 *
		 */
		virtual void CalculateLayout();

	private:
		Element* _parent;
		std::vector<Element*> _children;
		YGNodeRef _node{YGNodeNew()};

		float _x;
		float _y;

		void _init();

#ifdef DEBUG
		void _print(int depth = 0);
		auto _toSExpr(std::string& str) -> std::string;
#endif
	};
}