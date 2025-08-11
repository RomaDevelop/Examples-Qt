#include "widget.h"

#include <QApplication>
#include <QDebug>
#include <QtCharts>

#include "MyQShortings.h"
#include "MyCppDifferent.h"
#include "thread_box.h"

#include "MyQTimer.h"
#include "MyQDialogs.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	//Widget w;
	//w.show();

	QMainWindow w;

	// Создание данных для графика
	QLineSeries *series = new QLineSeries();
	for(float x=-10; x<=10; x+=0.1)
		series->append(x, x*x);

	// Создание графика
	QChart *chart = new QChart();
	chart->addSeries(series);
	chart->setTitle("Пример линейного графика");
	chart->createDefaultAxes();

	// Создание виджета для отображения графика
	QChartView *chartView = new QChartView(chart);
	chartView->setRenderHint(QPainter::Antialiasing);

	// Установка виджета в главное окно
	w.setCentralWidget(chartView);
	w.resize(800, 600);
	w.show();

	return a.exec();
}
