#pragma once

#include <memory>

namespace Logic
{
	class Trajectory
	{
	public:
		Trajectory();
		~Trajectory();

		size_t Size() const noexcept;

		int		GetDepth(size_t index) const;
		double	GetInclination(size_t index) const;
		double	GetAzimuth(size_t index) const;

		double GetX(size_t index) const;
		double GetY(size_t index) const;
		double GetZ(size_t index) const;

	private:
		struct Impl;
		std::unique_ptr<Impl> m_impl;
	};
}