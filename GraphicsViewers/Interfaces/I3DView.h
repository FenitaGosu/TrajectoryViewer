#pragma once

#include "GraphicsViewers/Curve.h"

namespace GraphicsViewers {

class I3DView
{
public:
	virtual ~I3DView() = default;

	virtual void Clear() = 0;
	virtual void AddCurve(const std::string& name, Curve&& curve) = 0;
};

}
