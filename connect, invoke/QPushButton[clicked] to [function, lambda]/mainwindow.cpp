#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow *mwGlob;
void func()
{
	QMessageBox::information(mwGlob,"Hi","Hello func()");
}

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	mwGlob = this;

	// connect(ui->pushButtonSlot,SIGNAL(clicked()),this,SLOT(SlotQMBi()));  // old style
	connect(ui->pushButtonSlot,&QPushButton::clicked,this,&MainWindow::SlotQMBi);

	// лямбда (возможны проблемы если emit будет делаться не из главного потока
	connect(ui->pushButtonLambda, &QPushButton::clicked,
		[this](){QMessageBox::information(this,"Hi","Hello лямбда");});

	// указатель на функцию
	connect(ui->pushButtonFuncPtr, &QPushButton::clicked, func);
	
	// QTimer -> лямбда
	connect(servisTimer, &QTimer::timeout,[](){qdbg << "servisTimer";});
}

MainWindow::~MainWindow()
{
	delete ui;
}


