#include "mainwindow.h"

#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QLabel>
#include <QGroupBox>


MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
	QPushButton *btn1 = new QPushButton("btn1") ;
	QLabel *label1 = new QLabel("label1") ;
	QGroupBox *grBox = new QGroupBox("grBox") ;
	QPushButton *btn2 = new QPushButton("btn2", grBox);
	btn2->move(0,20);

	QHBoxLayout *LayoutH = new QHBoxLayout ;
	QVBoxLayout *LayoutV = new QVBoxLayout ;

	LayoutH->addWidget(label1);
	LayoutH->addStretch () ;  //Добавим элемент-растяжку он займёт всё возможное свободное пространство и "прижмёт" кнопки к краю
	LayoutH->addWidget(btn1);

	LayoutV->addLayout(LayoutH) ;

	// https://stackoverflow.com/questions/72763764/add-qgroupbox-to-the-top-of-an-qhboxlayout
	// (написано нужно в параметры 1,0)
	LayoutV->addWidget(grBox, 1);

	//grBox->setLayout();

    //Задаём компоновщик для окна
	setLayout (LayoutV) ;

	connect(btn1,SIGNAL(clicked()),this, SLOT(on_pushButton_clicked1()));
}

void MainWindow::on_pushButton_clicked1()
{
	QMessageBox::information(this,"title","text");
}
