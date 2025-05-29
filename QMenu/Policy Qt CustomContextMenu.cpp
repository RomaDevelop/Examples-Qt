// Policy Qt::CustomContextMenu
treeWidget->setContextMenuPolicy(Qt::CustomContextMenu); // Устанавливаем политику контекстного меню

QMenu *menu(treeWidget);
// обработка сигнала вызова меню
QObject::connect(treeWidget, &QWidget::customContextMenuRequested, [menu](const QPoint& pos) {
		qDebug() << "Контекстное меню вызвано";
		//menu.exec(treeWidget->mapToGlobal(pos));  // выводится выше на заголовок формы
		menu->exec(treeWidget->viewport()->mapToGlobal(pos))
	});
	

QObject::connect(menu, &QMenu::triggered, [](QAction *action){qDebug() << "QMenu::triggered " << action->text();});

QAction *myAction = menu->addAction("Мое действие");
QObject::connect(myAction, &QAction::triggered, [](){qDebug() << "myAction";});

menu->addSeparator();

// shortcut 
action1->setShortcut(QKeySequence::Cut);
action2->setShortcut(Qt::CTRL + Qt::Key_Q)
// !!! чтобы работали нужно еще и сделать
widget->addAction(action1); // к тому виджету где они должны работать
widget->addAction(action2);