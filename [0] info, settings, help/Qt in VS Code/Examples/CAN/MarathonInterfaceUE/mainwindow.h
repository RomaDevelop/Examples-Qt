#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	Ui::MainWindow *ui;

	MainWindow(QWidget *parent = nullptr);
	~MainWindow();

private slots:
	void on_pushButtonStart_clicked();
	void on_pushButtonStop_clicked();
	void on_pushButtonTransmit_clicked();
	void on_pushButtonReceive_clicked();
	void on_pushButtonRegCBMsg_clicked();

	void on_pushButtonDisReg_clicked();

	void on_pushButtonRegWrTraffic_clicked();

	void on_pushButtonDisRegWrTraffic_clicked();

	void WorkMessage(const QString &str);
	void WorkError();

	void on_btnRegCBErr_clicked();

	void on_btnDisRegCBErr_clicked();

signals:
	void Message(const QString &str);
	void Error();
};
#endif // MAINWINDOW_H
