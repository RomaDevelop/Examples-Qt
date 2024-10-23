//------------------------------------------------
// QDialog -> QHBoxLayout
QDialog *dialog = new QDialog;
QHBoxLayout *all  = new QHBoxLayout(dialog);
QTextBrowser *tb = new QTextBrowser;
tb->setPlainText("text");
all->addWidget(tb);

dialog->exec();
delete dialog;
//------------------------------------------------
// QDialog -> QVBoxLayout
QDialog *dialog = new QDialog;
QVBoxLayout *all  = new QVBoxLayout(dialog);
QTextBrowser *tb = new QTextBrowser;
tb->setPlainText("text");
all->addWidget(tb);

dialog->exec();
delete dialog;
//------------------------------------------------
// QDialog -> QGridLayout -> widgets + QHBoxLayout(Ok, Cansel)
QDialog *dialog = new QDialog;
QGridLayout *loGmain  = new QGridLayout(dialog);

loGmain->addWidget(new QLabel("Каталог проекта"),0,0);
loGmain->addWidget(new QLabel("Наименование проекта"),1,0);
loGmain->addWidget(new QLabel("Шаблон проекта"),2,0);

auto loHbuttons = new QHBoxLayout;
loGmain->addLayout(loHbuttons, 3, 0, 1, -1);
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