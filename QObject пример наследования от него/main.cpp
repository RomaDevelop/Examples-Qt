#include "MyObject.h"
#include "main.h"

#include <thread>
#include <chrono>

#include <QWidget>
#include <QApplication>

#include <QDebug>
#include <QObject>

// наследник QObject обязательно должен быть в h-файле,
// если сделать в cpp выдаст ошибку undefined reference to `vtable for MyObjectInMainCpp'

class MyObjectInMainCpp : public QObject
{
	Q_OBJECT

public:
	MyObjectInMainCpp(QObject *parent = nullptr): QObject(parent)
	{
		connect(this,&MyObjectInMainCpp::Singal,this,&MyObjectInMainCpp::Slot);
		emit Singal(10);
	}
	~MyObjectInMainCpp() {}

private: signals:
	void Singal(int i);
private slots:
	void Slot(int i)
	{
		qDebug() << i;
	}
};

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	MyObject o;
	MyObjectInMainH oInMainH;
	//MyObjectInMainCpp oInMainCPP;  выдаёт undefined reference to `vtable for MyObjectInMainCpp'

	QWidget w; // нужно чтобы графическое приложение закрылось при закрытии этого виджета
	w.show();

	return a.exec();
}
