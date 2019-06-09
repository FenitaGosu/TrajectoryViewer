#include <algorithm>

#include "PointMD.h"

using namespace Geometry;

PointMD::PointMD(double x, double y, double z)
	: m_coordinates({ x, y, z })
{
}

PointMD::PointMD(const std::vector<double>& coordinates)
	: m_coordinates(coordinates)
{
}

PointMD::PointMD(std::vector<double>&& coordinates)
	: m_coordinates(std::move(coordinates))
{
}

PointMD::PointMD(std::initializer_list<double>&& coordinates)
	: m_coordinates(std::move(coordinates))
{
}

PointMD::PointMD(const size_t size)
{
	m_coordinates.resize(size);
}

PointMD::PointMD(const PointMD& rhs)
	: m_coordinates(rhs.m_coordinates)
{
}

PointMD::PointMD(PointMD&& rhs)
	: m_coordinates(std::move(rhs.m_coordinates))
{
}

PointMD& PointMD::operator =(const PointMD& rhs)
{
	m_coordinates = rhs.m_coordinates;
	return *this;
}

PointMD& PointMD::operator =(PointMD&& rhs)
{
	m_coordinates = std::move(rhs.m_coordinates);
	return *this;
}

void PointMD::Resize(const size_t size)
{
	m_coordinates.resize(size);
}

size_t PointMD::Size() const noexcept
{
	return m_coordinates.size();
}

double PointMD::X() const
{
	return m_coordinates[0];
}

double PointMD::Y() const
{
	return m_coordinates[1];
}

double PointMD::Z() const
{
	return m_coordinates[2];
}

const std::vector<double>& PointMD::P() const noexcept
{
	return m_coordinates;
}

void PointMD::SetX(const double x)
{
	Set(x, 0);
}

void PointMD::SetY(const double y)
{
	Set(y, 1);
}

void PointMD::SetZ(const double z)
{
	Set(z, 2);
}

void PointMD::Set(const std::vector<double>& coordinates)
{
	m_coordinates = coordinates;
}

void PointMD::Set(std::initializer_list<double>&& coordinates)
{
	m_coordinates = std::move(coordinates);
}

void PointMD::Set(const double value, const size_t index)
{
	m_coordinates[index] = value;
}

PointsMD PointMD::ToPointsMD(const std::vector<double>& vec)
{
	PointsMD result(vec.size());
	std::transform(vec.cbegin(), vec.cend(), result.begin(), [](auto value){ return PointMD({ value }); });
	return result;
}

double PointMD::operator [](const std::size_t num) const
{
	return m_coordinates[num];
}

double& PointMD::operator [](const std::size_t num)
{
	return m_coordinates[num];
}

