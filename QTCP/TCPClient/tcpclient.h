#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QTime>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class TCPClient; }
QT_END_NAMESPACE

class TCPClient : public QMainWindow
{
	Q_OBJECT	
	Ui::TCPClient *ui;
	QTcpSocket *socket;
	quint16 nextBlockSize;

public:
	TCPClient(QWidget *parent = nullptr);
	~TCPClient();

private slots:
	void SlotReadyRead();
	void SlotError(QAbstractSocket::SocketError err);
	void SlotSend();
	void SlotConnected();

	void on_pushButton_2_clicked();
};
#endif // TCPCLIENT_H
