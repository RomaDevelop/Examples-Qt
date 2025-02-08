//	QMenu *menu = new QMenu(tableView);
//	tableView->setContextMenuPolicy(Qt::CustomContextMenu);
//	connect(tableView, &QTableView::customContextMenuRequested, [menu, this](const QPoint &pos) {
//		menu->exec(tableView->viewport()->mapToGlobal(pos));
//	});
//	connect(menu, &QMenu::triggered, [](QAction *action){ qDebug() << "QMenu::triggered " << action->text(); });

//	QAction *action1 = menu->addAction("Обычное действие");
//	connect(action1, &QAction::triggered, [&]() { qDebug("Обычное действие выполнено"); });

//	// Сепаратор
//	menu->addSeparator();

//	// Подменю
//	QMenu *subMenu = menu->addMenu("Субменю");
//	QAction *subAction1 = subMenu->addAction("Подпункт 1");
//	connect(subAction1, &QAction::triggered, [&]() { qDebug("Подпункт 1 выполнен"); });
//	QAction *subAction2 = subMenu->addAction("Подпункт 2");
//	connect(subAction2, &QAction::triggered, [&]() { qDebug("Подпункт 2 выполнен"); });


	QMenu *subMenuAdditional = new QMenu("Submenu", this);

	tableView->setContextMenuPolicy(Qt::ActionsContextMenu);
	tableView->addAction(new QAction("Открыть файл", this));
	tableView->addAction(new QAction("Открыть расположение файла", this));
	tableView->addAction(new QAction("Содержание и логи", this));
	tableView->addAction(new QAction("", this));
	tableView->actions().back()->setSeparator(true);
	tableView->addAction(new QAction("Дополнительно", this));
	tableView->actions().back()->setMenu(subMenuAdditional);
	tableView->addAction(new QAction("", this));
	tableView->actions().back()->setSeparator(true);
	tableView->addAction(new QAction("Переместить", this));
	tableView->addAction(new QAction("Копировать", this));
	tableView->addAction(new QAction("", this));
	tableView->actions().back()->setSeparator(true);
	tableView->addAction(new QAction("Переименовать", this));
	tableView->addAction(new QAction("Удалить из базы", this));
	tableView->addAction(new QAction("Удалить с диска и из базы", this));
	tableView->addAction(new QAction("", this));
	tableView->actions().back()->setSeparator(true);
	tableView->addAction(new QAction("Добавить к редактируемым", this));
	tableView->addAction(new QAction("Добавить в список воспроизведения", this));
	tableView->actions().back()->setShortcut(Qt::CTRL + Qt::Key_A);
	connect(tableView->actions().back(), &QAction::triggered, this, []() {
				qdbg << "You pressed Ctrl + A";
			});

	subMenuAdditional->addAction(new QAction("Обновить превью", this));
	subMenuAdditional->addAction(new QAction("Открыть расположение превью", this));
	subMenuAdditional->addAction(new QAction("Задать превью вручную", this));
	subMenuAdditional->addAction(new QAction("", this));
	subMenuAdditional->actions().back()->setSeparator(true);
	subMenuAdditional->addAction(new QAction("Открыть расположение файла описания", this));
	subMenuAdditional->addAction(new QAction("", this));
	subMenuAdditional->actions().back()->setSeparator(true);
	subMenuAdditional->addAction(new QAction("Пересчитать размер", this));
	subMenuAdditional->addAction(new QAction("Пересчитать длительность", this));