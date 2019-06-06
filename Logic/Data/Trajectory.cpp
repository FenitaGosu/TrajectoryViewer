#include <vector>

#include "Trajectory.h"

using namespace Logic;

struct Trajectory::Impl
{
	struct Data
	{
		int depth;

		double inclination;
		double azimuth;

		double x;
		double y;
		double z;
	};

	std::vector<Data> data;
};

Trajectory::Trajectory()
	: m_impl(std::make_unique<Impl>())
{
}

Trajectory::~Trajectory() = default;

size_t Trajectory::Size() const noexcept
{
	return m_impl->data.size();
}

int Trajectory::GetDepth(size_t index) const
{
	return m_impl->data[index].depth;
}

double Trajectory::GetInclination(size_t index) const
{
	return m_impl->data[index].inclination;
}

double Trajectory::GetAzimuth(size_t index) const
{
	return m_impl->data[index].azimuth;
}

double Trajectory::GetX(size_t index) const
{
	return m_impl->data[index].x;
}

double Trajectory::GetY(size_t index) const
{
	return m_impl->data[index].y;
}

double Trajectory::GetZ(size_t index) const
{
	return m_impl->data[index].z;
}
