#ifndef MYOBJECT_H
#define MYOBJECT_H

#include <QDebug>
#include <QObject>

// наследник QObject обязательно должен быть в h-файле,
// если сделать в cpp выдаст ошибку undefined reference to `vtable for MyObjectInMainCpp'

// explicit обязательно нужен перед конструктором, иначе тоже выдаст ошибку undefined reference to `vtable for MyObjectInMainCpp'

class MyObject : public QObject
{
	Q_OBJECT

public:
	explicit MyObject(QObject *parent = nullptr): QObject(parent)
	{
		connect(this,&MyObject::Singal,this,&MyObject::Slot);
		emit Singal(10);
	}
	~MyObject() {}

private: signals:
	void Singal(int i);
private slots:
	void Slot(int i)
	{
		qDebug() << i;
	}
};


#endif // MYOBJECT_H
