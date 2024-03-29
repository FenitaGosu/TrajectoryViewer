#include "QPlot3D/QPlot3D.h"

#include "View3D.h"

using namespace GraphicsViewers;

struct View3D::Impl
{
	std::vector<QCurve3D> curves;
};

View3D::View3D(QWidget *parent)
	: QPlot3D(parent)
	, m_impl(std::make_unique<Impl>())
{
	setRoll(30);
	setPitch(180);
	setYaw(-50);
}

View3D::~View3D() = default;

void View3D::Clear()
{
	clear();
	replot();
	m_impl->curves.clear();
}

void View3D::AddCurve(const std::string& name, Curve&& curve)
{
	if (curve.points.empty())
		return;

	m_impl->curves.emplace_back(QString::fromStdString(name));

	for (const auto& p : curve.points)
		m_impl->curves.back().addData(p.X(), p.Y(), p.Z());

	m_impl->curves.back().setColor(QColor(curve.pen.r, curve.pen.g, curve.pen.b));
	m_impl->curves.back().setLineWidth(2);

	addCurve(&m_impl->curves.back());
}
