#include "MainWindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWindow w;
	w.show(); //this runs intializeGl() in GLWidget3D.cpp
	return a.exec();
}
