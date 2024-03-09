#include "utils/Color.h"
#include "core/Logger.h"
#include <iostream>

namespace Mountain
{
	Color::Color(unsigned int red, unsigned int green, unsigned int blue,
				 unsigned int alpha)
	{
		Red = red;
		Green = green;
		Blue = blue;
		Alpha = alpha;

		_checkColorRange();
	}

	Color::Color()
	{
		Red = 255;
		Green = 255;
		Blue = 255;
		Alpha = 255;
	}

	Color::Color(unsigned int hex)
	{
		Red = (hex >> 24) & 0xFF;
		Green = (hex >> 16) & 0xFF;
		Blue = (hex >> 8) & 0xFF;
		Alpha = (hex) & 0xFF;

		_checkColorRange();
	}

	auto Color::ToARGB() const -> unsigned int
	{
		unsigned int result = 0;
		result |= static_cast<unsigned int>(Alpha) << 24;
		result |= static_cast<unsigned int>(Red) << 16;
		result |= static_cast<unsigned int>(Green) << 8;
		result |= static_cast<unsigned int>(Blue);

		return result;
	}

	void Color::_checkColorRange()
	{
		if (Red >= 255)
		{
			Red = 255;
		}

		if (Green >= 255)
		{
			Green = 255;
		}

		if (Blue >= 255)
		{
			Blue = 255;
		}

		if (Alpha >= 255)
		{
			Alpha = 255;
		}
	}
}