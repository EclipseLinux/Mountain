#pragma once
#include "core/Application.h"
#include "core/Canvas.h"
#include "core/Element.h"
#include "core/Filter.h"
#include "core/SkFont.h"
#include "core/SkFontMgr.h"
#include "core/SkTextBlob.h"
#include "core/SkTypeface.h"
#include "yoga/YGNode.h"

namespace Mountain::Components
{
	class Text : public Element
	{
	public:
		using Element::Element;

		inline void Init() override
		{
			ShouldClip = false;

			YGNodeSetNodeType(YogaNode(), YGNodeTypeText);
			YGNodeSetMeasureFunc(YogaNode(), MeasureFunc);
			YGNodeSetContext(YogaNode(), this);

			AddFilter<Filters::BackgroundColor>(new Color(0xFFFFFFFF));

			Application::main->Enqueue(
				[=, this]()
				{
					_typeface =
						mn_fontMgr->legacyMakeTypeface("Inter", SkFontStyle::Normal());

					_font = SkFont(_typeface);
					_font.setSize(16);
					_font.setSubpixel(true);

					YGNodeMarkDirty(YogaNode());
					CalculateLayout();
				});
		}

		void Draw() override;

		[[nodiscard]] inline auto Content() -> std::string
		{
			return _content;
		}

		inline auto Content(const std::string& newContent) -> Text*
		{
			_content = newContent;
			return this;
		}

		[[nodiscard]] inline auto FontSize() -> float
		{
			return _font.getSize();
		}

		inline auto FontSize(float newSize) -> Text*
		{
			_font.setSize(newSize);
			return this;
		}

	private:
		std::string _content;
		SkFont _font;
		sk_sp<SkTypeface> _typeface;

		static auto MeasureFunc(YGNodeConstRef node, float width, YGMeasureMode widthMode,
								float height, YGMeasureMode heightMode) -> YGSize;
	};
}