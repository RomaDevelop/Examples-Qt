#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();

private slots:
	void on_Timer1();

	void on_pushButtonStartT1_clicked();

	void on_pushButtonStopT1_clicked();

	void on_pushButtonStartT2_clicked();

	void on_pushButtonStopT2_clicked();

private:
	Ui::MainWindow *ui;

public:
	QTimer *Timer1;
};
#endif // MAINWINDOW_H
