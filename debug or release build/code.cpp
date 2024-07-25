#ifdef QT_NO_DEBUG
	qDebug() << "QT_NO_DEBUG";  //сработет если сборка "Выпуск"
#endif
#ifdef QT_DEBUG
	qDebug() << "QT_DEBUG";		//сработет если сборка "Отладка"
#endif