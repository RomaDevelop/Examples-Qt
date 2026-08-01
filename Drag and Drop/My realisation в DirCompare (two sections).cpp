class MainWindow : public ...
{
...

protected:
	void dragEnterEvent(QDragEnterEvent* event);
	void dragLeaveEvent(QDragLeaveEvent *event);
	void dragMoveEvent(QDragMoveEvent *event);
	void dropEvent(QDropEvent* event);
	QLineEdit *editDropIn {};

};

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	setAcceptDrops(true);
}

void MainWindow::dragEnterEvent(QDragEnterEvent * event)
{
	auto dropedObj = MyQDropEvent::GetDropedObject(event);
	if(dropedObj.type != DropedObjectType::dir)
	{
		event->ignore();
	}
	else
	{
		event->acceptProposedAction();
	}
	editDropIn = {};
}

void MainWindow::dragLeaveEvent(QDragLeaveEvent * event) {
	leftEdit->setStyleSheet({});
	rightEdit->setStyleSheet({});
	event->accept();
}

void MainWindow::dragMoveEvent(QDragMoveEvent * event)
{
	event->acceptProposedAction();

	if (event->pos().x() < this->width() / 2) {
		editDropIn = leftEdit;
	}
	else {
		editDropIn = rightEdit;
	}
	static QLineEdit *prevEdit {};

	if(editDropIn != prevEdit) editDropIn->setStyleSheet("background-color: #d4edda; border: 2px dashed #28a745;");
}

void MainWindow::dropEvent(QDropEvent * event)
{
	auto dropedObj = MyQDropEvent::GetDropedObject(event);
	if(dropedObj.error.isEmpty() == false)
	{
		QMbError("Ошибка обработки перетаскивания: "+dropedObj.error);
		return;
	}

	if(dropedObj.type != DropedObjectType::dir)
	{
		QMbError("Неподдерживаемый тип объекта: "+dropedObj.initialValue);
		return;
	}

	if(not editDropIn) { QMbError("null editDropIn"); return; }

	leftEdit->setStyleSheet({});
	rightEdit->setStyleSheet({});

	editDropIn->setText(dropedObj.fileInfo.filePath());
}