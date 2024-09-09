auto tabWidget = new QTabWidget;
QStringList tabNames = {"1", "2", "3"};
for(auto &tname:tabNames)
{
	QWidget* tab = new QWidget;
	tab->setObjectName(tname);
	tab->setAutoFillBackground(true);
	tabWidget->addTab(tab,tname);
}