#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QAxObject> // в .pro нужно QT += axcontainer
#include <QDebug>

#include "MyQShortings.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	QAxObject* excel = new QAxObject("Excel.Application", 0);
	QAxObject* workbooks = excel->querySubObject("Workbooks");
	QAxObject* workbook = workbooks->querySubObject("Open(const QString&)", "F:\\C++\\00 Examples QT\\QAxObject (Excel)\\QAxObject\\Test.xlsx");
	QAxObject* sheets = workbook->querySubObject("Worksheets");
	QAxObject* sheet = sheets->querySubObject("Item(int)", 1);

	qdbg << sheets->property("Count").toInt();

	QAxObject* usedRange = sheet->querySubObject("UsedRange");
	QAxObject* rows = usedRange->querySubObject("Rows");
	int countRows = rows->property("Count").toInt();
	qdbg << countRows;

	QAxObject* columns = usedRange->querySubObject("Columns");
	int countCols = columns->property("Count").toInt();
	qdbg << countCols;

	QAxObject* cell;
	for(int r=1; r<=10; r++)
		for(int c=1; c<=10; c++)
		{
			cell = sheet->querySubObject("Cells(int,int)", c, r);
			QVariant value = cell->property("Value");
			QString cellValue = value.toString();
			if(cellValue!="") qdbg << c << r << cellValue;
		}

	cell = sheet->querySubObject("Cells(int,int)", 4, 4);
	cell->setProperty("Value","sdfgsdv5464564s111d");

	workbook->dynamicCall("Save()");
	workbook->dynamicCall("Close()");
	excel->dynamicCall("Quit()");
}

MainWindow::~MainWindow()
{
	delete ui;
}

