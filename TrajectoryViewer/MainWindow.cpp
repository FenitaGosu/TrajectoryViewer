#include <functional>

#include <QFileDialog>

#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "Data/Interfaces/IDataXmlParser.h"
#include "Data/DataXmlParser/DataXmlParser.h"

#include "Data/Interfaces/IDataSource.h"
#include "Data/DataSourceXml/DataSourceXml.h"

#include "FileWatcher/Interfaces/IFileWatcher.h"
#include "FileWatcher/QtFileWtcher/QtFileWatcher.h"

#include "Controller/Controller.h"

using namespace TrajectoryViewer;

MainWindow::MainWindow(QWidget *parent) 
	: QMainWindow(parent)
	, m_ui(std::make_unique<Ui::MainWindow>())
{
	m_ui->setupUi(this);

	connect(m_ui->action_Exit		, &QAction::triggered, this, &QMainWindow::close);
	connect(m_ui->actionOpen_XML	, &QAction::triggered, this, &MainWindow::OnOpenXmlFile);

	connect(m_ui->trajectoryButton, &QAbstractButton::toggled, [stacked = m_ui->stackedWidget, page = m_ui->pageTrajectory](bool value)
	{
		if (value)
			stacked->setCurrentWidget(page);
	});

	connect(m_ui->modelButton, &QAbstractButton::toggled, [stacked = m_ui->stackedWidget, page = m_ui->pageModel](bool value)
	{
		if (value)
			stacked->setCurrentWidget(page);
	});

	m_ui->trajectoryButton->setChecked(true);
}

MainWindow::~MainWindow() = default;

void MainWindow::OnOpenXmlFile()
{
	const auto filePath = QFileDialog::getOpenFileName(this, tr("Select xml file"), QString(), tr("XML files (*.xml)"));

	if (filePath.isEmpty())
		return;

	std::unique_ptr<Data::IDataXmlParser> xmlParser		= std::make_unique<Data::DataXmlParser>(filePath.toStdString());
	std::unique_ptr<Data::IDataSource> dataSource		= std::make_unique<Data::DataSourceXml>(std::move(xmlParser));
	
	m_controller	= std::make_unique<Controller>(std::move(dataSource), m_ui->view3D, m_ui->viewt2D);
	m_fileWatcher	= std::make_unique<FileWatcher::QtFileWatcher>();

	m_fileWatcher->AddFile(filePath.toStdString(), std::bind(&Controller::Draw, std::cref(m_controller)));

	m_controller->Draw();
}
