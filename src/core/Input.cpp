#include "core/Input.h"

namespace Mountain
{
	auto Input::HitTest(Element* tree) -> Element*
	{
		auto contains = tree->GetPath().contains(mouseX, mouseY);

		if (!contains)
		{
			return nullptr;
		}

		if (contains)
		{
			auto* result = tree;

			for (auto& child : tree->Children)
			{
				auto* childRresult = HitTest(child);

				if (childRresult != nullptr)
				{
					result = childRresult;
				}
			}

			return result;
		}

		return nullptr;
	}
}