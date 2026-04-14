#ifndef SERVERCHANNEL_H
#define SERVERCHANNEL_H

#include <memory>
#include <queue>
#include <tuple>

#include <QObject>
#include <QTcpSocket>

#include "icanchannel.h"

typedef void (*ServerChannelCB)(int channel, int event, void* udata);

class ServerChannel : public QObject, public ICANChannel
{
	Q_OBJECT

	int numberOnInterface;
	int numberAbsolut;
	QString name;
	QString ipAdress;
	int portCmd;
	int portData;
	bool started_us;
	int regime;
	int baud;
	unsigned long appFilter;
	unsigned long appMask;
	unsigned long progFilter;
	unsigned long progMask;

public:
	std::shared_ptr<QTcpSocket> sock_cmd;
	std::shared_ptr<QTcpSocket> sock_data;

	CBFunction_t CBFError;
	CBFunction_t CBFMessage;
	CBFunctionWriteLog_t CBFLog;
	FunctionWriteTraffic_t FWriteTraffic;

	int lastError;

	std::queue<CANMsg_t> messages;

public:	
	ServerChannel(int numberOnInterface_, int numberAbsolut_, QString name_, QString ipAdress_,
				  int portCmd_, int portData_, QObject *parent = nullptr);
	~ServerChannel() override;

	///\brief установка IP адреса, порта команд и порта данных
	/// если канал запущен, то он будет перезапущен с новыми параметрами
	int SetIP(std::tuple<QString, int, int> Tuple_IP_portCmd_portData);
	std::tuple<QString, int, int> GetIP();

	QString GetName() const override;
	int	GetNumberOnInterface() const override;
	int	GetNumberAbsolut() const override;
	int GetRegime() const override;
	int GetBaud() const override;
	void GetAppFilter(unsigned long &filter, unsigned long &mask) const override;
	void GetProgFilter(unsigned long &filter, unsigned long &mask) const override;

	int GetStatus() const override;

	int SetRegime(unsigned int regime) override;
	int SetBaud(unsigned int baud) override;
	int SetAppFilter(unsigned long filter, unsigned long mask) override;
	int SetProgFilter(unsigned long filter, unsigned long mask) override;

	int Start() override;
	int Stop() override;

	int WriteMsg(CANMsg_t *Msg) override;

	int GetRecCnt() const override;
	int ReadMsg(CANMsg_t *Msg, unsigned int cnt = 1) override;

	int SetCBFunctionForError(CBFunction_t CBFunction) override;
	int SetCBFunctionForMessage(CBFunction_t CBFunction) override;
	int SetCBFunctionForLog(CBFunctionWriteLog_t CBFLog) override;
	int SetFunctionWriteTraffic(FunctionWriteTraffic_t FTraffic) override;

	void ThrowError(int channel_) const;
	void WriteLog(const QString &log) const;

	QString FormatHex(int value, int digits);
	QString ConvertCANMsgForServer(CANMsg_t &msg);
	void ConvertFromServerToCANMsg(QString msg_str, CANMsg_t &msg);

private slots:
	void SlotReadyRead();
	void SlotError(QAbstractSocket::SocketError);
	void SlotConnected();
	void SlotDisconnected();
};
#endif // SERVERCHANNEL_H
