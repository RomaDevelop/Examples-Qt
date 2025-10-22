struct SearchResult // можно такое передавать через сигнал, работает из коробки без фокусов, без регистрации типа и тд
{
	IConfigItem *configItemPtr {};
	int fieldIndex = -1;
	int indexInField = -1;
	int length = -1;
};

void SignalSearchResultDoubleClicked(SearchResult searchResult); // можно

// ещё испытания с разными типами:
.h:

struct StructInCpp;
struct Struct { int n; QString str; void *ptr; QString ToStr() { return QSn(n)+" "+str+" "+MyQString::AsDebug(ptr); } };

public: signals:
	void SignalTestStr(QString str);
	void SignalTestStrList(QStringList strList);
	void SignalTestStrVect(std::vector<QString> strVect);
	void SignalTestStruct(Struct data);
	void SignalTestStructVect(std::vector<Struct> datas);

	//void SignalTestStructUPtr(std::unique_ptr<Struct> dataUPtr);	// нельзя потому что запрещено копирование unique_ptr
	void SignalTestStructShPtr(std::shared_ptr<Struct> dataShPtr);

	//void SignalTestStructInCpp(StructInCpp data);								// нельзя потому что по значению
	void SignalTestStructInCppShPtr(std::shared_ptr<StructInCpp> dataShPtr);	// можно по указателю, в т.ч. shared_ptr
	
public: 
	void TestSignals()
	{
		connect(this, &Widget::SignalTestStr, this, [](QString str){ qDebug() << str; });
		emit SignalTestStr("SignalTestStr(QString str)");

		connect(this, &Widget::SignalTestStrList, this, [](QStringList strList){ qDebug() << strList; });
		emit SignalTestStrList({"SignalTestStrList(QString strList)"});

		connect(this, &Widget::SignalTestStrVect, this, [](std::vector<QString> strVect){ qDebug() << strVect; });
		emit SignalTestStrVect({"SignalTestStrVect(std::vector<QString> strVect)"});

		connect(this, &Widget::SignalTestStruct, this, [](Struct data){ qDebug() << data.ToStr(); });
		emit SignalTestStruct({0,"SignalTestStruct", new int});

		connect(this, &Widget::SignalTestStructVect, this, [](std::vector<Struct> datas){ for(auto d:datas) qDebug() << d.ToStr(); });
		emit SignalTestStructVect({{1,"SignalTestStructVect", new int},{2,"v1",{}},{3,"v2",{}}});

		connect(this, &Widget::SignalTestStructShPtr, this, [](std::shared_ptr<Struct> dataShPtr){ qDebug() << dataShPtr->ToStr(); });
		emit SignalTestStructShPtr(std::make_shared<Struct>(Struct{1,"SignalTestStructShPtr", new int}));

		TestSignalsInCpp();
	}
	void TestSignalsInCpp();
	
.cpp:

struct StructInCpp
{
	QString name = "StructInCpp";

	QString ToStr() { return name; };
};

void Widget::TestSignalsInCpp()
{
	connect(this, &Widget::SignalTestStructInCppShPtr, this, [](std::shared_ptr<StructInCpp> dataShPtr){
		qDebug() << "SignalTestStructInCppShPtr " + dataShPtr->ToStr();
	});
	emit SignalTestStructInCppShPtr(std::make_shared<StructInCpp>());
}


	