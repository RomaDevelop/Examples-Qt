for (int col = 0; col < table->columnCount(); ++col) 
{
	if(table->item(row, col))
		table->item(row, col)->setBackground(Qt::NoBrush);  // Сброс цвета фона
}


for (int col = 0; col < table.ptr->columnCount(); ++col) 
{
	if(table->item(row, col))
		table->setItem(row, col, new QTableWidgetItem);
	table->item(row, col)->setBackground(Qt::yellow); 	// окраска
}
