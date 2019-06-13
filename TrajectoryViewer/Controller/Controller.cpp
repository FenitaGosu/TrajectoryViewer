#include <string>
#include <vector>

#include "Data/Data/Trajectory.h"
#include "Data/Data/Model.h"
#include "Data/Interfaces/IDataSource.h"

#include "GraphicsViewers/Interfaces/I3DView.h"
#include "GraphicsViewers/Interfaces/I2DView.h"

#include "GraphicsViewers/Curve.h"
#include "GraphicsViewers/Polygon.h"
#include "GraphicsViewers/ColorGradientGenertor.h"

#include "Controller.h"

using namespace TrajectoryViewer;

namespace
{
	GraphicsViewers::Curve TrajectoryToCurve(const Data::Trajectory& trajectory)
	{
		GraphicsViewers::Curve curve;

		curve.points.reserve(trajectory.Size());

		for (size_t i = 0, sz = trajectory.Size(); i < sz; ++i)
			curve.points.emplace_back(trajectory.GetX(i), trajectory.GetY(i), trajectory.GetZ(i));

		curve.pen = GraphicsViewers::Color(0, 123, 167);

		return curve;
	}

	std::vector<GraphicsViewers::Polygon> ModelToPolygons(const Data::Model& model)
	{
		std::vector<GraphicsViewers::Polygon> polygons;

		double hStep = model.GetHSize() / model.GetHResolution();
		double vStep = model.GetVSize() / model.GetVResolution();

		std::vector<double> horizontal;
		std::vector<double> vertical;

		horizontal.reserve(static_cast<size_t>(model.GetHResolution() + 1));
		vertical.reserve(static_cast<size_t>(model.GetVResolution() + 1));

		double hStart = model.GetHOffset();
		for (int i = 0, sz = model.GetHResolution() + 1; i < sz; ++i)
			horizontal.push_back(hStart + hStep * i);

		double vStart = model.GetVOffset();
		for (int i = 0, sz = model.GetVResolution() + 1; i < sz; ++i)
			vertical.push_back(vStart + vStep * i);

		const auto colors = GraphicsViewers::ColorGradientGenertor::GenerateColorDistribution(model.GetDistributionXZ());

		polygons.reserve(model.GetHResolution() * model.GetVResolution());

		for (int j = 0, szj = model.GetVResolution(); j < szj; ++j)
		{
			for (int i = 0, szi = model.GetHResolution(); i < szi; ++i)
			{
				GraphicsViewers::Polygon p;

				p.vertex.emplace_back(horizontal[i]			, vertical[j + 1]);
				p.vertex.emplace_back(horizontal[i + 1]		, vertical[j + 1]);
				p.vertex.emplace_back(horizontal[i + 1]		, vertical[j]);
				p.vertex.emplace_back(horizontal[i]			, vertical[j]);
				
				p.brush = colors[j][i];

				polygons.push_back(p);
			}
		}
		return polygons;
	}
}

struct Controller::Impl
{
	Impl(std::unique_ptr<Data::IDataSource>&& dataSource, GraphicsViewers::I3DView* view3d, GraphicsViewers::I2DView* view2d)
		: dataSource(std::move(dataSource))
		, view3d(view3d)
		, view2d(view2d)
	{
	}

	std::unique_ptr<Data::IDataSource> dataSource;
	GraphicsViewers::I3DView* view3d;
	GraphicsViewers::I2DView* view2d;
};

Controller::Controller(std::unique_ptr<Data::IDataSource>&& dataSource, GraphicsViewers::I3DView* view3d, GraphicsViewers::I2DView* view2d)
	: m_impl(std::make_unique<Impl>(std::move(dataSource), view3d, view2d))
{
}

Controller::~Controller() = default;

void Controller::Draw()
{
	m_impl->view3d->Clear();
	m_impl->view2d->Clear();

	if (!m_impl->dataSource->Refresh())
		return;
	
	m_impl->view3d->AddCurve("Trajectory", TrajectoryToCurve(m_impl->dataSource->GetTrajectory()));
	m_impl->view2d->AddPolygons("Model", ModelToPolygons(m_impl->dataSource->GetModel()));
}
