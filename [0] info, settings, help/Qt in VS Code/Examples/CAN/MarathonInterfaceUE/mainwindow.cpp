#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <fstream>
#include <vector>
#include <mutex>
using namespace std;

#include <QDebug>
#include <QMessageBox>

#include "MyQShortings.h"

#include "marathoninterface.h"

ICANInterface *marathonInterface;
vector<ICANChannel*> chs;
mutex GUImutex;

MainWindow *MWobject;
int chForEv;
int evForEv;

QString traffic;

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	MWobject = this;

	connect(this,&MainWindow::Message,this,&MainWindow::WorkMessage);
	connect(this,&MainWindow::Message,this,&MainWindow::WorkError);

	marathonInterface = new MarathonInterface();

	if(marathonInterface->InitInterface(0, "MarathonInterface", 0) != MarathonInterface::NO_ERRORS)
		QMbError("InitInterface error");
	chs = marathonInterface->GetChannels();

	auto CBLog = [](const QString &log){qDebug() << log;};
	marathonInterface->SetCBFunctionForLog(CBLog);
	marathonInterface->SetCBFunctionForToAllChannels(CBLog);

	for(auto ch:chs) ui->listWidget->addItem(ch->GetName());
}

MainWindow::~MainWindow()
{
	ofstream out;
	if(traffic.length())
	{
	out.open("../marathon traffic.txt", fstream::app);
	out << traffic.toStdString();
	out.close();
	}

	delete marathonInterface;
	delete ui;
}

void MainWindow::on_pushButtonStart_clicked()
{
	int index = ui->listWidget->currentRow();
	QString log = "ch " + QString::number(index) + " Start";
	if(chs[index]->SetBaud(ICANChannel::BR_1M) == ICANChannel::NO_ERRORS) log += "(BR_1M)";
	if(chs[index]->Start() == ICANChannel::NO_ERRORS) log += " success";
	else log += " error";
	ui->textBrowser->append(log);

}

void MainWindow::on_pushButtonStop_clicked()
{
	int index = ui->listWidget->currentRow();
	QString log = "ch " + QString::number(index) + " Stop";
	if(chs[index]->Stop() == ICANChannel::NO_ERRORS) log += " success";
	else log += " error";
	ui->textBrowser->append(log);
}

void MainWindow::on_pushButtonTransmit_clicked()
{
	int index = ui->listWidget->currentRow();
	QString log = "ch " + QString::number(index) + " WriteMsg";
	CANMsg_t msg;
	msg.Set(0x1010101, {8,7,6,5,4,3,2,1}, 8, 0b100, 0);
	if(chs[index]->WriteMsg(&msg) == ICANChannel::NO_ERRORS) log += " success";
	else log += " error";
	GUImutex.lock();
	ui->textBrowser->append(log);
	GUImutex.unlock();
}

void MainWindow::on_pushButtonReceive_clicked()
{
	int index = ui->listWidget->currentRow();
	QString log = "ch " + QString::number(index) + " receive";
	CANMsg_t msg;
	auto getMsgCntRes = chs[index]->GetMsgCnt();
	if(getMsgCntRes.first == ICANChannel::NO_ERRORS)
	{
		log += " " + QString::number(getMsgCntRes.second) + " messages";
		ui->textBrowser->append(log);
		for(int i=0; i<getMsgCntRes.second; i++)
		{
			chs[index]->ReadMsg(&msg);
			ui->textBrowser->append(QString::number(i) + " " + msg.ToStr());
		}
	}
	else ui->textBrowser->append("GetMsgCnt error "+ ICANChannel::ErrorCodeToStr(getMsgCntRes.first));
}

void CBFunctionMsg(int ch)
{
	CANMsg_t msg;
	chs[ch]->ReadMsg(&msg);
	emit MWobject->Message(msg.ToStr());
}

void CBFunctionError(int)
{
	emit MWobject->Error();
}

void MainWindow::WorkMessage(const QString &str)
{
	ui->textBrowser->append(str);
}

void MainWindow::WorkError()
{
	ui->textBrowser->append("CBError geted");
}

void MainWindow::on_pushButtonRegCBMsg_clicked()
{
	int index = ui->listWidget->currentRow();
	QString log = "ch " + QString::number(index) + " SetCBFunctionForMessage ";

	int result = chs[index]->SetCBFunctionForMessage(CBFunctionMsg);
	if(result == ICANChannel::NO_ERRORS) log += "success";
	else log += "error " + QString::number(result);

	ui->textBrowser->append(log);
}

void MainWindow::on_pushButtonDisReg_clicked()
{
	int index = ui->listWidget->currentRow();
	chs[index]->SetCBFunctionForMessage(nullptr);
}

void MainWindow::on_pushButtonRegWrTraffic_clicked()
{
	int index = ui->listWidget->currentRow();
	QString log = "ch " + QString::number(index) + " SetFunctionWriteTraffic ";

	auto FTraffic = [](int channel, bool read, const CANMsg_t &msg)
	{
		traffic += "channel " + QString::number(channel) + (read ? " read " : " write ") + msg.ToStr() + "\n";
	};

	chs[index]->SetFunctionWriteTraffic(FTraffic);

	log += "success";

	MWobject->ui->textBrowser->append(log);
}

void MainWindow::on_pushButtonDisRegWrTraffic_clicked()
{
	int index = ui->listWidget->currentRow();
	chs[index]->SetFunctionWriteTraffic(nullptr);
}

void MainWindow::on_btnRegCBErr_clicked()
{
	int index = ui->listWidget->currentRow();
	QString log = "ch " + QString::number(index) + " SetCBFunctionForError ";

	int result = chs[index]->SetCBFunctionForError(CBFunctionError);
	if(result == ICANChannel::NO_ERRORS) log += "success";
	else log += "error " + QString::number(result);

	ui->textBrowser->append(log);
}

void MainWindow::on_btnDisRegCBErr_clicked()
{
	int index = ui->listWidget->currentRow();
	chs[index]->SetCBFunctionForMessage(nullptr);
}
