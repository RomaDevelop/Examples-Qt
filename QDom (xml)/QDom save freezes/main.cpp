#include "mainwindow.h"

#include <chrono>
using namespace std;

#include <QApplication>
#include <QDomDocument>
#include <QFile>
#include <QDebug>

#include "MyQDom.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWindow w;
	w.show();

	QFile f("C:\\Work\\C++\\CAN\\ServisCreator\\Сюда можно скопировать XML.xml");
	f.open(QFile::ReadOnly);
	QString str = f.readAll();

	QDomDocument xmlForRun;
	xmlForRun.setContent(str);
	auto subElements = MyQDom::GetTopLevelElements(xmlForRun);

	qDebug() << "start";
	auto start_time = chrono::steady_clock::now();

	MyQDom::ToString(subElements[0]);

	auto end_time = chrono::steady_clock::now();
	auto elapsed = chrono::duration_cast<chrono::nanoseconds>(end_time - start_time);
	string elapsed_str = to_string(elapsed.count());
	for(int i=elapsed_str.size()-1, n=1; i>=0; i--, n++) if(n%3 == 0 && i!=0) elapsed_str.insert(i," ");
	qDebug() << elapsed_str.c_str();


	return a.exec();
}
