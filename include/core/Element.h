#pragma once
#include "core/LayoutEnums.h"
#include "core/SignalEmitter.h"
#include "yoga/YGNodeLayout.h"
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
		Element();

		/**
		 * @brief Add a new child to the Element, updating the layout if needed
		 *
		 * @tparam T Type of Element to add, must be derived from Element of course
		 * @tparam Args Any type of argument passable to the Element constructor
		 * @param args Arguments to pass to the Element constructor, if needed
		 * @return Element* New element added
		 */
		template <typename T, typename... Args> auto AddChild(Args&&... args) -> Element*
		{
			static_assert(std::is_base_of<Element, T>::value,
						  "Expected T to be of type, or derived from Element");

			auto child = new T(args...);
			InsertChild(child);
			child->_parent = this;
			child->Init();
			_children.push_back(child);

			EmitSignal("childNew", child);

			return child;
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
			return demangle(typeid(*this).name()) + " " + std::to_string((int)Width()) +
				   "x" + std::to_string((int)Height()) + " " + std::to_string((int)X()) +
				   "," + std::to_string((int)Y());
		}
#endif

		/**
		 * @brief Destroy the Element object
		 */
		virtual ~Element();

		virtual void Update(){};
		virtual void Draw(){};

		void Tick();
		virtual void Render(){};

#pragma region Layout related stuff
		/*
		 * Layout stuff
		 */

		// Get

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
		 * @brief Gets the current padding of the Element (left + top + bottom + right)
		 *
		 * @return float Padding (or padding in CSS)
		 */
		auto Padding() -> float;

		/**
		 * @brief Gets the current left padding of the Element
		 *
		 * @return float Left padding (or padding-left in CSS)
		 */
		auto PaddingLeft() -> float;

		/**
		 * @brief Gets the current right padding of the Element
		 *
		 * @return float Right padding (or padding-right in CSS)
		 */
		auto PaddingRight() -> float;

		/**
		 * @brief Gets the current top padding of the Element
		 *
		 * @return float Top padding (or padding-top in CSS)
		 */
		auto PaddingTop() -> float;

		/**
		 * @brief Gets the current bottom padding of the Element
		 *
		 * @return float Bottom padding (or padding-bottom in CSS)
		 */
		auto PaddingBottom() -> float;

		/**
		 * @brief Get the current mode of justifying content
		 *
		 * For more information, see the CSS Flexbox specification
		 * (https://developer.mozilla.org/en-US/docs/Web/CSS/justify-content)
		 * @return Layout::JustifyContent Current mode of justifying content
		 */
		auto JustifyContent() -> Layout::JustifyContent;

		/**
		 * @brief Get the current mode of aligning items
		 *
		 * For more information, see the CSS Flexbox specification
		 * (https://developer.mozilla.org/en-US/docs/Web/CSS/align-items)
		 * @return Layout::AlignItems Current mode of aligning items
		 */
		auto AlignItems() -> Layout::AlignItems;

		/**
		 * @brief Get the current direction of the Flexbox
		 *
		 * For more information, see the CSS Flexbox specification
		 * (https://developer.mozilla.org/en-US/docs/Web/CSS/flex-direction)
		 * @return Layout::FlexDirection Current mode of aligning items
		 */
		auto FlexDirection() -> Layout::FlexDirection;

		/**
		 * @brief Get the current gap between elements in the Flexbox
		 *
		 * For more information, see the CSS Flexbox specification
		 * (https://developer.mozilla.org/en-US/docs/Web/CSS/gap)
		 * @return float Current gap between elements
		 */
		auto Gap() -> float;

		// Set

		/**
		 * @brief Sets the current padding of the Element (left + top + right + bottom)
		 *
		 * @param newPadding New padding to set it to
		 * @return Element* Reference to the element, for chaining
		 */
		auto Padding(float newPadding) -> Element*;

		/**
		 * @brief Sets the current left padding of the Element
		 *
		 * @param newPadding New padding to set it to
		 * @return Element* Reference to the element, for chaining
		 */
		auto PaddingLeft(float newPadding) -> Element*;

		/**
		 * @brief Sets the current right padding of the Element
		 *
		 * @param newPadding New padding to set it to
		 * @return Element* Reference to the element, for chaining
		 */
		auto PaddingRight(float newPadding) -> Element*;

		/**
		 * @brief Sets the current top padding of the Element
		 *
		 * @param newPadding New padding to set it to
		 * @return Element* Reference to the element, for chaining
		 */
		auto PaddingTop(float newPadding) -> Element*;

		/**
		 * @brief Sets the current bottom padding of the Element
		 *
		 * @param newPadding New padding to set it to
		 * @return Element* Reference to the element, for chaining
		 */
		auto PaddingBottom(float newPadding) -> Element*;

		/**
		 * @brief Sets the current mode of justifying content
		 *
		 * @param newJustify New mode to set it to
		 * For more information, see the CSS Flexbox specification
		 * (https://developer.mozilla.org/en-US/docs/Web/CSS/justify-content)
		 * @return Element* Reference to the element, for chaining
		 */
		auto JustifyContent(Layout::JustifyContent newJustify) -> Element*;

		/**
		 * @brief Sets the current mode of aligning items
		 *
		 * @param newAlign New mode to set it to
		 * For more information, see the CSS Flexbox specification
		 * (https://developer.mozilla.org/en-US/docs/Web/CSS/align-items)
		 * @return Element* Reference to the element, for chaining
		 */
		auto AlignItems(Layout::AlignItems newAlign) -> Element*;

		/**
		 * @brief Sets the current gap between elements in the Flexbox
		 *
		 * @param newGap New gap to set it to
		 * For more information, see the CSS Flexbox specification
		 * (https://developer.mozilla.org/en-US/docs/Web/CSS/gap)
		 * @return Element* Reference to the element, for chaining
		 */
		auto Gap(float newGap) -> Element*;

		/**
		 * @brief Sets the current direction of the Flexbox
		 *
		 * @param newDirection New direction to set it to
		 * For more information, see the CSS Flexbox specification
		 * (https://developer.mozilla.org/en-US/docs/Web/CSS/flex-direction)
		 * @return Element* Reference to the element, for chaining
		 */
		auto FlexDirection(Layout::FlexDirection newDirection) -> Element*;

		/**
		 * @brief Sets the current Width of the Element
		 *
		 * @param newWidth New width to set it to
		 * @return Element* Reference to the element, for chaining
		 */
		auto Width(float newWidth) -> Element*;

		/**
		 * @brief Sets the current Height of the Element
		 *
		 * @param newWidth New height to set it to
		 * @return Element* Reference to the element, for chaining
		 */
		auto Height(float newHeight) -> Element*;

		/**
		 * @brief Gets the current X Position of the Element
		 *
		 * @return float X Position
		 */
		auto X() -> float;

		/**
		 * @brief Gets the current Y Position of the Element
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
		Element* _parent{nullptr};
		std::vector<Element*> _children;
		YGNodeRef _node;

		void _init(float width, float height);

#ifdef DEBUG
		void _print(int depth = 0);
		auto _toSExpr(std::string& str) -> std::string;
#endif

		inline auto _x() -> float
		{
			return _parent == nullptr ? YGNodeLayoutGetLeft(_node)
									  : YGNodeLayoutGetLeft(_node) + _parent->_x();
		}

		inline auto _y() -> float
		{
			return _parent == nullptr ? YGNodeLayoutGetTop(_node)
									  : YGNodeLayoutGetTop(_node) + _parent->_y();
		}
	};
}