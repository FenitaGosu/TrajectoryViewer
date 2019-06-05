#include "View2D.h"
#include "ui_View2D.h"

View2D::View2D(QWidget *parent) 
	: QWidget(parent)
	, m_ui(new Ui::View2D)
{
	m_ui->setupUi(this);
}

View2D::~View2D() = default;