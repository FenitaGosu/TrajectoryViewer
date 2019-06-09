#include "View2D.h"

using namespace GraphicsViewers;

struct View2D::Impl
{
	Impl()
		: chart(std::make_unique<QtCharts::QChart>())
	{
	}
	std::unique_ptr<QtCharts::QChart> chart;
};

View2D::View2D(QWidget *parent)
	: QtCharts::QChartView(parent)
	, m_impl(std::make_unique<Impl>())
{
	setChart(m_impl->chart.get());
	setRenderHint(QPainter::Antialiasing);
}

View2D::~View2D() = default;

void View2D::Clear()
{
	m_impl->chart->removeAllSeries();
}

void View2D::AddPolygons(const std::string& name, std::vector<Geometry::PointsMD>&& points)
{
}
