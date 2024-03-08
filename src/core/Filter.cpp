#include "core/Filter.h"
#include "core/Canvas.h"
#include "core/SkBlurTypes.h"
#include "core/SkMaskFilter.h"
#include "core/SkRRect.h"

namespace Mountain::Filters
{
	void BaseFilter::PostRender(Element* element)
	{
		Reset();
	}

	void BaseFilter::Reset()
	{
		mn_paint.reset();
		mn_paint.setColor(SK_ColorWHITE);
		mn_paint.setAntiAlias(true);
		mn_path.reset();
	}

	void BackgroundColor::PreRender(Element* element)
	{
		mn_paint.setColor(_bgColor.ToARGB());
	}

	void BorderRadius::PreRender(Element* element)
	{
		auto rect = SkRRect::MakeEmpty();

		rect.setNinePatch(SkRect::MakeXYWH(element->X(), element->Y(), element->Width(),
										   element->Height()),
						  _left, _top, _right, _bottom);

		element->Path().addRRect(rect);
	}

	void BackdropShadow::PreRender(Element* element)
	{
		mn_paint.setAntiAlias(true);

		mn_paint.setColor(_color.ToARGB());
		mn_paint.setMaskFilter(
			SkMaskFilter::MakeBlur(kNormal_SkBlurStyle, _depth, false));

		element->Path().offset(_x, _y);

		mn_canvas->drawPath(element->Path(), mn_paint);

		element->Path().offset(-_x, -_y);
		mn_paint.reset();
		mn_paint.setColor(SK_ColorWHITE);
	}
}