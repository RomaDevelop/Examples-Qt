std::unique_ptr<QDialog> dialog(new QDialog);
QVBoxLayout *all  = new QVBoxLayout(dialog.get());
QScrollArea *scrollArea = new QScrollArea;
all->addWidget(scrollArea);
auto widgetInScrollArea = new QWidget;
scrollArea->setWidget(widgetInScrollArea);
scrollArea->setWidgetResizable(true);
auto loInScrollArea = new QGridLayout(widgetInScrollArea);