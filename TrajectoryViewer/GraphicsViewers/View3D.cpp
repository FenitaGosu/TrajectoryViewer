#include "View3D.h"
#include "ui_View3D.h"

View3D::View3D(QWidget *parent)
	: QWidget(parent)
	, m_ui(new Ui::View3D)
{
	m_ui->setupUi(this);
}

View3D::~View3D() = default;
