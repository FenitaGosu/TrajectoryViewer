#pragma once

namespace GraphicsViewers {

struct Color
{
	Color() = default;
	Color(const Color& rhs) = default;
	Color(Color&& rhs) noexcept = default;
	
	Color(int r, int g, int b)
		: r(r)
		, g(g)
		, b(b)
	{
	}

	Color& operator = (const Color& rhs) = default;
	Color& operator = (Color&& rhs) noexcept = default;

	int r = 0;
	int g = 0;
	int b = 0;
};

}
