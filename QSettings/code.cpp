
void Widget::readSettingsQSetting()
{
	QSettings settings("MyCompany", "MyApp");
	tree->restoreGeometry(settings.value("treeGeo").toByteArray());

	qDebug() << "readSettings: tree->width = " << tree->width();
}

void Widget::writeSettingsQSetting()
{
	qDebug() << "writeSettingsQSetting: tree->width = " << tree->width();
	QSettings settings("MyCompany", "MyApp");
	settings.setValue("treeGeo", tree->saveGeometry());
}

группы настроек
	settings.beginGroup("gr1");
	settings.setValue("key","value in gr 1 k\"\"\"\"\n\ney");
	settings.endGroup();
	
	при чтении тоже самое
	settings.beginGroup("gr1");
	settings.value("key").toString();
	settings.endGroup();