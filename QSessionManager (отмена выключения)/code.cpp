#include <QSessionManager>

connect(qApp, &QGuiApplication::commitDataRequest, this, [](QSessionManager &manager) {
	if (manager.allowsInteraction()) {
		// Вызов системного окна блокировки
		manager.release();
		// Отмена выключения
		manager.cancel();
	}
}, Qt::DirectConnection);

/*

Чтобы это работало должно быть:
HKEY_CURRENT_USER\Control Panel\Desktop
там должен быть строковый параметр AutoEndTasks
значение должно быть 0
еще там должен быть строковый параметр  WaitToKillAppTimeout
его значение - это тайминг в мс ожидания перед принудительным закрытием
например 10000 = 10 секунд

*/

// функция создает сигнал и проверяет настройки в реестре и выставляет их по подтверждению пользователя
void WidgetMain::InitAndCheckShutdownBlock()
{
	connect(qApp, &QGuiApplication::commitDataRequest, this, [](QSessionManager &manager) {
		if (manager.allowsInteraction()) {
			// Вызов системного окна блокировки
			manager.release();
			// Отмена выключения
			manager.cancel();
		}
	}, Qt::DirectConnection);

	QSettings settings("HKEY_CURRENT_USER\\Control Panel\\Desktop", QSettings::NativeFormat);
	QStringList problems;
	bool exists = settings.contains("AutoEndTasks") and settings.contains("WaitToKillAppTimeout");
	if(not exists) problems += "настройки не обнаружены (одна или обе)";
	else
	{
		QString valueAutoEndTasks = settings.value("AutoEndTasks").toString();
		QString valueWaitToKillAppTimeout = settings.value("WaitToKillAppTimeout").toString();

		if(valueAutoEndTasks != "0")
			problems += "включен парамер завершения без запроса";
		if(valueWaitToKillAppTimeout.toInt() < 1000*60*5)
			problems += "малый тайминг ожидания ("+valueWaitToKillAppTimeout+" мс)";
	}

	if(not problems.isEmpty())
	{
		auto answ = QMbq({}, "Ожидание при выключении",
				"С настройками ожидания при выключении компьютера обнаружены проблемы:\n" +problems.join('\n')
				+"\n\nВыставить корректные значения (ожидать 5 минут)?");
		if(answ == QMessageBox::Yes)
		{
			settings.setValue("AutoEndTasks", "0");
			settings.setValue("WaitToKillAppTimeout", QSn(1000*60*5));
		}
	}
}