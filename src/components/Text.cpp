#include "components/Text.h"
#include "core/Canvas.h"
#include "core/SkCanvas.h"
#include "yoga/YGNode.h"

namespace Mountain::Components
{
	void Text::Draw()
	{
		mn_canvas->drawTextBlob(_blob, X(), Y(), mn_paint);
	}

	auto Text::MeasureFunc(YGNodeConstRef node, float width, YGMeasureMode widthMode,
						   float height, YGMeasureMode heightMode) -> YGSize
	{
		auto* component = static_cast<Text*>(YGNodeGetContext(node));

		YGSize size;
		size.width = component->_blob->bounds().width();
		size.height = component->_blob->bounds().height();

		return size;
	}
}