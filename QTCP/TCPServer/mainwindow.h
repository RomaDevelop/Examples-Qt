#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include <QHostAddress>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
	Q_OBJECT

	QTcpServer *server;

public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();

private:
	Ui::MainWindow *ui;

	void SendToClient(QTcpSocket *sock, const QString &str);

	public slots:
	void SlotNewConnection();
	void SlotReadClient();
};
#endif // MAINWINDOW_H
