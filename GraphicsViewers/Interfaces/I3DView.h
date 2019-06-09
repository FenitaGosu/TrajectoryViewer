#pragma once

#include "Geometry/PointMD.h"

namespace GraphicsViewers {

class I3DView
{
public:
	virtual ~I3DView() = default;

	virtual void Clear() = 0;
	virtual void AddLine(const std::string& name, std::vector<Geometry::PointMD>&& points) = 0;
};

}
