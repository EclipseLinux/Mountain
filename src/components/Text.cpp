#include "components/Text.h"
#include "core/Canvas.h"
#include "core/SkCanvas.h"
#include "core/SkFontTypes.h"
#include "yoga/YGNode.h"

namespace Mountain::Components
{
	void Text::Draw()
	{
		mn_canvas->drawString(_content.c_str(), X() - (Width() / 2), Y() - (Height() / 2),
							  _font, mn_paint);

		mn_info("{} {}", X(), Y());
	}

	auto Text::MeasureFunc(YGNodeConstRef node, float width, YGMeasureMode widthMode,
						   float height, YGMeasureMode heightMode) -> YGSize
	{
		auto* component = static_cast<Text*>(YGNodeGetContext(node));
		auto measured = component->_font.measureText(component->_content.c_str(),
													 component->_content.size(),
													 SkTextEncoding::kUTF8);

		YGSize size;
		size.width = measured;
		size.height = component->_font.getSize();

		return size;
	}
}