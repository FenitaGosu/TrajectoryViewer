#pragma once

#include <memory>

namespace Logic
{
	class Trajectory
	{
	public:
		struct Data
		{
			double depth = 0.0;

			double inclination	= 0.0;
			double azimuth		= 0.0;

			double x = 0.0;
			double y = 0.0;
			double z = 0.0;
		};

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

		void AddNewData(Data&& data);
		void Reserve(size_t count);

	private:
		struct Impl;
		std::unique_ptr<Impl> m_impl;
	};
}