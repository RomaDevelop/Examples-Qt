
// один виджет
tableWidget->setCellWidget(0,0,new QPushButton("test"));
qDebug() << ((QPushButton*)tableWidget->cellWidget(0,0))->text();

// группа
QWidget *w = new QWidget;
QHBoxLayout *hLao = new QHBoxLayout(w);
hLao->setSpacing(0); // убтирает расстояние между виджетами внутри Layout
hLao->setContentsMargins(0,0,0,0); // убтирает расстояние до края
hLao->addWidget(new QLineEdit);
hLao->addWidget(new QPushButton("test2"));

ui->tableWidget->setCellWidget(1,0,w);

# ВИДЖЕТ НЕВОЗМОЖНО ИЗЪЯТЬ ИЗ ТАБЛИЦЫ
# ЕСЛИ НА МЕСТО СУЩЕСТВУЮЩЕГО ВИДЖЕТА ЗАПИСАТЬ НОВЫЙ, СТАРЫЙ УНИЧТОЖАЕТСЯ
# Но, казалось бы, можно перемещать виджеты. Казалось бы даже из одной таблицы в другую.
# Но, ****, если на старое место виджета записать новый он, ****, умирает. Даже если он, ****, в другой, ****, таблице!!!

	auto t = new QTableWidget;
	t->show();
	t->setRowCount(5);
	t->setColumnCount(6);
	t->setCellWidget(0,0,new QLabel("0"));
	t->setCellWidget(0,1,new QLabel("1"));

	QObject::connect(t->cellWidget(0,0), &QWidget::destroyed, [](){ qdbg << 0; });
	QObject::connect(t->cellWidget(0,1), &QWidget::destroyed, [](){ qdbg << 1; });

	t->setCellWidget(0,0,new QLabel("0.1"));  // 0 будет уничтожен

	auto w = new QWidget;
	t->cellWidget(0,1)->setParent(w);
	t->setCellWidget(0,1,new QLabel("1.1")); // 1 все равно уничтожен