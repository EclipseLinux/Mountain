#include "core/Element.h"
#include "core/Application.h"
#include "core/Canvas.h"
#include "core/SkRect.h"
#include "yoga/YGEnums.h"
#include "yoga/YGNode.h"
#include "yoga/YGNodeLayout.h"
#include "yoga/YGNodeStyle.h"
#include "yoga/YGValue.h"

// TODO: Remove CalculateLayout() calls later as the TickSystem will take care of them
namespace Mountain
{
	Element::Element()
	{
		_init(0, 0);
	}

	Element::~Element()
	{
		Destroy();

		YGNodeFree(_node);
		for (const auto& child : Children)
		{
			delete child;
		}
	}

	void Element::_init(float width, float height)
	{
		_node = YGNodeNew();
		if (width == 0)
		{
			YGNodeStyleSetWidthAuto(_node);
		}
		else
		{
			Width(width);
		}

		if (height == 0)
		{
			YGNodeStyleSetHeightAuto(_node);
		}
		else
		{
			Height(height);
		}
	}

	void Element::Tick()
	{
		if (!Enabled)
		{
			CalculateLayout();
			return;
		}

		Update();

		for (auto& child : Children)
		{
			child->Tick();
		}

		CalculateLayout();
	}

	void Element::Draw()
	{
		mn_canvas->drawRect(Bounds, mn_paint);
	}

	void Element::Render()
	{
		Bounds = SkRect::MakeXYWH(X(), Y(), Width(), Height());

		if (Path.isEmpty())
		{
			Path.addRect(Bounds);
		}
		
		if (!Visible)
		{
			return;
		}

		mn_canvas->save();

		for (auto& filter : _filters)
		{
			filter->PreRender(this);
		}

		mn_canvas->clipPath(Path, true);

		Draw();

		for (auto& child : Children)
		{
			child->Render();
		}

		for (auto& filter : _filters)
		{
			filter->PostRender(this);
		}

		Filters::BaseFilter::Reset();

		mn_canvas->restore();
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

		for (const auto& child : Children)
		{
			child->_print(depth + 1);
		}
	}

	auto Element::_toSExpr(std::string& str) -> std::string
	{
		str += "(" + ToString();

		for (const auto& child : Children)
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
		if (!YGNodeIsDirty(_node))
		{
			return;
		}
		YGNodeCalculateLayout(_node, YGUndefined, YGUndefined, YGDirectionLTR);
	}

	void Element::InsertChild(Element* child)
	{
		YGNodeInsertChild(_node, child->_node, YGNodeGetChildCount(_node));
		if (Application::Presented())
		{
			CalculateLayout();
		}
	}

	auto Element::Width() -> float
	{
		return YGNodeLayoutGetWidth(_node);
	}

	auto Element::Height() -> float
	{
		return YGNodeLayoutGetHeight(_node);
	}

	auto Element::Width(float newWidth) -> Element*
	{
		if (newWidth == 0)
		{
			YGNodeStyleSetWidthAuto(_node);
			return this;
		}
		YGNodeStyleSetWidth(_node, newWidth);
		return this;
	}

	auto Element::Height(float newHeight) -> Element*
	{
		if (newHeight == 0)
		{
			YGNodeStyleSetHeightAuto(_node);
			return this;
		}
		YGNodeStyleSetHeight(_node, newHeight);
		return this;
	}

	auto Element::PaddingBottom(float newPadding) -> Element*
	{
		YGNodeStyleSetPadding(_node, YGEdgeBottom, newPadding);
		return this;
	}

	auto Element::PaddingTop(float newPadding) -> Element*
	{
		YGNodeStyleSetPadding(_node, YGEdgeTop, newPadding);
		return this;
	}

	auto Element::PaddingLeft(float newPadding) -> Element*
	{
		YGNodeStyleSetPadding(_node, YGEdgeLeft, newPadding);
		return this;
	}

	auto Element::PaddingRight(float newPadding) -> Element*
	{
		YGNodeStyleSetPadding(_node, YGEdgeRight, newPadding);
		return this;
	}

	auto Element::Padding(float newPadding) -> Element*
	{
		YGNodeStyleSetPadding(_node, YGEdgeAll, newPadding);
		return this;
	}

	auto Element::PaddingBottom() -> float
	{
		return YGNodeLayoutGetPadding(_node, YGEdgeBottom);
	}

	auto Element::PaddingTop() -> float
	{
		return YGNodeLayoutGetPadding(_node, YGEdgeTop);
	}

	auto Element::PaddingLeft() -> float
	{
		return YGNodeLayoutGetPadding(_node, YGEdgeLeft);
	}

	auto Element::PaddingRight() -> float
	{
		return YGNodeLayoutGetPadding(_node, YGEdgeRight);
	}

	auto Element::Padding() -> float
	{
		return YGNodeLayoutGetPadding(_node, YGEdgeAll);
	}

	auto Element::JustifyContent() -> Layout::JustifyContent
	{
		return (Layout::JustifyContent)YGNodeStyleGetJustifyContent(_node);
	}

	auto Element::AlignItems() -> Layout::AlignItems
	{
		return (Layout::AlignItems)YGNodeStyleGetAlignItems(_node);
	}

	auto Element::Gap() -> float
	{
		return YGNodeStyleGetGap(_node, YGGutterAll);
	}

	auto Element::Gap(float newGap) -> Element*
	{
		YGNodeStyleSetGap(_node, YGGutterAll, newGap);
		return this;
	}

	auto Element::FlexDirection() -> Layout::FlexDirection
	{
		return (Layout::FlexDirection)YGNodeStyleGetFlexDirection(_node);
	}

	auto Element::FlexDirection(Layout::FlexDirection newDirection) -> Element*
	{
		YGNodeStyleSetFlexDirection(_node, (YGFlexDirection)newDirection);
		return this;
	}

	auto Element::JustifyContent(Layout::JustifyContent newJustify) -> Element*
	{
		YGNodeStyleSetJustifyContent(_node, (YGJustify)newJustify);
		return this;
	}

	auto Element::AlignItems(Layout::AlignItems newAlign) -> Element*
	{
		YGNodeStyleSetAlignItems(_node, (YGAlign)newAlign);
		return this;
	}

	auto Element::X() -> float
	{
		return _x();
	}

	auto Element::Y() -> float
	{
		return _y();
	}
}