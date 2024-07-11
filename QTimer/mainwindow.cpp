#include "mainwindow.h"
#include "ui_mainwindow.h"

//----------------------------------------------------------------------------------------------------------
MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	Timer1 = new QTimer();
	connect(Timer1, SIGNAL(timeout()), this, SLOT(on_Timer1()));
	Timer1->start(1000);
	Timer1->stop();
	
	// QTimer -> лямбда
	connect(servisTimer, &QTimer::timeout,[](){qdbg << "servisTimer";});
	
	QTimer::singleShot(0,this,[this]
	{
		SomeThing();
	});

}

void MainWindow::on_Timer1()
{
	SomeThing();
}
