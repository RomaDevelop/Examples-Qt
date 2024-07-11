#include "bkz27psi.h"

#include <chrono>
#include <thread>
using namespace std;

#include <QGridLayout>
#include <QPushButton>


BKZ27_psi::BKZ27_psi(QString connectString_, QString name_, QObject * parent):
	QObject(parent)
{
	name = name_;
	connectString = connectString_;

	window = make_unique<QWidget>();
	window->setWindowTitle("БКЗ-27 ПСИ");
	auto layOutMain = new QVBoxLayout(window.get());
	auto layOutRow1 = new QHBoxLayout;
	auto layOutRow2 = new QHBoxLayout;
	layOutMain->addLayout(layOutRow1);
	layOutMain->addLayout(layOutRow2);

	auto btn = new QPushButton("Запустить проверку", window.get());
	layOutRow1->addWidget(btn);
	QObject::connect(btn,&QPushButton::clicked,[this]()
	{
		textBrowser->clear();

		auto tmpVectParams1 = objects[0]->FindParamsByName(TextConstant::CreateFromQString("Состояние устройства",true));
		auto tmpVectParams2 = objects[1]->FindParamsByName(TextConstant::CreateFromQString("Состояние устройства",true));

		auto tmpVectParamsVks1 = objects[0]->FindParamsByName(TextConstant::CreateFromQString("ВКЛ/ВЫКЛ",true));
		auto tmpVectParamsVks2 = objects[1]->FindParamsByName(TextConstant::CreateFromQString("ВКЛ/ВЫКЛ",true));

		auto tmpVectParamsIspr1 = objects[0]->FindParamsByName(TextConstant::CreateFromQString("Исправность",true));
		auto tmpVectParamsIspr2 = objects[1]->FindParamsByName(TextConstant::CreateFromQString("Исправность",true));

		auto tmpVectFrames1 = protocols[0]->FindFrameWorkers("вкл упр апериодический");
		auto tmpVectFrames2 = protocols[1]->FindFrameWorkers("вкл упр апериодический");

		if(tmpVectParams1.size() == 1 && tmpVectParams2.size() == 1
				&& tmpVectParamsVks1.size() == 48 && tmpVectParamsVks2.size() == 48 && tmpVectParamsIspr1.size() == 48 && tmpVectParamsIspr2.size() == 48
				&& tmpVectFrames1.size() == 1 && tmpVectFrames2.size() == 1)
		{
			Param *sostYstrCh1 = tmpVectParams1[0];
			Param *sostYstrCh2 = tmpVectParams2[0];
			FrameWorker *vklYprAper1 = tmpVectFrames1[0];
			FrameWorker *vklYprAper2 = tmpVectFrames1[0];

			std::thread *th = new std::thread([this, vklYprAper1]
			{;
				for(int i=0; i<5; i++)
				{
					emit this->SignalVklChan(i,vklYprAper1);
					this_thread::sleep_for(std::chrono::milliseconds(1000));
				}
			});
		}
		else textBrowser->append("Ошибка определения параметров - проверка отменена");
	});
	connect(this,&BKZ27_psi::SignalVklChan,this,&BKZ27_psi::SlotVklChan);

	textBrowser = new QTextBrowser(window.get());
	textBrowser->setFont(QFont("Courier new",12));
	layOutRow2->addWidget(textBrowser);
}

void BKZ27_psi::ConnectToObjects(IConnectExternalWidgets * programm_, std::vector<Object *> allObjects, std::vector<Protocol *> allProtocols)
{
	objects.clear();
	protocols.clear();
	programm = programm_;
	QStringList namesToConnect = Code::TextToCommands(connectString);
	for(auto &name:namesToConnect)
	{
		for(auto &obj:allObjects)
		{
			if(obj->name == name)
			{
				objects.push_back(obj);
				break;
			}
		}

		for(auto &prot:allProtocols)
		{
			if(prot->name == name)
			{
				protocols.push_back(prot);
				break;
			}
		}
	}

	int size = namesToConnect.size();
	if(size == 2 && size == (int)objects.size() && size == (int)protocols.size()) {/* all ok */}
	else
	{
		Error(GetClassName() + "::ConnectToObjects bad names ["+namesToConnect.join(";")+"] or objects or protocols");
		objects.clear();
		protocols.clear();
		return;
	}

	for(auto &ctrlElement:ctrlElements)
	{
		int res = programm->ConnectExternalWidget(ctrlElement.second);
		if(res != IConnectExternalWidgets::noError)
		{
			Error(GetClassName() + "::ConnectToObjects result ConnectExternalWidget error ["+IConnectExternalWidgets::ErrorCodeToStr(res)+
				  "] connectData:\n" + ctrlElement.second.ToStrForLog());
		}
	}

	for(auto &viewElement:viewElements)
	{
		int res = programm->ConnectExternalWidget(viewElement.second);
		if(res != IConnectExternalWidgets::noError)
		{
			Error(GetClassName() + "::ConnectToObjects result ConnectExternalWidget error ["+IConnectExternalWidgets::ErrorCodeToStr(res)+
				  "] connectData:\n" + viewElement.second.ToStrForLog());
		}
	}
}
