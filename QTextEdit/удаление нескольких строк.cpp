	
	QTextEdit  *objToClean;
	void SlotClean(int count)
	{
		QTextCursor cursor = objToClean->textCursor();
		cursor.setPosition(0);
		cursor.movePosition(QTextCursor::Down, QTextCursor::KeepAnchor, count);
		cursor.removeSelectedText();
		//cursor.deleteChar(); // clean up empty line
		
		
//		for(int i=0; i<100; i++)
//		{
//			QTextCursor cursor = ui->textBrowser->textCursor();
//			cursor.movePosition(QTextCursor::Start);
//			cursor.select(QTextCursor::LineUnderCursor);
//			cursor.removeSelectedText();
//			cursor.deleteChar(); // clean up empty line
			
//			altrnative way
//					QTextBlock b = ui->textBrowser->document()->findBlockByLineNumber(0);
//			if(b.isValid())
//			{
//				QTextCursor cursor(b);
//				cursor.select(QTextCursor::BlockUnderCursor);
//				cursor.removeSelectedText();
//				cursor.deleteChar(); // clean up empty line
//			}
//		}
	}