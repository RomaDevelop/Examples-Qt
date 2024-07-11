auto curs = tBrowser->textCursor();
curs.movePosition(QTextCursor::End, QTextCursor::MoveAnchor);  // перемещение курсора и установка начала выделения. Можно и через setPosition
curs.setPosition(curs.position() - (str.length()), QTextCursor::KeepAnchor); // перемещение курсора вместе с выделением

QTextCharFormat format;         
format.setForeground(Qt::darkGreen); // цвет текста   
format.setBackground(Qt::yellow); // цвет фона
curs.setCharFormat(format);     


void SetColor(QTextEdit *textEdit, int from, int to, const QColor &color)
{
	qdbg << from << to << textEdit->toPlainText().size();
	auto cursor = textEdit->textCursor();
	cursor.setPosition(from,QTextCursor::MoveAnchor);
	cursor.setPosition(to,QTextCursor::KeepAnchor);
	QTextCharFormat format;
	format.setForeground(color);
	cursor.setCharFormat(format);
}