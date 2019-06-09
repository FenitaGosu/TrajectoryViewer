#pragma once

#include <memory>

#include <QWidget>

#include "QPlot3D/QPlot3D.h"

#include "Interfaces/I3DView.h"

namespace GraphicsViewers {

class View3D
	: public QPlot3D
	, public I3DView
{
public:
	explicit View3D(QWidget* parent = nullptr);
	~View3D();
	
	void Clear() override;
	void AddCurve(const std::string& name, Curve&& curve) override;

private:
	struct Impl;
	std::unique_ptr<Impl> m_impl;
};

}
