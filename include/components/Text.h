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
			YGNodeSetNodeType(YogaNode(), YGNodeTypeText);
			YGNodeSetMeasureFunc(YogaNode(), MeasureFunc);
			YGNodeSetContext(YogaNode(), this);

			Application::main->Enqueue(
				[=, this]()
				{
					_typeface =
						mn_fontMgr->legacyMakeTypeface("Inter", SkFontStyle::Normal());
					_font = SkFont(_typeface);
					_font.setSubpixel(true);
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
			_blob = SkTextBlob::MakeFromString(_content.c_str(), _font);
			return this;
		}

	private:
		std::string _content;
		SkFont _font;
		sk_sp<SkTypeface> _typeface;
		sk_sp<SkTextBlob> _blob;

		static auto MeasureFunc(YGNodeConstRef node, float width, YGMeasureMode widthMode,
								float height, YGMeasureMode heightMode) -> YGSize;
	};
}