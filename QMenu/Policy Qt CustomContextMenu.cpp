// Policy Qt::CustomContextMenu
treeWidget->setContextMenuPolicy(Qt::CustomContextMenu); // Устанавливаем политику контекстного меню

QMenu menu(treeWidget);
QObject::connect(&menu, &QMenu::triggered, [](QAction *action){qDebug() << "QMenu::triggered " << action->text();});

QAction *myAction = menu.addAction("Мое действие");
QObject::connect(myAction, &QAction::triggered, [](){qDebug() << "myAction";});

menu->addSeparator();

// перехват сигнала вызова меню
QObject::connect(treeWidget, &QTreeWidget::customContextMenuRequested, [](const QPoint& pos) {
		qDebug() << "Контекстное меню вызвано";
		//menu.exec(treeWidget->mapToGlobal(pos));  // выводится выше на заголовок формы
		menu->exec(treeWidget->viewport()->mapToGlobal(pos))
	});
