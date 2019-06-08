#pragma once

namespace TrajectoryViewer {

class I3DView
{
public:
	struct Point3D
	{
		Point3D(double x, double y, double z)
			: x(x)
			, y(y)
			, z(z)
		{
		}

		Point3D()
			: x(0.0)
			, y(0.0)
			, z(0.0)
		{
		}

		Point3D(const Point3D& rhs)
			: x(rhs.x)
			, y(rhs.y)
			, z(rhs.z)
		{
		}

		double x;
		double y;
		double z;
	};

public:
	virtual ~I3DView() = default;

	virtual void Clear() = 0;
	virtual void AddLine(const std::string& name, std::vector<Point3D>&& points) = 0;
};

}
