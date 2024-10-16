//Policy Qt::ActionsContextMenu

QAction *mOpen = new QAction("mOpen", ui->tableWidget);
QAction *mShowInExplorer = new QAction("mShowInExplorer", ui->tableWidget);  // указание parent обязательно, потому что "The ownership of action is not transferred to this QWidget."
ui->tableWidget->addAction(mOpen);
ui->tableWidget->addAction(mShowInExplorer);
ui->tableWidget->setContextMenuPolicy(Qt::ActionsContextMenu);
connect(mOpen, &QAction::triggered, [](){qdbg << "mOpen";});
connect(mShowInExplorer, &QAction::triggered, [](){qdbg << "mShowInExplorer";});
	
//Policy Qt::CustomContextMenu
treeWidget->setContextMenuPolicy(Qt::CustomContextMenu); // Устанавливаем политику контекстного меню

QMenu menu(treeWidget);
QObject::connect(&menu, &QMenu::triggered, [](QAction *action){qDebug() << "QMenu::triggered " << action->text();});

QAction *myAction = menu.addAction("Мое действие");
QObject::connect(myAction, &QAction::triggered, [](){qDebug() << "myAction";});

QObject::connect(treeWidget, &QTreeWidget::customContextMenuRequested, [&](const QPoint& pos) {
		qDebug() << "Контекстное меню вызвано";
		menu.exec(treeWidget->mapToGlobal(pos));
	});