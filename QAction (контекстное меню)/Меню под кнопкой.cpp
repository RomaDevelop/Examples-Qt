btnMenu = new QPushButton("Menu", this);
layOut->addWidget(btnMenu);
QMenu *menu = new QMenu(this);
connect(btnMenu,&QPushButton::clicked, [btnMenu, menu](){
	menu->exec(btnMenu->mapToGlobal(QPoint(0, btnMenu->height())));
});
QAction *action1 = new QAction("Проверка работоспособности", menu);
QAction *action2 = new QAction("Чтение паспорта", menu);
QAction *action3 = new QAction("Проверка номера блока и режимов работы каналов", menu);
menu->addAction(action1);
menu->addAction(action2);
menu->addAction(action3);
connect(action1, &QAction::triggered, this, &BKZ_psi::Slot1);
connect(action2, &QAction::triggered, this, &BKZ_psi::Slot2);
connect(action3, &QAction::triggered, this, &BKZ_psi::Slot3);