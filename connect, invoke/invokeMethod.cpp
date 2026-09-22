QMetaObject::invokeMethod(object, [object, i](){
	object->textEdit->append(QSn(i));
});

QMetaObject::invokeMethod(object, [object](){}, Qt::BlockingQueuedConnection);
// Qt::BlockingQueuedConnection - чтобы код выполнился в основном потоке, но этот поток был заморожен, пока не выполнится
	
// чтобы не созхдавать object если под рукой нету можно использовать макрос qApp:
QMetaObject::invokeMethod(qApp, [](){}, Qt::BlockingQueuedConnection);