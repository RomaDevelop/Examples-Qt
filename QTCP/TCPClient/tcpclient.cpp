#include "tcpclient.h"
#include "ui_tcpclient.h"

int port = 25001;

TCPClient::TCPClient(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::TCPClient)
{
	ui->setupUi(this);

	socket = new QTcpSocket(this);
	nextBlockSize = 0;
	socket->connectToHost("127.0.0.1", port);
	connect(socket,SIGNAL(connected()),SLOT(SlotConnected()));
	connect(socket,SIGNAL(readyRead()),SLOT(SlotReadyRead()));
	connect(socket,SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(SlotError(QAbstractSocket::SocketError)));
	connect(ui->pushButton,SIGNAL(clicked()), this, SLOT(SlotSend()));
	connect(ui->lineEdit,SIGNAL(returnPressed()), this, SLOT(SlotSend()));
}

TCPClient::~TCPClient()
{
	delete ui;
}

void TCPClient::SlotReadyRead()
{
	QTcpSocket *sock = (QTcpSocket*)sender();
	int aviable = sock->bytesAvailable();
	char *buf = new char[aviable + 1];
	sock->read(buf, aviable);
	buf[aviable] = '\0';
	ui->textEdit->append(QString("received from server {") + buf + "}");

//	// пример из книжки Шлее - не заработал
//	QDataStream in(socket);
//	in.setVersion(QDataStream::Qt_5_12);
//	for(;;)
//	{
//		ui->textEdit->append(QString::number(socket->bytesAvailable()));
//		if(!nextBlockSize)
//		{
//			if(socket->bytesAvailable() < sizeof(quint16)) break;
//		}

//		if(socket->bytesAvailable() < nextBlockSize) break;

//		QString str;
//		in >> str;

//		ui->textEdit->append(str);
//		nextBlockSize = 0;
//	}
}

void TCPClient::SlotError(QAbstractSocket::SocketError err)
{
	QString str ="";
	if(err == QAbstractSocket::HostNotFoundError) str += "Host not foud. ";
	if(err == QAbstractSocket::RemoteHostClosedError) str += "Remote host is closed. ";
	if(err == QAbstractSocket::ConnectionRefusedError) str += "Connection was refused. ";
	str += socket->errorString();
	ui->textEdit->append(str);
}

void TCPClient::SlotSend()
{
	// моё максимально упрощенное
	// для пересылки больших данных сначала отправляют их размер, а затем читают нужное количество данных
	// тут это не реализовано
	if(ui->lineEdit->text() == "") ui->lineEdit->setText("emty package");
	socket->write(ui->lineEdit->text().toStdString().data());
	ui->lineEdit->setText("");

//	// пример из книжки Шлее - не заработал
//	QByteArray arrBlock;
//	QDataStream out(&arrBlock, QIODevice::WriteOnly);
//	out.setVersion(QDataStream::Qt_5_12);
//	out << quint16(0) /*<< QTime::currentTime() */<< ui->lineEdit->text();

//	out.device()->seek(0);
//	out << quint16(arrBlock.size() - sizeof(quint16));
//	/*
//	 * Для пересылки обычных строк можно было использовать класс потока ввода QTextStream,
//	 * QDataStream использован потому что пересылка бинарных данных более общий случай.
//	*/

//	socket->write(arrBlock);
}


void TCPClient::SlotConnected()
{
	ui->textEdit->append("connected");
}

void TCPClient::on_pushButton_2_clicked()
{
	socket->connectToHost("127.0.0.1", port);
}
