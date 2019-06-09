#include <QLineSeries>
#include <QAreaSeries>

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

	m_impl->chart->setBackgroundBrush(QBrush(Qt::white, Qt::SolidPattern));
	setBackgroundBrush(QBrush(Qt::white, Qt::SolidPattern));

	m_impl->chart->legend()->hide();
}

View2D::~View2D() = default;

void View2D::Clear()
{
	m_impl->chart->removeAllSeries();
}

void View2D::AddPolygons(const std::string& name, std::vector<Polygon>&& polygons)
{
	if (polygons.empty())
		return;

	for (const auto& polygon : polygons)
	{
		QtCharts::QLineSeries* curve = new QtCharts::QLineSeries();
		QtCharts::QAreaSeries* area = new QtCharts::QAreaSeries(curve, nullptr);

		area->setBrush(QColor(polygon.brush.r, polygon.brush.g, polygon.brush.b));
		area->setPen(QColor(polygon.pen.r, polygon.pen.r, polygon.pen.r));

		QList<QPointF> points;
		points.reserve(static_cast<int>(polygon.vertex.size()));

		std::transform(polygon.vertex.cbegin(), polygon.vertex.cend(), std::back_inserter(points), [](const auto& point)
		{
			return QPointF(point.X(), point.Y());
		});

		// close
		points.append(QPointF(polygon.vertex.front().X(), polygon.vertex.front().Y()));

		curve->append(points);

		m_impl->chart->addSeries(area);
	}

	m_impl->chart->createDefaultAxes();
}
