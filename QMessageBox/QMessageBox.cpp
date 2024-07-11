if(QMessageBox::question(nullptr, "Заголовок", "Текст", QMessageBox::Yes|QMessageBox::No) == QMessageBox::No)
	return;



QMessageBox messageBox(QMessageBox::Question, "Заголовок", "Текст");
messageBox.addButton("Кнопка1",QMessageBox::YesRole);  // Role не имеет значения
messageBox.addButton("Кнопка2",QMessageBox::YesRole);
messageBox.addButton("Отмена",QMessageBox::NoRole);
int desision =  messageBox.exec(); // возвращает 0 1 2 по порядку кнопок
if(messageBox.buttons()[desision]->text() == "Кнопка1") // кликнутый копируем на место всех
{
	
}
else if(messageBox.buttons()[desision]->text() == "Кнопка2") // кликнутый заменяем самым новым
{

}
else if(messageBox.buttons()[desision]->text() == "Отмена") ;  // Ничего
else QMb(this,"Error","Error code 50002");