// может перекрывать горячие клавиши других виджетов в приложении (текст браузер у меня перехватывало)
	// можно еще потестировать
addAction(createAction(tr("Cut"), QKeySequence::Cut, this, SLOT(cut())));
addAction(createAction(tr("Copy"), QKeySequence::Copy, this, SLOT(copy())));
addAction(createAction(tr("Paste"), QKeySequence::Paste, this, SLOT(paste())));

// в пределах виджета, но нужно получается наследовать
void keyPressEvent(QKeyEvent *event) override
{
	if (event->matches(QKeySequence::Cut)) cut();
	else if (event->matches(QKeySequence::Copy)) copy();
	else if (event->matches(QKeySequence::Paste)) paste();
	QTableWidget::keyPressEvent(event);
}