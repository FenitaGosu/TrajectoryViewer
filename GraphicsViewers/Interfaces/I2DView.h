#pragma once

#include "GraphicsViewers/Polygon.h"

namespace GraphicsViewers {

class I2DView
{
public:
	virtual ~I2DView() = default;

	virtual void Clear() = 0;
	virtual void AddPolygons(const std::string& name, std::vector<Polygon>&& polygons) = 0;
};

}
