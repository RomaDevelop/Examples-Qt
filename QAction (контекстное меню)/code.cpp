	QAction *mOpen = new QAction("mOpen", ui->tableWidget);
	QAction *mShowInExplorer = new QAction("mShowInExplorer", ui->tableWidget);
	ui->tableWidget->addAction(mOpen);
	ui->tableWidget->addAction(mShowInExplorer);
	ui->tableWidget->setContextMenuPolicy(Qt::ActionsContextMenu);
	connect(mOpen, &QAction::triggered, [](){qdbg << "mOpen";});
	connect(mShowInExplorer, &QAction::triggered, [](){qdbg << "mShowInExplorer";});