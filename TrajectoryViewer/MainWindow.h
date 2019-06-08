#pragma once

#include <memory>

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

namespace FileWatcher {
class IFileWatcher;
}

class Controller;

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = nullptr);
	~MainWindow();

private:
	void OnOpenXmlFile();

private:
	std::unique_ptr<Ui::MainWindow> m_ui;

	std::unique_ptr<Controller> m_controller;
	std::unique_ptr<FileWatcher::IFileWatcher> m_fileWatcher;
};
