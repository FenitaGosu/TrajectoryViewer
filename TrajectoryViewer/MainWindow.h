#pragma once

#include <memory>

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

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
};
