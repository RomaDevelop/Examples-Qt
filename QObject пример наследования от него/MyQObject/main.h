#ifndef MAIN_H
#define MAIN_H

#include <QDebug>
#include <QObject>

// наследник QObject обязательно должен быть в h-файле,
// если сделать в cpp выдаст ошибку undefined reference to `vtable for MyObjectInMainCpp'

// h-файл обязательно должен быть добавлен в HEADERS pro-файла, иначе тоже выдаст ошибку undefined reference to `vtable for MyObjectInMainCpp'

// explicit иногда нужен перед конструктором, иногда выдаёт ошибку undefined reference to `vtable for MyObjectInMainCpp'

// если все условия выполнены - очистить проект - помогает!

class MyObjectInMainH : public QObject
{
	Q_OBJECT

public:
	MyObjectInMainH(QObject *parent = nullptr): QObject(parent)
	{
		connect(this,&MyObjectInMainH::Singal,this,&MyObjectInMainH::Slot);
		emit Singal(10);
	}
	~MyObjectInMainH() {}

private: signals:
	void Singal(int i);
private slots:
	void Slot(int i)
	{
		qDebug() << i;
	}
};


#endif // MAIN_H
