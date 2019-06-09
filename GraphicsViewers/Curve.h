#pragma once

#include "Geometry/PointMD.h"

namespace GraphicsViewers {

struct Curve
{
	int r = 0, g = 0, b = 0;
	std::vector<Geometry::PointMD> points;
};

}
