#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);


	// ручной коннект
	connect(ui->listWidget, SIGNAL(itemClicked(QListWidgetItem*)),
			this, SLOT(itemClicked(QListWidgetItem*)));

	connect(ui->listWidget, SIGNAL(clicked(const QModelIndex&)),
			this, SLOT(clicked(const QModelIndex&)));
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::itemClicked(QListWidgetItem* item) // слот ручного коннекта
{
	ui->textEdit->append("itemClicked; text = " + item->text());
}

void MainWindow::clicked(const QModelIndex &index) // слот ручного коннекта
{
	ui->textEdit->append("clicked; index = " + QString::number(index.row()));
}

void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item)  // слот авто коннекта
{
	ui->textEdit->append("on_listWidget_itemClicked; text = " + item->text());
}

void MainWindow::on_listWidget_clicked(const QModelIndex &index)   // слот авто коннекта
{
	ui->textEdit->append("on_listWidget_clicked; index = " + QString::number(index.row()));
}
