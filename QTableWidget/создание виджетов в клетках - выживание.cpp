# ВИДЖЕТ НЕВОЗМОЖНО ИЗЪЯТЬ ИЗ ТАБЛИЦЫ
# ЕСЛИ НА МЕСТО СУЩЕСТВУЮЩЕГО ВИДЖЕТА ЗАПИСАТЬ НОВЫЙ, СТАРЫЙ УНИЧТОЖАЕТСЯ
# Но, казалось бы, можно перемещать виджеты. Казалось бы даже из одной таблицы в другую.
# Но, ****, если на старое место виджета записать новый он, ****, умирает. 
# Хоть если он, ****, в другой, хоть в той же, ****, таблице!!!

	auto t = new QTableWidget;
	t->show();
	t->setRowCount(5); t->setColumnCount(6);
	t->setCellWidget(0,0, new QLabel("0"));
	t->setCellWidget(0,1, new QLabel("1"));
	t->setCellWidget(0,2, new QLabel("2"));
	t->setCellWidget(0,3, new QLabel("3"));
	t->setCellWidget(0,4, new QLabel("4"));
	t->setCellWidget(0,5, new QLabel("5"));

	QObject::connect(t->cellWidget(0,0), &QWidget::destroyed, [](){ qdbg << 0; });
	QObject::connect(t->cellWidget(0,1), &QWidget::destroyed, [](){ qdbg << 1; });
	QObject::connect(t->cellWidget(0,2), &QWidget::destroyed, [](){ qdbg << 2; });
	QObject::connect(t->cellWidget(0,3), &QWidget::destroyed, [](){ qdbg << 3; });
	QObject::connect(t->cellWidget(0,4), &QWidget::destroyed, [](){ qdbg << 4; });
	QObject::connect(t->cellWidget(0,5), &QWidget::destroyed, [](){ qdbg << 5; });

	t->setCellWidget(0,0,new QLabel("0.1"));  // 0 будет уничтожен

	auto w = new QWidget;
	t->cellWidget(0,1)->setParent(w);
	t->setCellWidget(0,1,new QLabel("1.1")); // 1 все равно уничтожен
	
	t->setCellWidget(0,1,t->cellWidget(0,5)); // 5 пока жив
	t->setCellWidget(0,5,new QLabel("5.2")); // 5 будет мертв

	auto t2 = new QTableWidget;
	t2->setColumnCount(10); t2->setRowCount(1);
	t2->show();

	t2->setCellWidget(0,0, t->cellWidget(0,2)); // 2 ВЫЖИВАЕТ
	t2->setCellWidget(0,1, t2->cellWidget(0,0)); // 2 УМИРАЕТ

	t2->setCellWidget(0,1, t->cellWidget(0,3));
	t2->setCellWidget(0,1, new QLabel("3.1")); // 3 уничтожен