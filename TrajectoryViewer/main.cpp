#include <execution>
#include <cstdlib>
#include <iostream>

#include <QApplication>

#include "MainWindow.h"

int main(int argc, char *argv[])
{
	try
	{
		QApplication a(argc, argv);
		MainWindow w;
		w.show();

		return a.exec();
	}
	catch(std::exception& exp)
	{
		std::cerr << exp.what();
		return EXIT_FAILURE;
	}
}