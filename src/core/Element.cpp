#include "core/Element.h"

namespace Mountain
{
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
		Init();
	}

	void Element::InsertChild(Element* child)
	{
		YGNodeInsertChild(_node, child->_node, YGNodeGetChildCount(_node));
	}
}