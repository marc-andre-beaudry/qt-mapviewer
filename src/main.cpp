#include <QtGui/QApplication>
#include <QtGui>

#include "MainWindow.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	MainWindow mainWindow;
	mainWindow.show();

	return a.exec();
}
