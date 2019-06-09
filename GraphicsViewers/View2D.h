#pragma once

#include <memory>

#include <QtCharts/QChartView>

#include "Interfaces/I2DView.h"

namespace GraphicsViewers {

class View2D
	: public QtCharts::QChartView
	, public I2DView
{
public:
	explicit View2D(QWidget* parent = nullptr);
	~View2D();

	void Clear() override;
	void AddPolygons(const std::string& name, std::vector<Polygon>&& polygons) override;

private:
	struct Impl;
	std::unique_ptr<Impl> m_impl;
};

}
