#pragma once

#include <memory>

#include <QWidget>

#include "QPlot3D/QPlot3D.h"

#include "Interfaces/I3DView.h"

namespace TrajectoryViewer {

class View3D
	: public QPlot3D
	, public I3DView
{
	Q_OBJECT

public:
	explicit View3D(QWidget* parent = nullptr);
	~View3D();
	
	void Clear() override;
	void AddLine(const std::string& name, std::vector<Point3D>&& points) override;

private:
	struct Impl;
	std::unique_ptr<Impl> m_impl;
};

}
