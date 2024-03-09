#pragma once

#include "utils/Color.h"
namespace Mountain
{
	class Element;
}

namespace Mountain::Filters
{
	class BaseFilter
	{
	public:
		virtual void Init(Element* element){};
		virtual void PreRender(Element* element){};

		virtual void PostRender(Element* element);

		static void Reset();

		virtual ~BaseFilter()
		{
			Reset();
		}

		[[nodiscard]] virtual inline auto Priority() const -> int
		{
			return 0;
		}
	};

	class BackgroundColor : public BaseFilter
	{
	public:
		BackgroundColor(Color color)
		{
			_bgColor = color;
		}

		inline auto BgColor() -> Color
		{
			return _bgColor;
		}

		inline auto BgColor(Color newColor) -> BackgroundColor*
		{
			_bgColor = newColor;
			return this;
		}

		void PreRender(Element* element) override;

		[[nodiscard]] auto Priority() const -> int override
		{
			return -1;
		}

	private:
		class Color _bgColor;
	};

	class BorderRadius : public BaseFilter
	{
	public:
		BorderRadius(float radius)
			: _top(radius), _bottom(radius), _left(radius), _right(radius){};
		BorderRadius(float top, float bottom, float left, float right)
			: _top(top), _bottom(bottom), _left(left), _right(right){};

		void PreRender(Element* element) override;

		[[nodiscard]] auto Priority() const -> int override
		{
			return 5;
		}

	private:
		float _top;
		float _bottom;
		float _left;
		float _right;
	};

	class BackdropShadow : public BaseFilter
	{
	public:
		BackdropShadow(float xPos, float yPos, float depth, Color color)
			: _color(color), _x(xPos), _y(yPos), _depth(depth){};

		void PreRender(Element* element) override;

		[[nodiscard]] auto Priority() const -> int override
		{
			return 4;
		}

	private:
		Color _color;
		float _x;
		float _y;
		float _depth;
	};
}