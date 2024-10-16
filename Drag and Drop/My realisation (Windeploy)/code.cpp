class Windeploy : public QMainWindow
{
	Q_OBJECT

public:
	Windeploy(QWidget *parent = nullptr);
	~Windeploy();

protected:
	void dragEnterEvent( QDragEnterEvent* event );
	void dropEvent( QDropEvent* event );

};

Windeploy::Windeploy(QWidget *parent)
	: QMainWindow(parent)
{
	setAcceptDrops(true);
}

void Windeploy::dragEnterEvent(QDragEnterEvent* event)
{
	if(event->mimeData()->hasText() && event->mimeData()->text().right(4) == ".exe")  // если это текст и если он оканчивается на .exe
		event->acceptProposedAction();
		
	// фильтр пропускает только один файл, поскольку если файлов несколько, они разделяются \n и в конце он тоже есть
	
}

void Windeploy::dropEvent(QDropEvent* event)
{
	QString droped = event->mimeData()->text();
	if(droped.mid(0,8) == "file:///") droped = droped.remove(0,8);
		else QMessageBox::warning(this,"Внимание", "Возможно неправильный формат файла. Проверьте и добавьте если нужно вручную!");
	droped.replace("/","\\");
	
	ui->listWidget->addItem(droped);
	//event->acceptProposedAction();  было в примере, но у меня это лишнее, строки выше делают всё что нужно
}