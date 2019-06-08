#include "QPlot3D/QPlot3D.h"

#include "View3D.h"

using namespace TrajectoryViewer;

struct View3D::Impl
{
	std::vector<QCurve3D> curves;
};

View3D::View3D(QWidget *parent)
	: QPlot3D(parent)
	, m_impl(std::make_unique<Impl>())
{
}

View3D::~View3D() = default;

void View3D::Clear()
{
	clear();
	replot();
	m_impl->curves.clear();
}

void View3D::AddLine(const std::string& name, std::vector<Point3D>&& points)
{
	m_impl->curves.emplace_back(QString::fromStdString(name));

	for (const auto& p : points)
		m_impl->curves.back().addData(p.x, p.y, p.z);

	m_impl->curves.back().setColor(Qt::blue);
	m_impl->curves.back().setLineWidth(2);

	addCurve(&m_impl->curves.back());

	setAxisEqual(true);
}
