// Любые простые пользовательские типы можно передавать в сигнал по значению если сигнал подключен с Qt::DirectConnection 

struct Struct { int n; QString str; void *ptr; };
void SignalSearch(Struct searchResult); // можно с Qt::DirectConnection

// А что бы пользовательский тип работал с подключением Qt::QueuedConnection его нужно зарегистрировать:
struct StructRegistred { int n; QString str; void *ptr; };
Q_DECLARE_METATYPE(StructRegistred); // в области объявлений, можно сразу за объявлением класса
qRegisterMetaType<StructRegistred>(); // один раз в выполняемом коде

// Работа с типами C++
vector - проверено, работает
shared_ptr - проверено, не работает

// ещё испытания с разными типами:
.h:

	struct StructInCpp;
	struct Struct { int n; QString str; void *ptr; };

	QStringList signalsToSend{
		"SignalTestStr",
		"SignalTestStrList",
		"SignalTestStrVect",
		"SignalTestStrShPtr",
		"SignalTestStruct",
		"SignalTestStructVect",
		"SignalTestStructShPtr",
		"SignalTestStructInCppShPtr",
	};
	QStringList signalsGeted;

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

		TestSignalsInCpp();

		QTimer::singleShot(0,[this](){

			if(signalsToSend == signalsGeted)
			{
				qdbg << "all signals geted";
				return;
			}
			bool notFound = false;
			for(int i=0; i<signalsToSend.size(); i++)
				if(signalsGeted.contains(signalsToSend[i]) == false)
				{
					qdbg << "ERROR!!! signal "+signalsToSend[i]+" not geted";
					notFound = true;
				}

			if(not notFound)
				qdbg << "all signals geted";
			else
			{
				qdbg << "signalsToSend: "+signalsToSend.join(" ");
				qdbg << "signalsGeted: "+signalsGeted.join(" ");
			}
		});
	}
	void TestSignalsInCpp();

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

	
.cpp:

struct StructInCpp
{
	QString name = "";
	StructInCpp(QString name): name{name} {}
};

void Widget::TestSignalsInCpp()
{
	connect(this, &Widget::SignalTestStructInCppShPtr, this, [this](std::shared_ptr<StructInCpp> dataShPtr){
		signalsGeted += dataShPtr->name;
	});
	emit SignalTestStructInCppShPtr(std::make_shared<StructInCpp>(signalsToSend[7]));
}


	