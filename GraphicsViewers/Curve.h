#pragma once

#include "Geometry/PointMD.h"

#include "Color.h"

namespace GraphicsViewers {

struct Curve
{
	Color pen;
	std::vector<Geometry::PointMD> points;
};

}
