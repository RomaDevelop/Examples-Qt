#ifndef SERVERINTERFACE_H
#define SERVERINTERFACE_H

#include "icanchannel.h"
#include "icaninterface.h"

#include "ServerInterface_global.h"

class SERVERINTERFACE_EXPORT ServerInterface : public ICANInterface
{
	int number;
	QString name;

	///\brief Указатель на функцию записи лога
	ICANChannel::CBFunctionWriteLog_t CBFLog;

	///\brief Перечень каналов
	std::vector<ICANChannel*> channels;

public:
	///\brief задаются начальные значения свойствам
	ServerInterface(int interfaceNumber);
	///\brief вызов ClearChannels();
	~ServerInterface();

	///\brief Остановка всех каналов, освобождение выделенной памяти под каналы.
	void ClearChannels();

	///\brief создание каналов с IP по умолчанию и заполнение vector<ICANChannel*> channels
	int ScanInterface() override;
	void SetIP(std::vector<std::tuple<QString,int,int>> Vector_IP_portCmd_portData);
	int	GetNumber() const override;
	QString GetName() const override;
	int GetChannelsCount() const override;
	void GetChannels(std::vector<ICANChannel*> &channels) override;
	void GetChannels(std::vector<ICANChannel*> &channels, int status) override;
	void GetChannels_if(std::vector<ICANChannel*> &channels, bool(*condition)(ICANChannel*)) override;
	void SetCBFunctionForLog(ICANChannel::CBFunctionWriteLog_t CBFLog_) override;
	void SetCBFunctionForToAllChannels(ICANChannel::CBFunctionWriteLog_t CBFLog_) override;

	void WriteLog(const QString &log) const;
};

#endif // SERVERINTERFACE_H
