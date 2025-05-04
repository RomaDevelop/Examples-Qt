std::unique_ptr<QDialog> dialog(new QDialog);
QVBoxLayout *all  = new QVBoxLayout(dialog.get());
QScrollArea *scrollArea = new QScrollArea;
all->addWidget(scrollArea);
auto widgetInScrollArea = new QWidget;
scrollArea->setWidget(widgetInScrollArea);     	// обязательно нужно создать в scrollArea виджет, а уже в него помещать лэйауты
scrollArea->setWidgetResizable(true);			// если виджеты добавляются динамически, то обязательно
auto loInScrollArea = new QGridLayout(widgetInScrollArea);