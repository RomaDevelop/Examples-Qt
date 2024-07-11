#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::on_pushButtonH_clicked()
{
	ui->tableWidget->horizontalHeader()->setStyleSheet(ui->textEditH->toPlainText());
	ui->tableWidget->horizontalHeader()->setFirstSectionMovable(true);
}

void MainWindow::on_pushButtonV_clicked()
{
	ui->tableWidget->verticalHeader()->setStyleSheet(ui->textEditV->toPlainText());
	ui->tableWidget->verticalHeader()->setFirstSectionMovable(true);
}

void MainWindow::on_pushButtonCW_clicked()
{
	не работает! cornerWidget() это от скроллЭриа
	//ui->tableWidget->cornerWidget()->setStyleSheet(ui->textEditCW->toPlainText());
}
