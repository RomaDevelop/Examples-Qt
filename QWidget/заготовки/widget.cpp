#include "widget.h"

#include <QDebug>
#include <QCloseEvent>
#include <QMessageBox>
#include <QSettings>
#include <QDir>
#include <QTimer>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QTextEdit>

#include "MyQDifferent.h"
#include "MyQFileDir.h"


Widget::Widget(QWidget *parent) : QWidget(parent)
{
	if(0) // компоновка строками
	{
		QVBoxLayout *vlo_main = new QVBoxLayout(this);
		QHBoxLayout *hlo1 = new QHBoxLayout;
		QHBoxLayout *hlo2 = new QHBoxLayout;
		vlo_main->addLayout(hlo1);
		vlo_main->addLayout(hlo2);

		QPushButton *btn1 = new QPushButton("button1");
		hlo1->addWidget(btn1);
		connect(btn1,&QPushButton::clicked,[](){ qDebug() << "btn1"; });

		QPushButton *btn2 = new QPushButton("button1");
		hlo1->addWidget(btn2);

		hlo1->addStretch();

		hlo2->addWidget(new QTextEdit);
	}

	if(1) // компоновка колонками
	{
		QHBoxLayout *hlo_main = new QHBoxLayout(this);
		QVBoxLayout *vlo1 = new QVBoxLayout;
		QVBoxLayout *vlo2 = new QVBoxLayout;
		hlo_main->addLayout(vlo1);
		hlo_main->addLayout(vlo2);

		QPushButton *btn1 = new QPushButton("button1");
		vlo1->addWidget(btn1);
		connect(btn1,&QPushButton::clicked,[](){ qDebug() << "btn1"; });

		QPushButton *btn2 = new QPushButton("button1");
		vlo1->addWidget(btn2);
		vlo1->addStretch();

		vlo2->addWidget(new QTextEdit);
	}

	settingsFile = MyQDifferent::PathToExe()+"/files/settings.ini";
	QTimer::singleShot(0,this,[this]
	{
		//move(10,10);
		//resize(1870,675);
		LoadSettings();
	});
}

Widget::~Widget()
{

}

void Widget::closeEvent(QCloseEvent * event)
{
//	auto answ = QMessageBox::question(this,"Закрытие ...","...");
//	if(0){}
//	else if(answ == QMessageBox::Yes) {/*ничего не делаем*/}
//	else if(answ == QMessageBox::No) { event->ignore(); return; }
//	else { qCritical() << "not realesed button 0x" + QString::number(answ,16); return; }

	auto answ = MyQDialogs::CustomDialog("Завершение работы приложения","Вы уверены, что хотите завершить работу приложения?"
																		"\n\n(уведомления на задачи не будут поступать)"
																		"\n(можно свернуть в трей, приложение продолжит работать)",
										 {"Да, завершить", "Свернуть в трей", "Ничего не делать"});
	if(0){}
	else if(answ == "Завершить") {/*ничего не делаем*/}
	else if(answ == "Свернуть в трей") { hide(); event->ignore(); return; }
	else if(answ == "Ничего не делать") { event->ignore(); return; }
	else { QMbc(0,"error", "not realesed button " + answ); event->ignore(); return; }

	SaveSettings();
	event->accept();
}

void Widget::SaveSettings()
{
	QDir().mkpath(QFileInfo(settingsFile).path());
	MyQFileDir::WriteFile(settingsFile, "");
	QSettings settings(settingsFile, QSettings::IniFormat);

	settings.setValue("geo", this->saveGeometry());

	settings.beginGroup("group");
	settings.setValue("other", "something");
	settings.endGroup();
}

void Widget::LoadSettings()
{
	if(!QFile::exists(settingsFile)) return;
	QSettings settings(settingsFile, QSettings::IniFormat);

	this->restoreGeometry(settings.value("geo").toByteArray());

	settings.beginGroup("group");
	if(0) qDebug() << settings.value("other");
	settings.endGroup();
}




