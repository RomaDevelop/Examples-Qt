В C++ для построения графиков в Qt самым удобным вариантом будет использование **QCustomPlot**. Это сторонняя библиотека, которая легко интегрируется с Qt и предлагает простой интерфейс для построения графиков.
 
### Основные шаги для использования QCustomPlot:
1. Скачайте библиотеку QCustomPlot с официального сайта (http://www.qcustomplot.com/).
2. Добавьте файлы **qcustomplot.h** и **qcustomplot.cpp** в свой проект.
3. Используйте виджет **QCustomPlot** для построения графиков.
 
Пример кода для отображения синусоиды:
 
```cpp
#include <QApplication>
#include "qcustomplot.h"
#include <cmath>
 
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
 
    QCustomPlot customPlot;
    QVector<double> x(1000), y(1000); // Векторы для хранения точек
 
    // Заполнение данными для синусоиды
    for (int i = 0; i < 1000; ++i)
    {
        x[i] = i / 100.0; // значения по оси x
        y[i] = sin(x[i]); // значения по оси y (синусоида)
    }
 
    // Добавление графика
    customPlot.addGraph();
    customPlot.graph(0)->setData(x, y);
    customPlot.xAxis->setLabel("x");
    customPlot.yAxis->setLabel("sin(x)");
    
    // Настройка диапазонов осей
    customPlot.xAxis->setRange(0, 10);
    customPlot.yAxis->setRange(-1, 1);
    
    // Отображение графика
    customPlot.resize(800, 600);
    customPlot.show();
 
    return app.exec();
}
```
 
Этот код создаёт окно с графиком синусоиды.
 
--
С уважением,
Мысливченко Роман
тел., WhatsApp: +7 (918) 861-46-99
