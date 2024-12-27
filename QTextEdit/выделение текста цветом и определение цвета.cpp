QTextCharFormat format;         
format.setForeground(Qt::darkGreen); // цвет текста   
format.setBackground(Qt::yellow); // цвет фона

auto curs = tBrowser->textCursor();
curs.movePosition(QTextCursor::End, QTextCursor::MoveAnchor);  // перемещение курсора и установка начала выделения. Можно и через setPosition
curs.setPosition(curs.position() - (str.length()), QTextCursor::KeepAnchor); // перемещение курсора вместе с выделением
curs.setCharFormat(format);     


// определяем текущий цвет
tBrowser->textCursor().charFormat().foreground();

// если цвет задаётся синтакс хайлайтером, то определить сложнее


