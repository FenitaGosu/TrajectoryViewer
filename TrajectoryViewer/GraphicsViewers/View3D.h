#pragma once

#include <memory>

#include <QWidget>

namespace Ui {
class View3D;
}

class View3D : public QWidget
{
	Q_OBJECT

public:
	explicit View3D(QWidget *parent = nullptr);
	~View3D();

private:
	std::unique_ptr<Ui::View3D> m_ui;
};

