#pragma once

#include <memory>
#include <vector>

namespace Data {

class Model
{
public:
	Model(	double hSize, double vSize,
			double hOffset, double vOffset,
			int hResolution, int vResolution,
			double depth,
			double angle1X, double angle2Z, double angle3X,
			std::vector<std::vector<double>>&& distributionXZ
		);
	Model();
	~Model();

	Model& operator=(Model&& rhs) noexcept;

	double GetHSize() const noexcept;
	double GetVSize() const noexcept;

	double GetHOffset() const noexcept;
	double GetVOffset() const noexcept;

	int GetHResolution() const noexcept;
	int GetVResolution() const noexcept;

	double GetDepth() const noexcept;

	double GetAngle1X() const noexcept;
	double GetAngle2Z() const noexcept;
	double GetAngle3X() const noexcept;

	const std::vector<std::vector<double>>& GetDistributionXZ() const noexcept;

private:
	struct Impl;
	std::unique_ptr<Impl> m_impl;
};

}
