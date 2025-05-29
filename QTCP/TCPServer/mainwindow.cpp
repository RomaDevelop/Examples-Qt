#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	int port = 25001;
	server = new QTcpServer(this);
	connect(server, &QTcpServer::newConnection, this, &MainWindow::SlotNewConnection);

	if(!server->listen(QHostAddress::Any,port))
	{
		QMessageBox::critical(this,"","error listen " + server->errorString());
		server->close();
	}
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::SlotNewConnection()
{
	QTcpSocket *sock = server->nextPendingConnection();
	connect(sock, &QTcpSocket::disconnected, sock, &QTcpSocket::deleteLater);
	connect(sock, &QTcpSocket::readyRead, this, &MainWindow::SlotReadClient);
	SendToClient(sock, "connected");
	ui->textEdit->append("new connection processed");
}

void MainWindow::SlotReadClient()
{
	// моё максимально упрощенное
	// для пересылки больших данных сначала отправляют их размер, а затем читают нужное количество данных
	// тут это не реализовано
	QTcpSocket *sock = (QTcpSocket*)sender();
	QString readed = sock->readAll();
	ui->textEdit->append(QString("received from client {") + readed + "}");
	SendToClient(sock, QString("get {") + readed + "}");

//	// пример из книжки Шлее - не заработал
//	QTcpSocket *sock = (QTcpSocket*)sender();
//	QDataStream in(sock);
//	in.setVersion(QDataStream::Qt_5_12);
//	for(;;)
//	{
//		if(!nextBlockSize)
//		{
//			if(sock->bytesAvailable() < sizeof(quint16)) break;
//		}
//		in >> nextBlockSize;

//		if(sock->bytesAvailable() < nextBlockSize) break;

//		QTime time;
//		QString str;
//		in >> time >> str;

//		QString strMsg = time.toString() + " Client has send - " + str;
//		ui->textEdit->append(strMsg);
//		nextBlockSize = 0;

//		SendToClient(sock, "server response: Recived " + str);
//	}
}

void MainWindow::SendToClient(QTcpSocket *sock, const QString &str)
{
	// моё максимально упрощенное
	sock->write(str.toStdString().data());

//	// пример из книжки Шлее - не заработал
//	QByteArray arrBlock;
//	QDataStream out(&arrBlock, QIODevice::WriteOnly);
//	out.setVersion(QDataStream::Qt_5_12);
//	out << quint16(0) << str;

//	out.device()->seek(0);
//	out << quint16(arrBlock.size() - sizeof(quint16));

//	/*
//	 * Для пересылки обычных строк можно было использовать класс потока ввода QTextStream,
//	 * QDataStream использован потому что пересылка бинарных данных более общий случай.
//	*/

//	sock->write(arrBlock);
}






