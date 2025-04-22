void TimerWindow::CreateTrayIcon()
{
	if(icon)
		QMbc(this,"Error","CreateTrayIcon multiple times");

	icon = new QSystemTrayIcon(this);
	icon->setIcon(QApplication::style()->standardIcon(QStyle::SP_BrowserReload));
	icon->setToolTip("Timer");
	icon->show();
	
	QMenu *menu = new QMenu(this);
	icon->setContextMenu(menu);
	
	connect(icon, &QSystemTrayIcon::activated, [icon, showFoo](QSystemTrayIcon::ActivationReason reason){
		if(reason == QSystemTrayIcon::Trigger) show();
		if(reason == QSystemTrayIcon::Context) icon->contextMenu()->exec();
	});
	
	menu->addAction("Show Notes");
	connect(menu->actions().back(), &QAction::triggered, showFoo);

	menu->addAction("Create new note");
	connect(menu->actions().back(), &QAction::triggered, [this](){ SlotCreationNewNote(); });
}