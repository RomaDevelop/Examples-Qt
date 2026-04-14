#ifndef ICANINTERFACE_H
#define ICANINTERFACE_H

#include <vector>

#include "icanchannel.h"

class ICANInterface
{
public:
    virtual ~ICANInterface() = default;

    ///\brief Инициализация интерфейса
    ///\return результат выполнения функции (определяется перечислением ERROR_CODE)
    ///\param[in] interfaceNumber - номер интерфейса
    ///\param[in] interfaceName - имя интерфейса
    ///\param[in] absoluteChannelNumbersStartsFrom - номер с которого пойдет абсолютная нумерация каталов (см. описание в конце файла)
    virtual int InitInterface(int interfaceNumber, QString interfaceName, int absoluteChannelNumbersStartsFrom) = 0;

    ///\brief Номер интерфейса
    virtual int	GetNumber() const = 0;

    ///\brief Имя интерфейса
    virtual QString GetName() const = 0;

    ///\brief Количество каналов
    virtual int GetChannelsCount() const = 0;

    ///\brief Возвращает вектор каналов
    virtual std::vector<ICANChannel*> GetChannels() = 0;
    ///\brief Возвращает вектор каналов с указанным статусом status
    virtual std::vector<ICANChannel*> GetChannels(int status) = 0;
    ///\brief Возвращает вектор каналов, удовлетворяющих условию condition
    /// пример лямбда condition: [](ICANChannel *ch){ return ch->GetName().contains("USB"); }
    virtual std::vector<ICANChannel*> GetChannels_if(bool(*condition)(ICANChannel*)) = 0;

    ///\brief Регистрирует функцию записи лога
    virtual void SetCBFunctionForLog(ICANChannel::CBFunctionWriteLog_t CBFLog) = 0;
    ///\brief Регистрирует функцию записи лога для всех каналов
    virtual void SetCBFunctionForToAllChannels(ICANChannel::CBFunctionWriteLog_t CBFLog) = 0;

    enum ERROR_CODE
    {
        NO_ERRORS = 0,			///< Ошибка отсутствует
        INIT_ERROR = 1			///< Ошибка инициализации библиотеки
    };
};

#endif // ICANINTERFACE_H

/*
InitInterface(int absoluteChannelNumbersStartsFrom)
Владельцам ICANInterface-ов необходимо назначать начальный абсолютный номер каналов для интерфейсов самостоятельно,
поскольку создание здесь счетчика невозможно, ввиду того что этот .h файл используется в разных dll,
в каждой единице компилляции счетчик будет по факту свой.
 */
