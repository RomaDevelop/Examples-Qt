	
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