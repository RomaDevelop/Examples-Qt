tableView->setContextMenuPolicy(Qt::ActionsContextMenu);

tableView->addAction(new QAction("Открыть файл", this));

// сепаратор
menu->addSeparator();
// но если не в меню, а прям в виджет, то только так
tableView->addAction(new QAction("", this));
tableView->actions().back()->setSeparator(true);


tableView->addAction(new QAction("Дополнительно", this));
QMenu *subMenuAdditional = new QMenu("Submenu", this);
tableView->actions().back()->setMenu(subMenuAdditional);

subMenuAdditional->addAction(new QAction("Обновить превью", this));
subMenuAdditional->addAction(new QAction("Открыть расположение превью", this));
	
connect(actionPtr, &QAction::triggered, this, []() {
	qdbg << "You pressed Ctrl + A";
	});
	
	
// shortcut (только отображение)
cutAction->setShortcut(QKeySequence::Cut);
copyAction->setShortcut(QKeySequence::Copy);
pasteAction->setShortcut(QKeySequence::Paste);