#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "test_dll.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	Test_dll dll;
	ui->label->setText("Test_dll dll.Get5() = " + QString::number(dll.Get5()));
}

MainWindow::~MainWindow()
{
	delete ui;
}

