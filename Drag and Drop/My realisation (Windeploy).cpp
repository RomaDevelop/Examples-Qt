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
	if(event->mimeData()->hasText())
	{
		event->acceptProposedAction();
	}
}

void Windeploy::dropEvent(QDropEvent* event)
{
	auto dropedObj = MyQDropEvent::GetDropedObject(event);
	if(dropedObj.error.isEmpty() == false)
	{
		QMbError("Ошибка обработки перетаскивания: "+dropedObj.error);
		return;
	}

	if(dropedObj.type != DropedObjectType::dir and dropedObj.type != DropedObjectType::file)
	{
		QMbError("Неподдерживаемый тип объекта: "+dropedObj.initialValue);
		return;
	}

	QString file = dropedObj.workedValue;

	if(!CheckKirillic(file)) return;

	QFileInfo fi(file);
	if(fi.isDir())
	{
		auto fiList = MyQFileDir::GetAllFilesIncludeSubcats(file, {"exe"});

		if(0) CodeMarkers::to_do("а нужно еще и каждый файл проверить на CheckKirillic!");

		if(fiList.size() == 0) { QMbInfo("В директории \n\n["+file+"]\n\nотсутсвуют исполняемые файлы"); return; }
		else if(fiList.size() == 1) file = fiList.first().filePath();
		else
		{
			if(0) CodeMarkers::to_do("из-за того что ListDialog вызывается прямо в dropEvent место откуда "
									 "вызвали зависает можно создать слот и там самым сделать развязку");

			auto filesList = MyQFileDir::FileInfoListToStrList(fiList);
			auto res = MyQDialogs::ListDialog("Choose executable file", filesList);
			file = res.chosenText;
			if(file.isEmpty()) { QMbInfo("Не выбраны файлы"); return; }
		}
	}

	if(CheckFile(file))
	{
		ui->editFile->clear();
		ui->editFile->setText(file);
	}
}