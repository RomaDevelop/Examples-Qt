#ifndef MYOBJECT_H
#define MYOBJECT_H

#include <QDebug>
#include <QObject>

// наследник QObject обязательно должен быть в h-файле,
// если сделать в cpp выдаст ошибку undefined reference to `vtable for MyObjectInMainCpp'

// h-файл обязательно должен быть добавлен в HEADERS pro-файла, иначе тоже выдаст ошибку undefined reference to `vtable for MyObjectInMainCpp'

// explicit иногда нужен перед конструктором, иногда выдаёт ошибку undefined reference to `vtable for MyObjectInMainCpp'

// если все условия выполнены - очистить проект

// 26.05.2026 undefined reference to vtable не проходило, пока не удалил всю папку сборки. Очистки проекта было мало.
// причем я сначала удалил содержимое папки сборки, но это не помогло, еще помучался, и только после удаелния всей папки заработало.
// Не собирался Notes из-за AdditionalTrayIcon

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
