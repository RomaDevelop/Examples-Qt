#include "widget.h"

#include <QDebug>
#include <QPushButton>
#include <QHBoxLayout>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    auto vlo = new QVBoxLayout(this);
    auto hlo = new QHBoxLayout();
    vlo->addLayout(hlo);
    vlo->addStretch();

    auto btn = new QPushButton("btn");
    hlo->addWidget(btn);
    hlo->addStretch();
    
    connect(btn, &QPushButton::clicked, [](){
        qDebug() << "dfbdfbdfb";
    });

    resize(300,300);
}

Widget::~Widget()
{
}