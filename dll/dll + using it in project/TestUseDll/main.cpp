#include "mainwindow.h"

#include <QApplication>
#include <QMessageBox>

#include <testdll.h>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWindow w;
	w.show();

	TestDll t;
	QMessageBox::information(0,"",t.Hello());

	return a.exec();
}
