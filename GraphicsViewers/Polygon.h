#pragma once

#include "Geometry/PointMD.h"

#include "Color.h"

namespace GraphicsViewers {

struct Polygon
{
	Color pen;
	Color brush;

	std::vector<Geometry::PointMD> vertex;
};

}
