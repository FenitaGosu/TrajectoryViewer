#include <functional>

#include <QFileDialog>

#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "Logic/Interfaces/IDataXmlParser.h"
#include "Logic/DataXmlParser/DataXmlParser.h"

#include "Logic/Interfaces/IDataSource.h"
#include "Logic/DataSourceXml/DataSourceXml.h"

#include "FileWatcher/Interfaces/IFileWatcher.h"
#include "FileWatcher/QtFileWtcher/QtFileWatcher.h"

#include "Controller/Controller.h"

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
	const auto filePath = QFileDialog::getOpenFileName(this, tr("Select xml file"), QString(), tr("XML files (*.xml)"));

	if (filePath.isEmpty())
		return;

	std::unique_ptr<Logic::IDataXmlParser> xmlParser	= std::make_unique<Logic::DataXmlParser>(filePath.toStdString());
	std::unique_ptr<Logic::IDataSource> dataSource		= std::make_unique<Logic::DataSourceXml>(std::move(xmlParser));
	
	m_controller	= std::make_unique<Controller>(std::move(dataSource));
	m_fileWatcher	= std::make_unique<FileWatcher::QtFileWatcher>();

	m_fileWatcher->AddFile(filePath.toStdString(), std::bind(&Controller::Draw, std::cref(m_controller)));

	m_controller->Draw();
}
