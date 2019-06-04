#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "XmlTools/BaseXmlParser.h"

MainWindow::MainWindow(QWidget *parent) 
	: QMainWindow(parent)
	, m_ui(std::make_unique<Ui::MainWindow>())
{
	m_ui->setupUi(this);	

	connect(m_ui->action_Exit		, &QAction::triggered, this, &QMainWindow::close);
	connect(m_ui->actionOpen_XML	, &QAction::triggered, this, &MainWindow::OnOpenXmlFile);
}

MainWindow::~MainWindow() = default;

void MainWindow::OnOpenXmlFile()
{
}