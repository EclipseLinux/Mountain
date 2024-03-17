#pragma once
#include "core/Application.h"
#include "core/Canvas.h"
#include "core/Element.h"
#include "core/SkCanvas.h"
#include "core/SkData.h"
#include "core/SkImage.h"
#include "core/SkSamplingOptions.h"
#include "core/SkStream.h"
#include <string>

namespace Mountain::Components
{
	class Image : public Element
	{
	public:
		using Element::Element;

		inline auto Content(const std::string& path) -> Image*
		{
			Application::main->Enqueue(
				[=, this]() {
					_image = SkImages::DeferredFromEncodedData(
						SkData::MakeFromFileName(path.c_str()));
				});
			return this;
		}

		inline void Draw() override
		{
			if (_src.fLeft == -1)
			{
				_src = SkRect::Make(_image->bounds());
			}
			
			mn_canvas->drawImageRect(_image.get(), _src, GetBounds(),
									 SkSamplingOptions::Aniso(2), &mn_paint,
									 SkCanvas::kFast_SrcRectConstraint);
		}

	private:
		sk_sp<SkImage> _image;
		SkRect _src{-1, -1, -1, -1};
	};
}