#include "components/Text.h"
#include "yoga/YGNode.h"

namespace Mountain::Components
{
	void Text::Draw()
	{
	}

	auto Text::MeasureFunc(YGNodeConstRef node, float width, YGMeasureMode widthMode,
						   float height, YGMeasureMode heightMode) -> YGSize
	{
		auto component = static_cast<Text*>(YGNodeGetContext(node));
	}
}