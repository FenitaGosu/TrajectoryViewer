#pragma once

#include "Geometry/PointMD.h"

namespace GraphicsViewers {

class I2DView
{
public:
	virtual ~I2DView() = default;

	virtual void Clear() = 0;

	virtual void AddPolygons(const std::string& name, std::vector<Geometry::PointsMD>&& points) = 0;
};

}
