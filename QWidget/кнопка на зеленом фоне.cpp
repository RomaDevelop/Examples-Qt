// через QPalette
QWidget *widget = new QWidget;
QPalette pal = widget->palette();
pal.setColor(QPalette::Window, Qt::green);
widget->setAutoFillBackground(true);
widget->setPalette(pal);

QPushButton *button = new QPushButton("Нажми", widget);

widget->resize(200, 100);
button->move(50, 30);

widget->show();

// через setStyleSheet
QWidget *cw = new QWidget;
cw->setObjectName("myCellWidget");
cw->setStyleSheet("#myCellWidget { background-color: green; }");

QPushButton *btn = new QPushButton("Click", cw);

cw->resize(200, 100);
btn->move(50, 30);

cw->show();