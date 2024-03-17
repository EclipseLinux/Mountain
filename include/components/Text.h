#pragma once
#include "core/Element.h"
#include "core/Filter.h"
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

	private:
		std::string _content;

		static auto MeasureFunc(YGNodeConstRef node, float width, YGMeasureMode widthMode,
								float height, YGMeasureMode heightMode) -> YGSize;
	};
}