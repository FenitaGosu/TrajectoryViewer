#include "Model.h"

using namespace Data;

struct Model::Impl
{
	Impl(double hSize, double vSize, double hOffset, double vOffset, int hResolution, int vResolution, double depth, double angle1X, double angle2Z, double angle3X, std::vector<std::vector<double>>&& distributionXZ)
		: hSize(hSize)
		, vSize(vSize)
		, hOffset(hOffset)
		, vOffset(vOffset)
		, hResolution(hResolution)
		, vResolution(vResolution)
		, depth(depth)
		, angle1X(angle1X)
		, angle2Z(angle2Z)
		, angle3X(angle3X)
		, distributionXZ(std::move(distributionXZ))
	{
	}

	double hSize = 0.0;
	double vSize = 0.0;

	double hOffset = 0.0;
	double vOffset = 0.0;

	int hResolution = 0;
	int vResolution = 0;

	double depth = 0.0;

	double angle1X = 0.0;
	double angle2Z = 0.0;
	double angle3X = 0.0;

	std::vector<std::vector<double>> distributionXZ;
};

Model::Model(double hSize, double vSize, double hOffset, double vOffset, int hResolution, int vResolution, double depth, double angle1X, double angle2Z, double angle3X, std::vector<std::vector<double>>&& distributionXZ)
	: m_impl(std::make_unique<Impl>(hSize, vSize, hOffset, vOffset, hResolution, vResolution, depth, angle1X, angle2Z, angle3X, std::move(distributionXZ)))
{
}

Model::Model() = default;

Model& Model::operator=(Model&& rhs) noexcept
{
	m_impl = std::move(rhs.m_impl);

	return *this;
}

Model::~Model() = default;

double Model::GetHSize() const noexcept
{
	return m_impl->hSize;
}

double Model::GetVSize() const noexcept
{
	return m_impl->vSize;
}

double Model::GetHOffset() const noexcept
{
	return m_impl->hOffset;
}

double Model::GetVOffset() const noexcept
{
	return m_impl->vOffset;
}

int Model::GetHResolution() const noexcept
{
	return m_impl->hResolution;
}

int Model::GetVResolution() const noexcept
{
	return m_impl->vResolution;
}

double Model::GetDepth() const noexcept
{
	return m_impl->depth;
}

double Model::GetAngle1X() const noexcept
{
	return m_impl->angle1X;
}

double Model::GetAngle2Z() const noexcept
{
	return m_impl->angle2Z;
}

double Model::GetAngle3X() const noexcept
{
	return m_impl->angle3X;
}

const std::vector<std::vector<double>>& Model::GetDistributionXZ() const noexcept
{
	return m_impl->distributionXZ;
}
