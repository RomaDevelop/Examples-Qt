#include "widget.h"

#include <QLabel>
#include <QVBoxLayout>

#include "MyCppDifferent.h"
#include "MyQDifferent.h"

struct StructInCpp
{
	QString name = "";
	StructInCpp(QString name): name{name} {}
};

Widget::Widget(QWidget *parent)
	: QWidget(parent)
{
	//QVBoxLayout *vlo = new QVBoxLayout(this);
	//QLabel *l = new QLabel;
	//vlo->addWidget(l);
}

Widget::~Widget()
{
}

void Widget::TestSignalsInCpp()
{
	connect(this, &Widget::SignalTestStructInCppShPtr, this, [this](std::shared_ptr<StructInCpp> dataShPtr){
		signalsGetedInCpp += dataShPtr->name;
	});
	emit SignalTestStructInCppShPtr(std::make_shared<StructInCpp>(signalsToSendInCpp[0]));
}

