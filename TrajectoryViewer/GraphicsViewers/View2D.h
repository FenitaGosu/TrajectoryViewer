#pragma once

#include <memory>

#include <QWidget>

#include "Interfaces/I2DView.h"

namespace TrajectoryViewer {

class View2D
	: public QWidget
	, public I2DView
{
	Q_OBJECT

public:
	explicit View2D(QWidget* parent = nullptr);
	~View2D();

	void Clear() override;
};

}
