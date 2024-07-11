#include "parentwidjet.h"
#include "mainwindow.h"
#include "calcwindow.h"

#include <QApplication>
#include <QLabel>


int main(int argc, char *argv[])
{
    //Создаём объект QApplication, который инициализирует и настраивает оконную программу,
    //управляет её выполнением с помощью цикла обработки событий
    QApplication lApplication ( argc , argv ) ;

	MainWindow MainWindow1 ;
    //Переместить окно в точку экрана с координатами 100, 200
	MainWindow1.move (50 , 50) ;
	MainWindow1.show () ;

    //ParentWidjet * lParentWidget=new ParentWidjet();
    //Переместить окно в точку экрана с координатами 100, 200
    //lParentWidget->move (100 , 200) ;
    //lParentWidget->show () ;

	//CalcWindow *CalcWindow1 = new CalcWindow();
	//CalcWindow1->show();

    return lApplication.exec () ; //Запускаем программу на выполнение exec() выполняет
    //цикл обработки событий. Программа ожидает действия пользователя и выполняет их обработку.
}
