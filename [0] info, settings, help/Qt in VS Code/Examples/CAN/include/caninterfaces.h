//==================================================================================================
/*
 * Добавление в проект:
 * INCLUDEPATH += ../include  # добавление пути к cansettingdialogdynamic.h
 * DEPENDPATH += ../include   # добавление пути к cansettingdialogdynamic.h
 * win32:CONFIG(release, debug|release): LIBS += -L../bin/ -lCANInterfaces      # добавление dll
 * else:win32:CONFIG(debug, debug|release): LIBS += -L../bin/ -lCANInterfacesd  # добавление dll с возможностью отладки
 *
 * Примение в проекте:
 * #include "caninterfaces.h"		// в файле, где будут объявлены интерфейсы
 * CANInterfaces *interfaces;		// глобально, или в классе ообъекта, который будет работать с CANInterfaces
 * interfaces = new CANInterfaces;	// выделение памяти под интерфейсы, автоматическое чтение данных о каналах
 * delete interfaces;				// освобождение памяти когда работа завершена
*/
//==================================================================================================
#ifndef CANINTERFACES_H
#define CANINTERFACES_H

#include <memory>
#include <vector>

#include "icaninterface.h"

#include "CANInterfaces_global.h"

class CANINTERFACES_EXPORT CANInterfaces
{
	ICANChannel::CBFunctionWriteLog_t CBFLog = nullptr;

		///\brief Перечень интерфейсов
	std::vector<ICANInterface*> interfaces;
		///\brief конструктор private для создания объяекта использовать Create()
	CANInterfaces() = default;
public:
		///\brief возвращаемое значение для функции Create
	struct CreateResult
	{
		std::string errors;
		std::unique_ptr<CANInterfaces> canInterfaces;
	};

		///\brief создание объекта CANInterfaces
		/// errors содержит описание ошибок если были
		/// canInterfaces объект CANInterfaces (пустой указатель не возвращает ни при каких обстоятельствах)
	static CreateResult Create();

		///\brief Вызов ClearInterfaces()
	~CANInterfaces();

		///\brief Освобождение памяти выделенной под vector<ICANInterface*> interfaces
	void ClearInterfaces();

		///\brief Кол-во интерфейсов
	int GetInterfacesCount();

		///\brief Возвращает вектор всех интерфейсов
	std::vector<ICANInterface*> GetInterfaces();

		///\brief Возвращает вектор интерфейсов, удовлетворяющих условию condition
		/// пример condition: [](ICANInterface *ch){ return ch->GetName().contains("CAN"); }
	std::vector<ICANInterface*> GetInterfaces_if(bool(*condition)(ICANInterface*));

		///\brief Кол-во всех каналов на всех интерфейсах
	int GetChannelsCount();

		///\brief Возвращает канал по номеру
	ICANChannel* GetChannel(int numberAbsolut);

		///\brief Возвращает вектор каналов со всех интерфейсов
	std::vector<ICANChannel*> GetChannels();

		///\brief Возвращает вектор каналов с указанным статусом (определяется перечислением CANChannel::STATUS_CODE)
	std::vector<ICANChannel*> GetChannels(int status);

		///\brief Возвращает вектор каналов удовлетворяющих условию condition
		/// пример condition: [](ICANChannel *ch){ return ch->GetName().contains("USB"); }
	std::vector<ICANChannel*> GetChannels_if(bool(*condition)(ICANChannel*));

		///\brief Регистрирует функцию записи лога для себя
		///\return результат выполнения функции
		///\param [in] указатель на функцию  записи лога
	void SetCBFunctionForLog(ICANChannel::CBFunctionWriteLog_t CBFLog_);
		///\brief Регистрирует функцию записи лога для всех интерфейсов
	void SetCBFunctionForLogToAllInterfaces(ICANChannel::CBFunctionWriteLog_t CBFLog_);
		///\brief Регистрирует функцию записи лога для себя, всех интерфейсов и всех каналов
	void SetCBFunctionForLogToSelfAndInterfacesAndChannels(ICANChannel::CBFunctionWriteLog_t CBFLog_);

		///\brief вызывает функцию записи лога если она зарегистрирована
	void WriteLog(const QString &log) const;
};

#endif // CANINTERFACES_H
