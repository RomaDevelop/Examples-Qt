#ifndef WIDGET_H
#define WIDGET_H

#include <memory>

#include "MyQShortings.h"
#include "MyQString.h"

#include <QDebug>
#include <QWidget>
#include <QTimer>

struct StructInCpp;

struct StructRegistred { int n; QString str; void *ptr; };
Q_DECLARE_METATYPE(StructRegistred);

class Widget : public QWidget
{
	Q_OBJECT

public:
	Widget(QWidget *parent = nullptr);
	~Widget();

	struct Struct { int n; QString str; void *ptr; };


	QStringList signalsToSend{
		"SignalTestStr",
		"SignalTestStrList",
		"SignalTestStrVect",
		"SignalTestStrShPtr",
		"SignalTestStruct",
		"SignalTestStructVect",
		"SignalTestStructShPtr",
		"SignalRegistredType"
	};
	QStringList signalsToSendInCpp{
		"SignalTestStructInCppShPtr",
	};
	QStringList signalsGeted;
	QStringList signalsGetedInCpp;

	void TestSignals()
	{
		connect(this, &Widget::SignalTestStr, this, [this](QString str){ signalsGeted += str; }
		, Qt::QueuedConnection);
		emit SignalTestStr(signalsToSend[0]);

		connect(this, &Widget::SignalTestStrList, this, [this](QStringList strList){ signalsGeted += strList[0]; }
		, Qt::QueuedConnection);
		emit SignalTestStrList({signalsToSend[1]});

		connect(this, &Widget::SignalTestStrVect, this, [this](std::vector<QString> strVect){ signalsGeted += strVect[0]; },
		Qt::QueuedConnection);
		emit SignalTestStrVect({signalsToSend[2]});

		connect(this, &Widget::SignalTestStrShPtr, this, [this](std::shared_ptr<QString> str){ signalsGeted += *str; }
		/*, Qt::QueuedConnection*/);
		emit SignalTestStrShPtr(std::make_shared<QString>(signalsToSend[3]));

		connect(this, &Widget::SignalTestStruct, this, [this](Struct data){ signalsGeted += data.str; }
		/*, Qt::QueuedConnection*/);
		emit SignalTestStruct({0,signalsToSend[4], new int});

		connect(this, &Widget::SignalTestStructVect, this, [this](std::vector<Struct> datas){ signalsGeted += datas[0].str; }
		, Qt::DirectConnection);
		emit SignalTestStructVect({{1,signalsToSend[5], new int},{},{}});

		connect(this, &Widget::SignalTestStructShPtr, this, [this](std::shared_ptr<Struct> dataShPtr){ signalsGeted += dataShPtr->str; }
		, Qt::DirectConnection);
		emit SignalTestStructShPtr(std::make_shared<Struct>(Struct{1,signalsToSend[6], new int}));

		qRegisterMetaType<StructRegistred>();
		connect(this, &Widget::SignalStructRegistred, this, [this](StructRegistred data){ signalsGeted += data.str; }
		, Qt::QueuedConnection);
		emit SignalStructRegistred({0,signalsToSend[7], new int});

		TestSignalsInCpp();

		QTimer::singleShot(0,[this](){
			if(CheckResult(signalsToSend, signalsGeted)
					and CheckResult(signalsToSendInCpp, signalsGetedInCpp))
				qdbg << "all signals geted";
		});
	}
	void TestSignalsInCpp();

	static bool CheckResult(const QStringList &toSend, const QStringList &geted)
	{
		if(toSend == geted)
		{
			return true;
		}
		bool notFound = false;
		for(int i=0; i<toSend.size(); i++)
			if(geted.contains(toSend[i]) == false)
			{
				qdbg << "ERROR!!! signal "+toSend[i]+" not geted";
				notFound = true;
			}

		if(not notFound)
			return true;
		else
		{
			return false;
		}
	}

public: signals:
	void SignalTestStr(QString str);
	void SignalTestStrList(QStringList strList);
	void SignalTestStrVect(std::vector<QString> strVect);
	void SignalTestStrShPtr(std::shared_ptr<QString> strShPtr);
	void SignalTestStruct(Struct data);
	void SignalTestStructVect(std::vector<Struct> datas);

	//void SignalTestStructUPtr(std::unique_ptr<Struct> dataUPtr);	// нельзя потому что запрещено копирование unique_ptr
	void SignalTestStructShPtr(std::shared_ptr<Struct> dataShPtr);

	//void SignalTestStructInCpp(StructInCpp data);								// нельзя потому что по значению
	void SignalTestStructInCppShPtr(std::shared_ptr<StructInCpp> dataShPtr);	// можно по указателю, в т.ч. shared_ptr

	void SignalStructRegistred(StructRegistred data);
};

#endif // WIDGET_H
