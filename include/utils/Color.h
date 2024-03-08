#pragma once

namespace Mountain
{
	class Color
	{
	public:
		unsigned int Red;
		unsigned int Green;
		unsigned int Blue;
		unsigned int Alpha;

		Color();
		Color(unsigned int red, unsigned int green, unsigned int blue,
			  unsigned int alpha = 255);
		Color(unsigned int hex);

		[[nodiscard]] auto ToARGB() const -> unsigned int;

	private:
		void _checkColorRange();
	};
}