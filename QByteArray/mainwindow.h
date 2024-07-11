#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

#include "chai.h"
#include "can/can.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow, public CAN_PROCESSING_OBJECT
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButtonOpen_clicked();
    void on_pushButtonClose_clicked();
    void on_pushButtonStart_clicked();
    void on_pushButtonStop_clicked();
    void on_pushButtonTestTransmit_clicked();
	void on_pushButtonRegEvent_clicked();
	void on_pushButtonGenID_clicked();
	void on_pushButtonVersionReqst_clicked();
	void on_Timer1();
	void on_pushButtonTest_clicked();
	void on_pushButtonDecVersions_clicked();

private:
    Ui::MainWindow *ui;

public:
	QTimer *Timer1;

	_u8 GetChanel();

	static int test_transmit_n;
	static int test_recieved_n;

	void RC_processing() override;
	// RC_processing - обработка одного кадра находящегося в msg

	void Err_processing(int err_code) override;
	void Success_processing(QString Success) override;

	bool filter(_u32);
};
#endif // MAINWINDOW_H
