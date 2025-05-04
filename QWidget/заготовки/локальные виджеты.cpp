//------------------------------------------------
// QDialog -> QHBoxLayout
QDialog *dialog = new QDialog;
QHBoxLayout *vloMain  = new QHBoxLayout(dialog);
QTextBrowser *tb = new QTextBrowser;
tb->setPlainText("text");
vloMain->addWidget(tb);

dialog->exec();
delete dialog;
//------------------------------------------------
// QDialog -> QVBoxLayout
QDialog *dialog = new QDialog;
QVBoxLayout *vloMain  = new QVBoxLayout(dialog);
QTextBrowser *tb = new QTextBrowser;
tb->setPlainText("text");
vloMain->addWidget(tb);

dialog->exec();
delete dialog;
//------------------------------------------------
// QDialog -> QGridLayout -> widgets + QHBoxLayout(Ok, Cansel)
QDialog *dialog = new QDialog;
QGridLayout *grloMain  = new QGridLayout(dialog);

grloMain->addWidget(new QLabel("Каталог проекта"),0,0);
grloMain->addWidget(new QLabel("Наименование проекта"),1,0);
grloMain->addWidget(new QLabel("Шаблон проекта"),2,0);

auto loHbuttons = new QHBoxLayout;
grloMain->addLayout(loHbuttons, 3, 0, 1, -1);
loHbuttons->addStretch();
auto btnOk = new QPushButton("Ok");
connect(btnOk, &QPushButton::clicked, [dialog](){
	// ok code
	dialog->close();
});
auto btnCansel = new QPushButton("Отмена");
connect(btnCansel, &QPushButton::clicked, [dialog](){
	dialog->close();
});
loHbuttons->addWidget(btnOk);
loHbuttons->addWidget(btnCansel);

dialog->exec();
delete dialog;
//------------------------------------------------