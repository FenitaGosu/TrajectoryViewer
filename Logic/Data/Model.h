#pragma once

#include <memory>
#include <vector>

namespace Logic
{
	class Model
	{
	public:
		Model(	double hSize, double vSize,
				double hOffset, double vOffset, 
				int hResolution, int vResolution, 
				double depth,
				double angle1X, double angle2Z, double angle3X,
				std::vector<double>&& distributionXZ
			);

		~Model();
		
		double GetHSize() const noexcept;
		double GetVSize() const noexcept;

		double GetHOffset() const noexcept;
		double GetVOffset() const noexcept;

		int GetHResolution() const noexcept;
		int GetVResolution() const noexcept;

		double GetDepth() const noexcept;

		double GetAgle1X() const noexcept;
		double GetAgle2Z() const noexcept;
		double GetAgle3X() const noexcept;

		const std::vector<double>& GetDistributionXZ() const noexcept;

	private:
		struct Impl;
		std::unique_ptr<Impl> m_impl;
	};
}