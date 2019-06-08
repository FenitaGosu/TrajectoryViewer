#include <string>
#include <vector>

#include "Logic/Data/Trajectory.h"
#include "Logic/Data/Model.h"

#include "Interfaces/IDataSource.h"

#include "Interfaces/I3DView.h"
#include "Interfaces/I2DView.h"

#include "Controller.h"

using namespace TrajectoryViewer;

struct Controller::Impl
{
	Impl(std::unique_ptr<Logic::IDataSource>&& dataSource, I3DView* view3d, I2DView* view2d)
		: dataSource(std::move(dataSource))
		, view3d(view3d)
		, view2d(view2d)
	{
	}

	std::unique_ptr<Logic::IDataSource> dataSource;
	I3DView* view3d;
	I2DView* view2d;
};

Controller::Controller(std::unique_ptr<Logic::IDataSource>&& dataSource, I3DView* view3d, I2DView* view2d)
	: m_impl(std::make_unique<Impl>(std::move(dataSource), view3d, view2d))
{
}

Controller::~Controller() = default;

void Controller::Draw()
{
	m_impl->dataSource->Refresh();

	m_impl->view3d->Clear();

	const auto& trajectory = m_impl->dataSource->GetTrajectory();

	std::vector<I3DView::Point3D> points;
	points.reserve(trajectory.Size());

	for (size_t i = 0, sz = trajectory.Size(); i < sz; ++i)
		points.emplace_back(trajectory.GetX(i), trajectory.GetY(i), trajectory.GetZ(i));

	m_impl->view3d->AddLine("Trajectory", std::move(points));
}
