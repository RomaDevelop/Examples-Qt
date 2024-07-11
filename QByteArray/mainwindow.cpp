#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QTextCodec>
#include <QByteArray>

#include <string>
#include <bitset>
#include <memory>
#include <queue>
#include <vector>
using namespace std;

//----------------------------------------------------------------------------------------------------------
//инициализация статики MainWindow
int MainWindow::test_transmit_n {0};
int MainWindow::test_recieved_n {0};
//----------------------------------------------------------------------------------------------------------

unique_ptr<CAN> can;

queue<QString> recieved;

class decimal_vers
{
public:
	int controller;
	int number_msg;
	QString version;
	decimal_vers(int c, int n, QString v): controller{c}, number_msg{n}, version{v} {}
	QString asText() {return QString::number(controller) + QString::number(number_msg) + version ;}
};
vector <decimal_vers> global_decimal_versions;
//----------------------------------------------------------------------------------------------------------
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	Timer1 = new QTimer();
	connect(Timer1, SIGNAL(timeout()), this, SLOT(on_Timer1()));
	Timer1->start(30);

	setGeometry(100,50,width(),height());
}
//----------------------------------------------------------------------------------------------------------
MainWindow::~MainWindow()
{
    delete ui;
}
//----------------------------------------------------------------------------------------------------------
QString hex_to_string(unsigned long long value)
{
	char str[32];
	itoa(value,str,16);
	return str;
}
//----------------------------------------------------------------------------------------------------------
void MainWindow::RC_processing()
{
	//ui->textEditReceive->append("RC_processing");

	QString strfilter=ui->lineEditFilter->text();
	strfilter.replace(" ","");
	QString strfilter0=strfilter, strfilter1=strfilter;
	strfilter0.replace("C","0");
	strfilter1.replace("C","1");

	bitset<32> bitset_id0 { strfilter0.data() };
	bitset<32> bitset_id1 { strfilter1.data() };
	bitset<32> bitset_idcur { msg.id };

	if(msg.id == bitset_id0.to_ullong() || msg.id == bitset_id1.to_ullong())
	{
		MainWindow::test_recieved_n++;
		QString data_str;
		QString msg_str10;
		QString msg_str16;
		for(int i=0; i<8; i++) msg_str10 += QString::number(msg.data[i]) + " ";
		for(int i=0; i<8; i++) msg_str16 += hex_to_string(msg.data[i]) + " ";

		QString ID_2 = bitset_idcur.to_string().data();
		QString nomer_kontroller = QString(ID_2[ID_2.length()-1]);
		ID_2.remove(0,3);
		ID_2.insert(19,' '); ID_2.insert(13,' '); ID_2.insert(10,' '); ID_2.insert(6,' '); ID_2.insert(3,' ');

		data_str = QString("\n----------------------------------------------------------") +
				"\nRead kadr"+QString::number(MainWindow::test_recieved_n) +
				"\nid = "+hex_to_string(msg.id) + "(16)" +
				"\nid = " + ID_2 + "(2)" +
				"\nmsg: {"+msg_str16+"}(16)\nmsg: {"+msg_str10+"}(10)";

		recieved.push(data_str);

		if(msg.data[0]==0x8A)
		{
			bitset<8> data1 { msg.data[1] };

			QString data = "\n\nНомер контроллера: " + nomer_kontroller +
					"\nКод команды: " + hex_to_string(msg.data[0]) + "(16);" +
					"\nНомер платы: " + (data1[0] ? "МУП МДК" : "МДК") +
					"\nТип модуля: " + QString::number(msg.data[2]) + "(10);" +
					"\nНомер модуля: " + QString::number(msg.data[3]) + "(10);" +
					"\nВерсия: " + QString::number(msg.data[4]) + "(10);" +
					"\nДата: " + QString::number(msg.data[5]) + "(10);" +
					"\nМесяц: " + QString::number(msg.data[6]) + "(10);" +
					"\nГод: " + QString::number(msg.data[7]) + "(10);";

			data += "\n----------------------------------------------------------";
			recieved.push(data);
		}
		if(msg.data[0]==0x8C)
		{
			bitset<8> data1 { msg.data[1] };
			QString data1_str = data1.to_string().data();
			bitset<4> nomer_msg { data1_str.mid(0,4).data() };

			QString data = "\n\nНомер контроллера " + nomer_kontroller +
					"\nКод команды: " + hex_to_string(msg.data[0]) + "(16);" +
					"\nmsg.data[1] = {" + hex_to_string(msg.data[1]) + "}(16);"
																	   ""
																	   " {" + data1_str +"}(2);" +
					"\nНомер платы " + (data1[7] ? "МУП МДК" : "МДК") +
					"\nНомер Сообщения: " + QString::number(nomer_msg.to_ulong()) + "(10); " + nomer_msg.to_string().data() + "(2);";

			QByteArray vers_strBA;
			QTextCodec *codec1251 = QTextCodec::codecForName("Windows-1251");
			QString vers_str;

			//QString str = codec1251->toUnicode(ba);
			//QMessageBox::information(this,"",str);

			for(int i=2; i<8; i++) { vers_strBA += msg.data[i]; vers_str += QString::number(msg.data[i]) + " "; }

			data += "\nФрагмент версии: " + codec1251->toUnicode(vers_strBA) +
					"\n----------------------------------------------------------";

			recieved.push(data);
			decimal_vers d_v(nomer_kontroller.toInt(),nomer_msg.to_ulong(),codec1251->toUnicode(vers_strBA));
			global_decimal_versions.push_back(d_v);
		}
	}
}
//----------------------------------------------------------------------------------------------------------
void MainWindow::Success_processing(QString Success)
{
	this->ui->textBrowserLog->append(Success);
}
//----------------------------------------------------------------------------------------------------------
void MainWindow::Err_processing(int err_code)
{
	this->ui->textBrowserLog->append("Error processing err_code = "+QString::number(err_code));
}
//----------------------------------------------------------------------------------------------------------
_u8 MainWindow::GetChanel()
{
    if(ui->radioCh0->isChecked()) return 0;
		else if(ui->radioCh1->isChecked()) return 1;
		else if(ui->radioCh2->isChecked()) return 2;
		else if(ui->radioCh3->isChecked()) return 3;
		else if(ui->radioCh4->isChecked()) return 4;
		else if(ui->radioCh5->isChecked()) return 5;
		else if(ui->radioCh6->isChecked()) return 6;
		else if(ui->radioCh7->isChecked()) return 7;
		else {ui->textBrowserLog->append("Error GetChanel, return 0"); return 0;}
}
//----------------------------------------------------------------------------------------------------------
void MainWindow::on_pushButtonOpen_clicked()
{
    _u8 chan=GetChanel();

	can.reset(new CAN(MainWindow::CAN_processing_object,chan));
	can->open();

	if(ui->lineEditBund->text() == "1000")	   can->set_bound(BCI_1M);
	else if(ui->lineEditBund->text() == "800") can->set_bound(BCI_800K);
	else if(ui->lineEditBund->text() == "500") can->set_bound(BCI_500K);
	else if(ui->lineEditBund->text() == "250") can->set_bound(BCI_250K);
	else if(ui->lineEditBund->text() == "125") can->set_bound(BCI_125K);
	else if(ui->lineEditBund->text() == "50")  can->set_bound(BCI_50K);
	else if(ui->lineEditBund->text() == "20")  can->set_bound(BCI_20K);
	else if(ui->lineEditBund->text() == "10")  can->set_bound(BCI_10K);
}
//----------------------------------------------------------------------------------------------------------
void MainWindow::on_pushButtonClose_clicked()
{
	can->close();
}
//----------------------------------------------------------------------------------------------------------
void MainWindow::on_pushButtonStart_clicked()
{
	can->start();
}
//----------------------------------------------------------------------------------------------------------
void MainWindow::on_pushButtonStop_clicked()
{
	can->stop();
}
//----------------------------------------------------------------------------------------------------------
void MainWindow::on_pushButtonTestTransmit_clicked()
{
	msg.id=MainWindow::test_transmit_n++;
	msg.data[0] = 1;
	msg.data[1] = 2;
	msg.data[2] = 3;
	msg.data[3] = 4;
	msg.data[4] = 5;
	msg.data[5] = 6;
	msg.data[6] = 7;
	msg.data[7] = 8;
	msg.len = 8;
	//msg.flags = ;
	//msg.tslen = ;

	can->transmit();
}
//----------------------------------------------------------------------------------------------------------
void MainWindow::on_pushButtonRegEvent_clicked()
{
	can->reg_event_RC();
}
//----------------------------------------------------------------------------------------------------------
void MainWindow::on_pushButtonGenID_clicked()
{
	QString MMM;
	QString TTTTT;
	if(ui->radioButton7A->isChecked())  TTTTT="10110";
	if(ui->radioButton20A->isChecked()) TTTTT="11001";
	if(ui->radioButton40A->isChecked()) TTTTT="11100";
	if(ui->radioButtonM1->isChecked()) MMM="001";
	if(ui->radioButtonM2->isChecked()) MMM="010";
	if(ui->radioButtonM3->isChecked()) MMM="011";
	if(ui->radioButtonM4->isChecked()) MMM="100";
	if(ui->radioButtonM5->isChecked()) MMM="101";

	ui->lineEditIDReqst->setText("101 110 1000 111 000000 "+MMM+" "+TTTTT+" 11");
	ui->lineEditFilter ->setText("101 110 1000 111 1"+TTTTT+" "+MMM+" 00010 1C");

	//	0001011101000111000000МММТТТТТ11
	//	12341234123412341234123412341234
	//	1   2   3   4   5   6   7   8
}
//----------------------------------------------------------------------------------------------------------
void MainWindow::on_pushButtonVersionReqst_clicked()
{
	QString id=ui->lineEditIDReqst->text();
	id.replace(" ","");

	bitset<32> bitset_id { id.data() };

	msg.id=bitset_id.to_ulong();
	msg.data[0] = 0x8A;

	if(ui->radioButtonEngVersion->isChecked()) msg.data[0]=0x8A;
	if(ui->radioButtonDecimVersion->isChecked()) msg.data[0]=0x8C;

	if(ui->radioButtonMUPMDK->isChecked()) msg.data[1]=0x01;
	if(ui->radioButtonMDK->isChecked()) msg.data[1]=0x00;

	msg.data[2] = 0;
	msg.data[3] = 0;
	msg.data[4] = 0;
	msg.data[5] = 0;
	msg.data[6] = 0;
	msg.data[7] = 0;
	msg.len = 8;
	msg.flags = 4; // 000000100 в двоичной (EFF)
	//msg.tslen = ;

	can->transmit();
}
//----------------------------------------------------------------------------------------------------------
void MainWindow::on_Timer1()
{
	//ui->textEditReceive->append("on_pushButtonTest_clicked");
	bool added = recieved.size();
	for(unsigned int i=0; i < recieved.size(); i++)
	{
		ui->textEditReceive->append(recieved.front());
		recieved.pop();
	}
	if(added) ui->textEditReceive->moveCursor(QTextCursor::End);
}
//----------------------------------------------------------------------------------------------------------

void MainWindow::on_pushButtonTest_clicked()
{
//	char *rus="ИКЛВ";
//	int rus_i[4];
//	QString rus_i_s;

//	for(int i=0; i<4; i++)
//	{
//		rus_i[i]=rus[i];
//		rus_i_s += QString(rus[i]) +":" + QString::number(rus_i[i]) + " ";
//	}
//	QMessageBox::information(this,"",rus_i_s);

//	unsigned char rus2[5];
//	rus2[0]=200;
//	rus2[1]=202;
//	rus2[2]=203;
//	rus2[3]=194;
//	rus2[4]='\0';
//	QString s="0000";
//	s[0]=200;
//	//string rus2str=rus2;
//	QMessageBox::information(this,"",s);


}
//----------------------------------------------------------------------------------------------------------
void MainWindow::on_pushButtonDecVersions_clicked()
{
	QString contr0;
	QString contr1;
	for(auto g:global_decimal_versions)
	{
		if(g.controller==0)
		{
			contr0 += g.version;
			if(g.number_msg == 3) contr0 += "\n";
		}
		if(g.controller==1)
		{
			contr1 += g.version;
			if(g.number_msg == 3) contr1 += "\n";
		}
	}
	QString str_append = QString("\n----------------------------------------------------------") +
			"\nВерсии от контроллера 0:\n" + contr0 +
			"\nВерсии от контроллера 1:\n" + contr1 +
			"\n----------------------------------------------------------";
	ui->textEditReceive->append(str_append);
	ui->textEditReceive->moveCursor(QTextCursor::End);
	global_decimal_versions.clear();
}
//----------------------------------------------------------------------------------------------------------
