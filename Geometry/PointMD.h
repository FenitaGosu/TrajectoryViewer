#pragma once

#include <vector>
#include <string>

namespace Geometry {

class PointMD;
using PointsMD = std::vector<PointMD>;

enum class Coordinate
{
	x = 0,
	y,
	z,
};

class PointMD
{
public:
	PointMD(double x, double y, double z);
	PointMD(double x, double y);
	PointMD(const std::vector<double>& coordinates = std::vector<double>());
	PointMD(std::vector<double>&& coordinates);
	PointMD(std::initializer_list<double>&& coordinates);
	PointMD(const size_t size);
	PointMD(const PointMD& rhs);
	PointMD(PointMD&& rhs) noexcept;

	PointMD& operator =(const PointMD& rhs);
	PointMD& operator =(PointMD&& rhs) noexcept;

	void Resize(const size_t size);
	size_t Size() const noexcept;

	double X() const;
	double Y() const;
	double Z() const;

	const std::vector<double>& P() const noexcept;

	double operator [](const size_t num) const;
	double& operator [](const size_t num);

	void SetX(const double x);
	void SetY(const double y);
	void SetZ(const double z);

	void Set(const std::vector<double>& coordinates);
	void Set(std::initializer_list<double>&& coordinates);
	void Set(double value, const size_t index);
	
	static PointsMD ToPointsMD(const std::vector<double>& vec);

private:
	std::vector<double> m_coordinates;
};

}
