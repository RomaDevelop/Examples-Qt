#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QThread>
#include <QDebug>

class WorkerThread : public QThread
{
	void run() override
	{
		int i = 1;
		while(i++)
		{
		qDebug()<< "WorkerThread::run(" + QString::number(i) + ")";
		QThread::msleep(100);
		}
	}
};

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	WorkerThread *workerThread = new WorkerThread;
	workerThread->start();
}

MainWindow::~MainWindow()
{
	delete ui;
}

