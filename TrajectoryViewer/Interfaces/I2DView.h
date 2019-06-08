#pragma once

namespace TrajectoryViewer {

class I2DView
{
public:
	virtual ~I2DView() = default;

	virtual void Clear() = 0;
};

}
