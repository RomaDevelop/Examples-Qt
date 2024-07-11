#include "calcwindow.h"
#include <QPushButton>
#include <QGridLayout>
#include <QLCDNumber>

CalcWindow::CalcWindow(QWidget *parent) : QWidget(parent)
{
    QGridLayout *CalcLayout = new QGridLayout ;
    setLayout ( CalcLayout ) ;

    QPushButton *Btn0[10];
    for(int i=0; i<10; i++)
    {
        Btn0[i]=new QPushButton;
        Btn0[i]->setText(QString::number(i));
        Btn0[i]->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);
    }

    int btn_i=1;
    for(int i=0; i<3; i++)
        for(int j=0; j<3; j++)
            CalcLayout->addWidget(Btn0[btn_i++],i,j);

    QLCDNumber *lcdNumber = new QLCDNumber ;
    CalcLayout->addWidget(lcdNumber,4,0,1,3);
    //lcdNumber->setFixedHeight (50) ;

    //setGeometry ( x ( ) , y ( ) , 300 , 150) ;
    resize (300 , 300) ;


    setWindowTitle ( "Calculator" ) ;




}
