// вызывается при смене выбора ячеек
connect(table.ptr, &QTableWidget::itemSelectionChanged, &table, &TableWidget::CellSelection);
void TableWidget::CellSelection()
{
	if(!changeRowCountNow)
	{
		...
	}
	// else { если сигнал был послан во время changeRowCountNow, но ничего делать не надо }
}