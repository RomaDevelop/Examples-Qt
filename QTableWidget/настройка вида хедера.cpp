
// на форуме:
table.horizontalHeader()->setStyleSheet("QHeaderView::section:horizontal{"
                                        "background: gray;"
                                        "color: white;"
                                        "}"
                                        "QHeaderView{
                                        "border-style: none;
                                        "border-bottom: 3px solid red;
                                        "}
									
// я сделяль									
table->horizontalHeader()->setStyleSheet("QHeaderView { border-style: none; border-bottom: 1px solid gray; }");

// текст в шапке таблицы (ru.stackoverflow.com/questions/1350991/Как-установить-названия-столбцов-в-виджете-qtablewidget)
ptr->setHorizontalHeaderLabels(colNames);


QHeaderView::section:horizontal{
border-style: none;
border-right: 1px solid grey;
}
QHeaderView{
border-style: none;
border-bottom: 1px solid grey;
}

QHeaderView::section:vertical{
border-style: none;
border-bottom: 1px solid grey;
}
QHeaderView{
border-style: none;
border-right: 1px solid grey;
}