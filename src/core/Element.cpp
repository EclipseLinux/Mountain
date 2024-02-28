#include "core/Element.h"
#include "yoga/YGEnums.h"
#include "yoga/YGNode.h"
#include "yoga/YGNodeLayout.h"
#include "yoga/YGValue.h"

namespace Mountain
{
	Element::Element()
	{
		_init();
	}
	Element::~Element()
	{
		Destroy();

		YGNodeFree(_node);
		for (const auto& child : _children)
		{
			delete child;
		}
	}

	void Element::_init()
	{
		_node = YGNodeNew();
		CalculateLayout();
	}

	void Element::Tick()
	{
		Update();

		for (const auto& child : _children)
		{
			child->Update();
		}

		if (!_updated)
		{
			CalculateLayout();
			_updated = true;
		}
	}

#ifdef DEBUG
	void Element::_print(int depth)
	{
		std::string indent;

		for (size_t i = 0; i < (size_t)depth; i++)
		{
			indent += "	";
		}

		mn_coreDebug(indent + ToString());

		for (const auto& child : _children)
		{
			child->_print(depth + 1);
		}
	}

	auto Element::_toSExpr(std::string& str) -> std::string
	{
		str += "(" + ToString();

		for (const auto& child : _children)
		{
			str += " ";
			child->_toSExpr(str);
		}

		str += ")";
		return str;
	}
#endif

	void Element::CalculateLayout()
	{
		YGNodeCalculateLayout(_node, YGUndefined, YGUndefined, YGDirectionLTR);
		_x = _getX() + YGNodeLayoutGetLeft(_node);
		_y = _getY() + YGNodeLayoutGetTop(_node);
	}

	void Element::InsertChild(Element* child)
	{
		YGNodeInsertChild(_node, child->_node, YGNodeGetChildCount(_node));
	}

	auto Element::Width() -> float
	{
		return YGNodeLayoutGetWidth(_node);
	}

	auto Element::Height() -> float
	{
		return YGNodeLayoutGetHeight(_node);
	}

	auto Element::X() -> float
	{
		if (!_updated)
		{
			CalculateLayout();
			_updated = true;
		}

		return _x;
	}

	auto Element::Y() -> float
	{
		if (!_updated)
		{
			CalculateLayout();
			_updated = true;
		}

		return _y;
	}
}