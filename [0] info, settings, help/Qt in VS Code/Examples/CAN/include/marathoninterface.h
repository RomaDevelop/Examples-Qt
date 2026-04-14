#ifndef MARATHONINTERFACE_H
#define MARATHONINTERFACE_H

#include <memory>

#include "chai.h"
#include "icanchannel.h"
#include "icaninterface.h"

#include "MarathonInterface_global.h"

class MARATHONINTERFACE_EXPORT MarathonInterface : public ICANInterface
{
	int number = -1;
	QString name;
	_u32 versionLib = 0;
	_u32 versionDrvr = 0;

	///\brief Указатель на функцию записи лога
	ICANChannel::CBFunctionWriteLog_t CBFLog = nullptr;

	///\brief Перечень каналов
	std::vector<ICANChannel*> channels;

public:
	///\brief создание пустого интерфейса, инициализация в InitInterface
	MarathonInterface() = default;

	///\brief вызов ClearChannels();
	~MarathonInterface();

	///\brief Остановка всех каналов, освобождение выделенной памяти под каналы.
	void ClearChannels();

	///\brief инициализация интерфейса
	/// назначение свойств,
	/// инициализация библиотеки (однократно),
	/// вызов ClearChannels() (на случай если переинициализация)
	/// создание каналов, заполнение vector<ICANChannel*> channels
	virtual int InitInterface(int interfaceNumber, QString interfaceName, int absoluteChannelNumbersStartsFrom) override;
	virtual int GetNumber() const override;
	virtual QString GetName() const override;
	virtual int GetChannelsCount() const override;
	virtual std::vector<ICANChannel*> GetChannels() override;
	virtual std::vector<ICANChannel*> GetChannels(int status) override;
	virtual std::vector<ICANChannel*> GetChannels_if(bool(*condition)(ICANChannel*)) override;
	virtual void SetCBFunctionForLog(ICANChannel::CBFunctionWriteLog_t CBFLog_) override;
	virtual void SetCBFunctionForToAllChannels(ICANChannel::CBFunctionWriteLog_t CBFLog_) override;

	void WriteLog(const QString &log) const;

	_u32 GetVersionLib() {return versionLib;}
	_u32 GetVersionDrvr() {return versionDrvr;}
};

#endif // MARATHONINTERFACE_H
