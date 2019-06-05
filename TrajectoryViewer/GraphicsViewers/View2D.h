#pragma once

#include <memory>

#include <QWidget>

namespace Ui {
class View2D;
}

class View2D : public QWidget
{
	Q_OBJECT

public:
	explicit View2D(QWidget *parent = nullptr);
	~View2D();

private:
	std::unique_ptr<Ui::View2D> m_ui;
};

