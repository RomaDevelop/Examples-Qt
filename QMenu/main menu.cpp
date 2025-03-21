void WidgetCatalog::CreateMainMenu(QLayout *lo)
{
	QMenuBar *menuBar = new QMenuBar(this);
	lo->setMenuBar(menuBar);
	QMenu *baseMenu = menuBar->addMenu("База данных");
	baseMenu->addAction("Открыть");
	baseMenu->addAction("Выход");
}