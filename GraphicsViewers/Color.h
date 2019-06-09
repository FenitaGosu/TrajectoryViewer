#pragma once

namespace GraphicsViewers {

struct Color
{
	Color() = default;
	Color(const Color& rhs) = default;

	Color(int r, int g, int b)
		: r(r)
		, g(g)
		, b(b)
	{
	}

	int r = 0;
	int g = 0;
	int b = 0;
};

}