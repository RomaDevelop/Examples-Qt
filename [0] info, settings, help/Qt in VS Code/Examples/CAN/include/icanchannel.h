#ifndef ICANCHANNEL_H
#define ICANCHANNEL_H

#include <bitset>
#include <array>
#include <set>

#include <QString>
#include <QDebug>

struct ICANChannelTests {
	inline static bool AllTests();
};

typedef unsigned char u8;
typedef unsigned long u32;

///\brief Предварительное объявление фильтров
class CANMsgIDFilter_t;
class CANMsgDataFilter_t;

///\brief Структура CAN-сообщения
struct CANMsg_t
{
	inline static const int dataFieldsCount = 8;
	inline static const int dataOneFieldBitsSize = 8;

	u32	ID {0};								///< Идентификатор
	std::array<u8,8> data {};	///< Поля данных
	u8	length {0};							///< Фактическая длина поля данных
	u32	regime {0};							///< Формат сообщения (bit 0 - RTR, bit 2 – EFF) (пример: 0b100 - EFF кадр)
	u32	timeStamp {0};						///< Отметка времени получения

	CANMsg_t() = default;
	CANMsg_t(u32 aID, const std::array<u8,8> &aData, u8 aLength, u32 aRegime, u32 aTimeStamp):
		ID{aID}, data{aData}, length{aLength}, regime{aRegime}, timeStamp{aTimeStamp} {  }

	/// пример вызова: Set(0x1010101, {8,7,6,5,4,3,2,1}, 8, 0b100, 0);
	inline void Set(u32 aID, const std::array<u8,8> &aData, u8 aLength, u32 aRegime, u32 aTimeStamp);
	inline void CopyCanMsg(CANMsg_t *dstMsg) const;
	inline QString ToStr(int base = 16) const;
	inline QString ToStrExt(int base = 16) const;
	inline CANMsg_t& FromStrExt(const QString &str, int base = 16);

	inline bool IsRTR() const;
	inline bool IsEFF() const;

	inline bool CheckFilter(const CANMsgIDFilter_t & filter) const;
	inline bool CheckFilter(const CANMsgDataFilter_t & filter) const;

	/// сравнивает все поля структуры, кроме timeStamp
	inline bool operator== (const CANMsg_t &msgToCmp) const;
	inline bool operator!= (const CANMsg_t &msgToCmp) const;

	inline static const int idVariableBitSize = 32;
	inline static const u8 fullMask_8bit = 0xFF;
	inline static const u32 fullMask_29bit = 0x1FFFFFFF;
	inline static const u32 fullMask_32bit = 0xFFFFFFFF;

	inline static bool TestToAndFromStrExt();
};

enum class CompareFilterRes { lower, intersects, greater };
inline const char* CompareFilterResToString(CompareFilterRes val);

///\brief Фильтр ID для CAN-сообщения
class CANMsgIDFilter_t
{
	u32 filter {0};
	u32 mask {0};
	std::bitset<CANMsg_t::idVariableBitSize> filterBitset {};
	std::bitset<CANMsg_t::idVariableBitSize> maskBitset {};

public:
	CANMsgIDFilter_t() = default;
	inline CANMsgIDFilter_t(u32 aFilter, u32 aMask) { Set(aFilter, aMask); }

	inline void Set(u32 aFilter, u32 aMask);
	inline u32 Filter() const { return filter; }
	inline u32 Mask() const { return mask; }

	inline const std::bitset<32>& FilterBitset() const { return filterBitset; }
	inline const std::bitset<32>& MaskBitset() const { return maskBitset; }

	inline bool HasMask() const { return mask; }

	inline QString ToStr(int base = 16) const;

	inline bool CheckMsg(const CANMsg_t &msg) const;

	inline static CompareFilterRes Compare(const CANMsgIDFilter_t &lhs, const CANMsgIDFilter_t &rhs);

	inline static bool TestCompare();
	inline static bool Test_set_non_intersecting_id_filters();

	friend struct static_assertation;
};

struct CANIdFilterComparator {
	bool operator()(const CANMsgIDFilter_t &lhs, const CANMsgIDFilter_t &rhs) const {
		return CANMsgIDFilter_t::Compare(lhs, rhs) == CompareFilterRes::lower;
	}
};

using set_non_intersecting_id_filters = std::set<CANMsgIDFilter_t, CANIdFilterComparator>;

///\brief Фильтр данных для CAN-сообщения
class CANMsgDataFilter_t
{
	std::array<std::bitset<8>, 8> filterBitset {};
	std::array<std::bitset<8>, 8> maskBitset {};

public:
	CANMsgDataFilter_t() = default;
	inline CANMsgDataFilter_t(const std::array<u8,8> &aFilter, const std::array<u8,8> &aMask) { Set(aFilter, aMask); }
	inline CANMsgDataFilter_t(const std::array<std::bitset<8>,8> &aFilter, const std::array<std::bitset<8>,8> &aMask) { Set(aFilter, aMask); }

	inline const std::array<std::bitset<8>, 8>& Filter() const { return filterBitset; }
	inline const std::array<std::bitset<8>, 8>& Mask() const { return maskBitset; }
	inline bool HasMask() const;

	inline void Set(const std::array<u8,8> &aFilter, const std::array<u8,8> &aMask);
	inline void Set(const std::array<std::bitset<8>,8> &aFilter, const std::array<std::bitset<8>,8> &aMask);

	inline void SetFilter(const std::array<u8,8> &aFilter);
	inline void SetMask(const std::array<u8,8> &aMask);

	inline void SetFilter(const std::array<std::bitset<8>,8> &aFilter) { filterBitset = aFilter; }
	inline void SetMask(const std::array<std::bitset<8>,8> &aMask) { maskBitset = aMask; }

	inline void SetFilter(u8 byte, u8 value) { filterBitset[byte] = value; }
	inline void SetMask(u8 byte, u8 value) { maskBitset[byte] = value; }

	inline void SetFilter(u8 byte, u8 bit, bool value) { filterBitset[byte][bit] = value; }
	inline void SetMask(u8 byte, u8 bit, bool value) { maskBitset[byte][bit] = value; }

	///\brief Объединение текущего фильтра с фильтром aFilter
	/// в местах пересечения масок останется текущее значение
	///\return возвращает false если маски пересекаются
	inline bool UniteFilters(const CANMsgDataFilter_t &aFilter);

	inline bool FromStr(QString aFilter, int filterBase = 16, QString aMask = "1");
	inline QString FilterToStr(int base = 16) const;
	inline QString MaskToStr(int base = 16) const;
	inline QString ToStr(int base = 16) const;

	inline bool CheckMsg(const CANMsg_t &msg) const;

	inline static CompareFilterRes Compare(const CANMsgDataFilter_t &lhs, const CANMsgDataFilter_t &rhs);

	inline static bool TestCompare();

	friend struct static_assertation;
};

struct CANDataFilterComparator {
	bool operator()(const CANMsgDataFilter_t &lhs, const CANMsgDataFilter_t &rhs) const {
		return CANMsgDataFilter_t::Compare(lhs, rhs) == CompareFilterRes::lower;
	}
};

using set_non_intersecting_data_filters = std::set<CANMsgDataFilter_t, CANDataFilterComparator>;

class ICANChannel
{
public:
	virtual ~ICANChannel() = default;

	///\brief Получение номера канала в нумерации производителя
	virtual int GetNumberOnInterface() const = 0;

	///\brief Получение абсолютного номера канала
	virtual int GetNumberAbsolut() const = 0;

	///\brief Получение имени канала
	virtual QString GetName() const = 0;

	///\brief Текущий статус канала (определяется перечислением STATUS_CODE)
	virtual int GetStatus() const = 0;

	///\brief Установка режима передачи и выставление в тот же статус, что был до
	///\return результат выполнения функции (определяется перечислением ERROR_CODE)
	///\param[in] regime значение режима передачи (определяется перечислением REGIME_CODE)
	virtual int SetRegime(uint regime_) = 0;

	///\brief Текущая скорость (определяется перечислением REGIME_CODE)
	virtual int GetRegime() const = 0;

	///\brief Установка скорости передачи и выставление в тот же статус, что был до
	///\return результат выполнения функции (определяется перечислением ERROR_CODE)
	///\param[in] baud скорость передачи (определяется перечислением BAUD_CODE)
	virtual int SetBaud(uint baud_) = 0;

	///\brief Текущая скорость (определяется перечислением BAUD_CODE)
	virtual int GetBaud() const = 0;

	///\brief Установка аппаратного фильтра и выставление в тот же статус, что был до
	/// в Marathon фильрация осущетсвляется внутри Marathon
	/// в CANServer фильтрация осуществляется последовательно: appFilter, затем progFilter
	///\return результат выполнения функции (определяется перечислением ERROR_CODE)
	///\param[in] filter значение фильтра
	///\param[in] mask значение маски
	virtual int SetAppFilter(ulong filter, ulong mask) = 0;

	///\brief Текущий аппаратный фильтр
	///\param[out] filter значение фильтра
	///\param[out] mask значение маски
	virtual void GetAppFilter(ulong &filter, ulong &mask) const = 0;

	///\brief Установка программного фильтра и выставление в тот же статус, что был до
	/// в Marathon отсутсвует возможность фильтровать при помощи ProgFilter
	/// в CANServer фильтрация осуществляется последовательно: appFilter, затем progFilter
	///\return результат выполнения функции (определяется перечислением ERROR_CODE)
	///\param[in] filter значение фильтра
	///\param[in] mask значение маски
	virtual int SetProgFilter(ulong filter, ulong mask) = 0;

	///\brief Текущий программный фильтр
	///\param[out] filter значение фильтра
	///\param[out] mask значение маски
	virtual void GetProgFilter(ulong &filter, ulong &mask) const = 0;

	///\brief Открытие канала для приема-передачи
	/// если канал открыт, он не переоткрывается, возвращает ошибку
	///\return результат выполнения функции (определяется перечислением ERROR_CODE)
	virtual int Start() = 0;

	///\brief Закрытие канала для приема-передачи
	///\return результат выполнения функции (определяется перечислением ERROR_CODE)
	/// при остановке канала обнуюляются его cb-функции!
	virtual int Stop() = 0;

	///\brief Установка режима передачи, скорости и статуса канала в указанные состояния
	///\return результат выполнения функции (определяется перечислением ERROR_CODE)
	///\param[in] regime значение режима передачи (определяется перечислением REGIME_CODE)
	///\param[in] baud значение режима передачи (определяется перечислением BAUD_CODE)
	///\param[in] status значение режима передачи (определяется перечислением STATUS_CODE)
	virtual int Set(int regime, int baud, int status) = 0;

	///\brief Отправка кадра в сеть
	///\return результат выполнения функции (определяется перечислением ERROR_CODE)
	///\param[out] *Msg указатель на отправляемый кадр
	virtual int WriteMsg(const CANMsg_t *Msg) = 0;

	///\brief Запрос количества принятых кадров в очереди
	///\return .first - результат выполнения функции (определяется перечислением ERROR_CODE)
	///\return .second - количество сообщений в очереди принятых сообщений
	virtual std::pair<int,int> GetMsgCnt() const = 0;

	///\brief Чтение сообщений из очереди принятых
	///\return .first - результат выполнения функции (определяется перечислением ERROR_CODE)
	///\return .second - количество считанных кадров
	///\param[out] *Msg указатель на буфер для приема кадров
	///\param[in] cnt количество считываемых сообщений
	virtual std::pair<int,int> ReadMsg(CANMsg_t *Msg, unsigned int cnt = 1) = 0;

	///\brief определение типов указателей на функции для обработчиков событий
	typedef void (*CBFunction_t)(int channelNumberAbsolut);
	typedef void (*CBFunction2_t)(void *handler);
	//typedef void (*CB_Read_Msg_t)(CANMsg_t*);

	///\brief Регистрирует функцию обратного вызова при возникновении ошибки
	///\return результат выполнения функции (определяется перечислением ERROR_CODE)
	///\param [in] CBFext указатель на функцию обратного вызова
	///\param [out] udata буфер для сообщения
	virtual int SetCBFunctionForError(CBFunction_t CBFunction) = 0;

	///\brief Регистрирует функцию обратного вызова при получении сообщения
	///\return результат выполнения функции (определяется перечислением ERROR_CODE)
	///\param [in] CBFunction указатель на функцию обратного вызова
	virtual int SetCBFunctionForMessage(CBFunction_t CBFunction) = 0;

	///\brief Регистрирует функцию обратного вызова при получении сообщения
	///\return результат выполнения функции (определяется перечислением ERROR_CODE)
	///\param [in] CBFunction указатель на функцию обратного вызова
	///\param [in] handler указатель будет передан в функцию при срабатывании
	virtual int SetCBFunctionForMessage2(CBFunction2_t CBFunction, void *handler) = 0;

	///\brief определение типа указателя на функцию обработки лога
	/// Внимание! Существование log гарантируется только во время выполенения обработчика лога
	/// В случае назначения одного обработчика на несколько каналов (и др.) требуется синхронизация
	typedef void (*CBFunctionWriteLog_t)(const QString &log);

	///\brief Регистрирует функцию записи лога
	///\return результат выполнения функции (определяется перечислением ERROR_CODE)
	///\param [in] указатель на функцию записи лога
	virtual int SetCBFunctionForLog(CBFunctionWriteLog_t CBFLog) = 0;

	///\brief определение типа указателя на функцию записи траффика
	/// Внимание! Существование msg гарантируется только во время выполенения функции записи
	/// В случае назначения одного обработчика на несколько каналов (и др.) требуется синхронизация
	///\param [in] msg ссылка на считанное или отправляемое сообщение
	///\param [in] read - флаг получено или отправлено сообщение. (1 - read, 0 - write)
	typedef void (*FunctionWriteTraffic_t)(int chNumberAbsolut, bool read, const CANMsg_t &msg);

	///\brief Регистрирует функцию записи траффика
	/// FunctionWriteTraffic_t вызывается при выполнении WriteMsg и ReadMsg если зарегистрирована
	///\return результат выполнения функции (определяется перечислением ERROR_CODE)
	///\param [in] указатель на функцию
	virtual int SetFunctionWriteTraffic(FunctionWriteTraffic_t FTraffic) = 0;

	///\brief Набор возможных статусов канала
	enum STATUS_CODE
	{
		STATUS_ERROR = 404,	///< Ошибка определения статуса
		UNAVIABLE = 1,		///< Недоступен для нас
		AVIABLE = 2,		///< Доступен, но не запущен, можно запустить
		STARTED = 3		///< Запущен
	};
	inline static QString StatusToStr(int code);
	inline static int StatusStrToInt(QString statusStr);

	///\brief Набор возможных ошибок
	enum ERROR_CODE
	{
		NO_ERRORS = 0,		///< Ошибка отсутствует
		NO_SPECIFIED = -1,	///< Тип ошибки не определен
		BUSY = -2,		///< Устройство занято
		MEMORY_ERROR = -3,	///< Ошибка памяти
		STATE_ERROR = -4,	///< Действие не может быть выполнено в данном состоянии устройства
		CALL_ERROR = -5,	///< Ошибка вызова объекта
		INVALID_PARAMETR = -6,	///< Неверное значение параметра
		ACCESS_ERROR = -7,	///< Ошибка доступа к ресурсу
		NO_RESOURCES = -8,	///< Отсутствует запрашиваемый ресурс
		NOT_IMPLEMENT = -9,	///< Ошибка выполнения функции
		IO_ERROR = -10,		///< Ошибка ввода-вывода
		NO_DEVICE = -11,	///< Устройство не обнаружено
		INTERRUPT = -12,	///< Отмена по прерыванию от события
		RESOURCE_ERROR = -13,	///< Нет ресурсов
		TYMEOUT = -14,		///< Прервано по таймауту
		MOCK_ERROR = -15	///< Вызов нереализованной функции
	};
	inline static QString ErrorCodeToStr(int errorCode);

	///\brief Набор кодов возможных скоростей приема-передачи
	enum BAUD_CODE
	{
		BR_ERROR = 404,	///< Ошибка определения скорости
		BR_125K = 125,	///< 125 кБ/с
		BR_250K = 250,	///< 250 кБ/с
		BR_500K = 500,	///< 500 кБ/с
		BR_1M = 1000	///< 1 МБ/с
	};
	inline static QString BaudToStr(int code);
	inline static int BaudStrToInt(QString baudStr);

	///\brief Режим работы канала
	enum REGIME_CODE
	{
		REG_ERROR = 404,    ///< Ошибка определения режима
		REG_CAN11 = 0x2,    ///<Стандартный режим (идентификатор 11 бит)
		REG_CAN29 = 0x4,    ///<Расширенный режим (идентификатор 29 бит)
		REG_CAN11_29 = 0x6  ///<Работа в любом из режимов (идентификатор 11 или 29 бит)
	};
	inline static QString RegimeToStr(int code);
	inline static int RegimeStrToInt(QString regimeStr);

	inline static QString CrChannelName(int numberAbs, int numberOnInt, QString interface);
};

struct static_assertation {
	inline static CANMsgIDFilter_t ifFilter;
	inline static CANMsgDataFilter_t dataFilter;

	static_assert (sizeof(u8)*8 == CANMsg_t::dataFieldsCount, "wrong size u8");
	static_assert (sizeof(u32)*8 == CANMsg_t::idVariableBitSize, "wrong size u32");

	static_assert (std::is_same<decltype(CANMsg_t::ID), u32>::value, "wrong type CANMsg_t::ID");
	static_assert (std::is_same<decltype(CANMsg_t::data)::value_type, u8>::value, "wrong type CANMsg_t::data");
	static_assert (sizeof(CANMsg_t::data) / sizeof(u8) == CANMsg_t::dataFieldsCount, "wrong size CANMsg_t::data");

	static_assert (std::is_same<decltype(CANMsgIDFilter_t::filter), u32>::value, "wrong type CANMsgIDFilter_t::filter");
	static_assert (std::is_same<decltype(CANMsgIDFilter_t::mask), u32>::value, "wrong type CANMsgIDFilter_t::mask");
	static_assert (ifFilter.filterBitset.size() == CANMsg_t::idVariableBitSize, "wrong size CANMsgIDFilter_t::filterBitset");
	static_assert (ifFilter.maskBitset.size() == CANMsg_t::idVariableBitSize, "wrong size CANMsgIDFilter_t::maskBitset");

	static_assert (dataFilter.filterBitset.size() == CANMsg_t::dataFieldsCount, "wrong size CANMsgDataFilter_t::filterBitset");
	static_assert (dataFilter.maskBitset.size() == CANMsg_t::dataFieldsCount, "wrong size CANMsgDataFilter_t::maskBitset");
	static_assert (dataFilter.filterBitset[0].size() == CANMsg_t::dataOneFieldBitsSize, "wrong el size CANMsgDataFilter_t::filterBitset");
	static_assert (dataFilter.maskBitset[0].size() == CANMsg_t::dataOneFieldBitsSize, "wrong type CANMsgDataFilter_t::maskBitset");
};

const char* CompareFilterResToString(CompareFilterRes val)
{
	if(val == CompareFilterRes::lower) return "lower";
	if(val == CompareFilterRes::intersects) return "intersects";
	if(val == CompareFilterRes::greater) return "greater";
	return "wrong_CompareRes";
}

void CANMsgIDFilter_t::Set(u32 aFilter, u32 aMask)
{
	filter = aFilter;
	mask = aMask;
	filterBitset = aFilter;
	maskBitset = aMask;
}

QString CANMsgIDFilter_t::ToStr(int base) const
{
	return "{ F:" + QString::number(filter, base) + " | M:" + QString::number(mask, base) + " }";
}

bool CANMsgIDFilter_t::CheckMsg(const CANMsg_t & msg) const
{
	if(!mask) return true;

	std::bitset<32> id {msg.ID};

	for(int i=0; i<32; i++)
	{
		if(maskBitset[i]) // если бит в маске равен 1
		{
			if(id[i] != filterBitset[i]) { return false; }  // если бит в ID не равен биту в фильтре
		}
	}
	return true;
}

CompareFilterRes CANMsgIDFilter_t::Compare(const CANMsgIDFilter_t &lhs, const CANMsgIDFilter_t &rhs)
{
	if(lhs.Mask() == CANMsg_t::fullMask_32bit and rhs.Mask() == CANMsg_t::fullMask_32bit)
	{
		if(lhs.Filter() == rhs.Filter()) return CompareFilterRes::intersects;
		else return lhs.Filter() < rhs.Filter() ? CompareFilterRes::lower : CompareFilterRes::greater;
	}

	for (int i = 0; i < CANMsg_t::idVariableBitSize; i++)
	{
		bool lhsMaskBit = (lhs.Mask() & (1 << i));
		bool rhsMaskBit = (rhs.Mask() & (1 << i));
		bool lhsFilterBit = (lhs.Filter() & (1 << i));
		bool rhsFilterBit = (rhs.Filter() & (1 << i));

		// если бит маски 0
		if (lhsMaskBit == 0 or rhsMaskBit == 0)
		{
			continue; // пропускаем
		}
		else
		{
			if(lhsFilterBit != rhsFilterBit) // если есть различие в фильтре
				return lhsFilterBit < rhsFilterBit ? CompareFilterRes::lower : CompareFilterRes::greater; // сравниваем биты фильтра
		}
	}
	return CompareFilterRes::intersects; // фильтры пересекаются
}

bool CANMsgIDFilter_t::TestCompare()
{
	bool correct = true;

	struct TestCase {
		CANMsgIDFilter_t lhs;
		CANMsgIDFilter_t rhs;
		CompareFilterRes result;
	};
	std::vector<TestCase> cases{
		// пустые маски
		{	CANMsgIDFilter_t(0b0000, 0b0000),
			CANMsgIDFilter_t(0b0000, 0b0000),
			CompareFilterRes::intersects},
		{	CANMsgIDFilter_t(0b1111, 0b0000),
			CANMsgIDFilter_t(0b1111, 0b0000),
			CompareFilterRes::intersects},
		{	CANMsgIDFilter_t(0b1111, 0b0000),
			CANMsgIDFilter_t(0b1001, 0b0000),
			CompareFilterRes::intersects},
		{	CANMsgIDFilter_t(0b1001, 0b0000),
			CANMsgIDFilter_t(0b1111, 0b0000),
			CompareFilterRes::intersects},

		// полные маски
		{	CANMsgIDFilter_t(0b0000, 0xFFFFFFFF),
			CANMsgIDFilter_t(0b0000, 0xFFFFFFFF),
			CompareFilterRes::intersects},
		{	CANMsgIDFilter_t(0b1111, 0xFFFFFFFF),
			CANMsgIDFilter_t(0b1001, 0xFFFFFFFF),
			CompareFilterRes::greater},
		{	CANMsgIDFilter_t(0b1001, 0xFFFFFFFF),
			CANMsgIDFilter_t(0b1111, 0xFFFFFFFF),
			CompareFilterRes::lower},
		{	CANMsgIDFilter_t(0b1011, 0xFFFFFFFF),
			CANMsgIDFilter_t(0b1111, 0xFFFFFFFF),
			CompareFilterRes::lower},

		// частичные маски
		{	CANMsgIDFilter_t(0b0000, 0b1011),
			CANMsgIDFilter_t(0b0000, 0b1111),
			CompareFilterRes::intersects},
		{	CANMsgIDFilter_t(0b0000, 0b1011),
			CANMsgIDFilter_t(0b0000, 0b1101),
			CompareFilterRes::intersects},
		{	CANMsgIDFilter_t(0b1111, 0b1011),
			CANMsgIDFilter_t(0b1011, 0b1011),
			CompareFilterRes::intersects},
		{	CANMsgIDFilter_t(0b0011, 0b1011),
			CANMsgIDFilter_t(0b1111, 0b1011),
			CompareFilterRes::lower},

		{	CANMsgIDFilter_t(0b1111, 0b1011),
			CANMsgIDFilter_t(0b1101, 0b1011),
			CompareFilterRes::greater},
		{	CANMsgIDFilter_t(0b1111, 0b1011),
			CANMsgIDFilter_t(0b1011, 0b1011),
			CompareFilterRes::intersects},
		{	CANMsgIDFilter_t(0b1111, 0b1011),
			CANMsgIDFilter_t(0b1110, 0b1011),
			CompareFilterRes::greater},

		{	CANMsgIDFilter_t(0b1101, 0b1011),
			CANMsgIDFilter_t(0b1011, 0b1101),
			CompareFilterRes::intersects},
		{	CANMsgIDFilter_t(0b1100, 0b1011),
			CANMsgIDFilter_t(0b1011, 0b1101),
			CompareFilterRes::lower},
		{	CANMsgIDFilter_t(0b1101, 0b1011),
			CANMsgIDFilter_t(0b0011, 0b1101),
			CompareFilterRes::greater},

		{	CANMsgIDFilter_t(0b1101, 0b1011), // тест на порядок оценки битов - от младших к старшим или от старших к младшим
			CANMsgIDFilter_t(0b0010, 0b1101), // поскольку результат - greater порядок оценки от младших
			CompareFilterRes::greater},
	};

	for(auto &testCase:cases)
	{
		auto res = Compare(testCase.lhs, testCase.rhs);
		if(res != testCase.result)
		{
			correct = false;
			qDebug() << "TestCANMsgIDFilter_cmp error:";
			qDebug() << "Compare("+testCase.lhs.ToStr(2)+", "+testCase.rhs.ToStr(2)+") result is "+CompareFilterResToString(res)+
					", but expected "+CompareFilterResToString(testCase.result);
		}
	}

	return correct;
}

bool CANMsgIDFilter_t::Test_set_non_intersecting_id_filters()
{
	bool correct = true;

	bool inserted = true;
	bool not_inserted = false;

	struct TestCase{
		CANMsgIDFilter_t filter;
		bool result;
		bool clearSet = false;
	};
	TestCase clearSetCommand {{},{}, true};

	std::vector<TestCase> cases{
		// полная маска
		{ CANMsgIDFilter_t(0b0000, 0xFFFFFFFF), inserted },
		{ CANMsgIDFilter_t(0b0000, 0xFFFFFFFF), not_inserted },
		{ CANMsgIDFilter_t(0b0101, 0xFFFFFFFF), inserted },
		{ CANMsgIDFilter_t(0b0101, 0xFFFFFFFF), not_inserted },
		{ CANMsgIDFilter_t(0b0111, 0xFFFFFFFF), inserted },
		{ CANMsgIDFilter_t(0b0111, 0xFFFFFFFF), not_inserted },

		// пустая маска
		{ CANMsgIDFilter_t(0b0111, 0b0000), not_inserted }, // пустая маска в непустой сет
		{ clearSetCommand },
		{ CANMsgIDFilter_t(0b0111, 0b0000), inserted },		// пустая маска в пустой сет
		{ CANMsgIDFilter_t(0b1010, 0b0000), not_inserted }, // пустая маска в сет с одной пустой маской
		{ CANMsgIDFilter_t(0b1111, 0b1001), not_inserted }, // непустая маска в сет с одной пустой маской
		{ clearSetCommand },

		// частичная маска
		{ CANMsgIDFilter_t(0b0100, 0b1011), inserted },
		{ CANMsgIDFilter_t(0b0010, 0b1101), not_inserted },
		{ CANMsgIDFilter_t(0b1111, 0b1111), inserted },
		{ CANMsgIDFilter_t(0b0110, 0b1101), not_inserted },
		{ CANMsgIDFilter_t(0b1110, 0b1101), inserted },
	};

	set_non_intersecting_id_filters filters;

	for(auto &testCase:cases)
	{
		if(testCase.clearSet) { filters.clear(); continue; }

		auto res = filters.insert(testCase.filter).second;
		if(res != testCase.result)
		{
			correct = false;
			qDebug() << "TestCANMsgIDFilter_t_set_work error:";
			qDebug() << "filters.insert("+testCase.filter.ToStr(2)+") result is "+(res == inserted ? "inserted" : "not inserted")+
					", but expected "+(testCase.result == inserted ? "inserted" : "not inserted");
		}
	}

	return correct;
}

void CANMsgDataFilter_t::Set(const std::array<u8, 8> & aFilter, const std::array<u8, 8> & aMask)
{
	for(int i=0; i<8; i++)
	{
		filterBitset[i] = aFilter[i];
		maskBitset[i] = aMask[i];
	}
}

void CANMsgDataFilter_t::Set(const std::array<std::bitset<8>, 8> & aFilter, const std::array<std::bitset<8>, 8> & aMask)
{
	filterBitset = aFilter;
	maskBitset = aMask;
}

void CANMsgDataFilter_t::SetFilter(const std::array<u8, 8> & aFilter)
{
	for(int i=0; i<8; i++)
	{
		filterBitset[i] = aFilter[i];
	}
}

void CANMsgDataFilter_t::SetMask(const std::array<u8, 8> & aMask)
{
	for(int i=0; i<8; i++)
	{
		maskBitset[i] = aMask[i];
	}
}

bool CANMsgDataFilter_t::HasMask() const
{
	for(int i=0; i<8; i++)
		if(maskBitset[i].to_ulong()) return true;
	return false;
}

bool CANMsgDataFilter_t::UniteFilters(const CANMsgDataFilter_t & aFilter)
{
	bool intersects = false;
	for(int byte = 0; byte<8; byte++)
	{
		for(int bit=0; bit<8; bit++)
		{
			if(aFilter.maskBitset[byte][bit])
			{
				if(maskBitset[byte][bit])
				{
					intersects = true;
					continue;
				}

				maskBitset[byte][bit] = aFilter.maskBitset[byte][bit];
				filterBitset[byte][bit] = aFilter.filterBitset[byte][bit];
			}
		}
	}
	return !intersects;
}

bool CANMsgDataFilter_t::FromStr(QString aFilter, int filterBase, QString aMask)
{
	bool retVal = true;
	bool checkToInt;

	aFilter.replace(" ", "");
	aMask.replace(" ", "");

	for(int i=0; i<8; i++)
	{
		int len = 8;  // для filterBase == 2;
		if(filterBase == 10) len = 3;
		if(filterBase == 16) len = 2;

		filterBitset[i] = aFilter.left(len).toUInt(&checkToInt,filterBase);
		if(!checkToInt) retVal = false;
		aFilter.remove(0,len);

		maskBitset[i] = aMask.left(8).toUInt(&checkToInt,2);
		if(!checkToInt) retVal = false;
		aMask.remove(0,8);
	}
	return retVal;
}

QString CANMsgDataFilter_t::FilterToStr(int base) const
{
	QString ret;
	for(int i=0; i<8; i++) ret += QString::number(filterBitset[i].to_ulong(), base) + " ";
	return ret;
}

QString CANMsgDataFilter_t::MaskToStr(int base) const
{
	QString ret;
	for(int i=0; i<8; i++) ret += QString::number(maskBitset[i].to_ulong(), base) + " ";
	return ret;
}

QString CANMsgDataFilter_t::ToStr(int base) const
{
	return "{ F:" + FilterToStr(base) + "| M:" + MaskToStr(base) + "}";
}

bool CANMsgDataFilter_t::CheckMsg(const CANMsg_t & msg) const
{
	for(uint dataIndex=0; dataIndex<8; dataIndex++)
	{
		if(maskBitset[dataIndex].any()) // если есть какая-то маска на это поле данных
		{
			if(dataIndex >= msg.length) return false; // если сообщение короче маски

			std::bitset<8> data_bits = msg.data[dataIndex];
			for(int bitIndex=0; bitIndex<8; bitIndex++)
			{
				if(maskBitset[dataIndex][bitIndex]) // если бит в маске равен 1
				{
					if(data_bits[bitIndex] != filterBitset[dataIndex][bitIndex])
						return false; // если бит в дате не равен биту в фильтре
				}
			}
		}
	}
	return true;
}

CompareFilterRes CANMsgDataFilter_t::Compare(const CANMsgDataFilter_t &lhs, const CANMsgDataFilter_t &rhs)
{
	for(int dataIndex=0; dataIndex<CANMsg_t::dataFieldsCount; dataIndex++)
	{
		auto &lhsMask = lhs.Mask()[dataIndex];
		auto &rhsMask = rhs.Mask()[dataIndex];
		auto &lhsFilter = lhs.Filter()[dataIndex];
		auto &rhsFilter = rhs.Filter()[dataIndex];

		if(lhsMask == CANMsg_t::fullMask_8bit and rhsMask == CANMsg_t::fullMask_8bit)
		{
			if(lhsFilter == rhsFilter)
				continue; // тут нужно continue, потому что если поле данных совпало, то может в других полях будут отличия
			else
				return lhsFilter.to_ulong() < rhsFilter.to_ulong() ? CompareFilterRes::lower : CompareFilterRes::greater;
		}

		// если маска поля пустая
		if(lhsMask.to_ulong() == 0 or rhsMask.to_ulong() == 0) continue; // пропускаем

		for(int bitIndex=0; bitIndex<CANMsg_t::dataOneFieldBitsSize; bitIndex++)
		{
			bool lhsMaskBit = lhsMask[bitIndex];
			bool rhsMaskBit = rhsMask[bitIndex];
			bool lhsFilterBit = lhsFilter[bitIndex];
			bool rhsFilterBit = rhsFilter[bitIndex];

			// если бит маски 0
			if (lhsMaskBit == 0 or rhsMaskBit == 0)
			{
				continue; // пропускаем
			}
			else
			{
				if(lhsFilterBit != rhsFilterBit) // если есть различие в фильтре
					return lhsFilterBit < rhsFilterBit ? CompareFilterRes::lower : CompareFilterRes::greater; // сравниваем биты фильтра
			}
		}
	}

	return CompareFilterRes::intersects; // фильтры пересекаются
}

bool CANMsgDataFilter_t::TestCompare()
{
	using filter = CANMsgDataFilter_t;
	using arr8 = std::array<u8,8>;

	bool correct = true;

	struct TestCase {
		filter lhs;
		filter rhs;
		CompareFilterRes result;
	};

	std::vector<TestCase> cases{
		// пустые маски
		{	filter(arr8{0b11111111, 0, 0, 0, 0, 0, 0, 0}, arr8{0, 0, 0, 0, 0, 0, 0, 0}),
			filter(arr8{0b11111111, 0, 0, 0, 0, 0, 0, 0}, arr8{0, 0, 0, 0, 0, 0, 0, 0}),
			CompareFilterRes::intersects},
//		{	CANMsgDataFilter_t(0b1111, 0b0000),
//			CANMsgDataFilter_t(0b1001, 0b0000),
//			CompareFilterRes::intersects},
//		{	CANMsgDataFilter_t(0b1001, 0b0000),
//			CANMsgDataFilter_t(0b1111, 0b0000),
//			CompareFilterRes::intersects},

//		// полные маски
//		{	CANMsgDataFilter_t(0b0000, 0xFFFFFFFF),
//			CANMsgDataFilter_t(0b0000, 0xFFFFFFFF),
//			CompareFilterRes::intersects},
//		{	CANMsgDataFilter_t(0b1111, 0xFFFFFFFF),
//			CANMsgDataFilter_t(0b1001, 0xFFFFFFFF),
//			CompareFilterRes::greater},
//		{	CANMsgDataFilter_t(0b1001, 0xFFFFFFFF),
//			CANMsgDataFilter_t(0b1111, 0xFFFFFFFF),
//			CompareFilterRes::lower},
//		{	CANMsgDataFilter_t(0b1011, 0xFFFFFFFF),
//			CANMsgDataFilter_t(0b1111, 0xFFFFFFFF),
//			CompareFilterRes::lower},

//		// частичные маски
		{	filter(arr8{0b01111111, 0, 0, 0, 0, 0, 0, 0}, arr8{0b11111111, 0, 0, 0, 0, 0, 0, 0}),
			filter(arr8{0b01110000, 0, 0, 0, 0, 0, 0, 0}, arr8{0b01110000, 0, 0, 0, 0, 0, 0, 0}),
			CompareFilterRes::intersects},
//		{	CANMsgDataFilter_t(0b0000, 0b1011),
//			CANMsgDataFilter_t(0b0000, 0b1101),
//			CompareFilterRes::intersects},
//		{	CANMsgDataFilter_t(0b1111, 0b1011),
//			CANMsgDataFilter_t(0b1011, 0b1011),
//			CompareFilterRes::intersects},
//		{	CANMsgDataFilter_t(0b0011, 0b1011),
//			CANMsgDataFilter_t(0b1111, 0b1011),
//			CompareFilterRes::lower},

//		{	CANMsgDataFilter_t(0b1111, 0b1011),
//			CANMsgDataFilter_t(0b1101, 0b1011),
//			CompareFilterRes::greater},
//		{	CANMsgDataFilter_t(0b1111, 0b1011),
//			CANMsgDataFilter_t(0b1011, 0b1011),
//			CompareFilterRes::intersects},
//		{	CANMsgDataFilter_t(0b1111, 0b1011),
//			CANMsgDataFilter_t(0b1110, 0b1011),
//			CompareFilterRes::greater},

//		{	CANMsgDataFilter_t(0b1101, 0b1011),
//			CANMsgDataFilter_t(0b1011, 0b1101),
//			CompareFilterRes::intersects},
//		{	CANMsgDataFilter_t(0b1100, 0b1011),
//			CANMsgDataFilter_t(0b1011, 0b1101),
//			CompareFilterRes::lower},
//		{	CANMsgDataFilter_t(0b1101, 0b1011),
//			CANMsgDataFilter_t(0b0011, 0b1101),
//			CompareFilterRes::greater},

//		{	CANMsgDataFilter_t(0b1101, 0b1011), // тест на порядок оценки битов - от младших к старшим или от старших к младшим
//			CANMsgDataFilter_t(0b0010, 0b1101), // поскольку результат - greater порядок оценки от младших
//			CompareFilterRes::greater},
	};

	for(auto &testCase:cases)
	{
		auto res = Compare(testCase.lhs, testCase.rhs);
		if(res != testCase.result)
		{
			correct = false;
			qDebug() << "TestCANMsgIDFilter_cmp error:";
			qDebug() << "Compare("+testCase.lhs.ToStr(2)+", "+testCase.rhs.ToStr(2)+") result is "+CompareFilterResToString(res)+
					", but expected "+CompareFilterResToString(testCase.result);
		}
	}

	return correct;
}

void CANMsg_t::Set(u32 aID, const std::array<u8,8> &aData, u8 aLength, u32 aRegime, u32 aTimeStamp)
{
	ID = aID;
	length = aLength;
	regime = aRegime;
	timeStamp = aTimeStamp;
	data = aData;
}

void CANMsg_t::CopyCanMsg(CANMsg_t * dstMsg) const
{
	dstMsg->ID = this->ID;
	dstMsg->data[0] = this->data[0];
	dstMsg->data[1] = this->data[1];
	dstMsg->data[2] = this->data[2];
	dstMsg->data[3] = this->data[3];
	dstMsg->data[4] = this->data[4];
	dstMsg->data[5] = this->data[5];
	dstMsg->data[6] = this->data[6];
	dstMsg->data[7] = this->data[7];
	dstMsg->length = this->length;
	dstMsg->regime = this->regime;
	dstMsg->timeStamp = this->timeStamp;
}

QString CANMsg_t::ToStr(int base) const
{
	QString str = QString::number(this->ID, base);
	QString regime = QString::number(this->regime, 2);
	regime = regime.rightJustified(3,'0');
	str += " R:0b" + regime;
	str += " L:" + QString::number(this->length, 10) + " ";
	if(this->length)
	{
		str += "{ ";
		for(unsigned int i = 0; i < this->length; i++)
			str += QString::number(this->data[i], base) + " ";
		str += "}";
	}
	str += " T:";
	str += QString::number(this->timeStamp);
	return str;
}

QString CANMsg_t::ToStrExt(int base) const
{
	QString ID = QString::number(this->ID, base) + " ";
	if(base == 16) ID = ID.rightJustified(8 + 1,'0');     // +1 для пробела
	if(base == 10) ID = ID.rightJustified(10 + 1,'0');
	if(base == 2) ID = ID.rightJustified(32 + 1,'0');

	QString ret;
	if     (this->regime == 0b100)  ret = "EFF     ";
	else if(this->regime == 0b101)  ret = "EFF RTR ";
	else if(this->regime == 0b000)  ret = "SFF     ";
	else if(this->regime == 0b001)  ret = "SFF RTR ";
	else                            ret = "ERR RGM ";

	if	   (base == 2)	ret += "BIN ";
	else if(base == 10) ret += "DEC ";
	else if(base == 16) ret += "HEX ";
	else		ret += "UND ";

	ret += std::move(ID);
	ret += QString::number(this->length);
	ret += ' ';

	for(unsigned int i = 0; i < this->length; i++)
	{
		if(base == 16)
		{
			ret += " ";
			if(this->data[i] < 0x10) ret += "0";
			ret += QString::number(this->data[i], base);
		}
		if(base == 10)
		{
			if(this->data[i] < 10) ret += "00";
			else if(this->data[i] < 100) ret += "0";
			ret += QString::number(this->data[i], base);
		}
		if(base == 2)
		{
			auto tmp = QString::number(this->data[i], base);
			ret += tmp.rightJustified(8,'0');
		}
		ret += ' ';
	}

	QString timeSt = QString::number(this->timeStamp);
	ret += timeSt.rightJustified(10,'0');

	return ret;
}

CANMsg_t& CANMsg_t::FromStrExt(const QString &str, int base)
{
	bool eff = str.contains("EFF");
	bool sff = str.contains("SFF");
	bool rtr = str.contains("RTR");

	bool bin = str.contains("BIN");
	bool dec = str.contains("DEC");
	bool hex = str.contains("HEX");

	if(eff && sff) { qCritical() << "FromStrExt2: str ["+str+"] contains both EFF RTR, frame not set"; return *this; }

	int count = 0;
	if(bin) count++;
	if(dec) count++;
	if(hex) count++;
	if(count != 1) { qCritical() << "FromStrExt2: str ["+str+"] wrong encodings, frame not set"; return *this; }

	auto words = str.split(" ", QString::SkipEmptyParts);

	int id_word_index = 2;
	if(rtr) id_word_index = 3;
	int len_word_index = id_word_index + 1;

	if(len_word_index >= words.size()) { qCritical() << "FromStrExt2: str ["+str+"] wrong length 1"; return *this; }

	ID = words[id_word_index].toUInt(nullptr,base);
	length = words[len_word_index].toUInt(nullptr,10);

	int time_stamp_index = len_word_index + length + 1;

	if(time_stamp_index >= words.size()) { qCritical() << "FromStrExt2: str ["+str+"] wrong length 2"; return *this; }

	for(int i=0; i<length; i++)
		data[i] = words[len_word_index + 1 + i].toUInt(nullptr,base);

	timeStamp = words[time_stamp_index].toUInt(nullptr,base);

	if     (eff && !rtr) this->regime = 0b100;
	else if(eff &&  rtr) this->regime = 0b101;
	else if(sff && !rtr) this->regime = 0b000;
	else if(sff &&  rtr) this->regime = 0b001;
	else                 this->regime = 0b010;

	return *this;
}

bool CANMsg_t::IsRTR() const
{
	return regime & 1;
}

bool CANMsg_t::IsEFF() const
{
	return (regime >> 2) & 1;
}

bool CANMsg_t::CheckFilter(const CANMsgIDFilter_t & filter) const
{
	return filter.CheckMsg(*this);
}

bool CANMsg_t::CheckFilter(const CANMsgDataFilter_t & filter) const
{
	return filter.CheckMsg(*this);
}

bool CANMsg_t::operator==(const CANMsg_t & msgToCmp) const
{
	return (ID == msgToCmp.ID &&
			data == msgToCmp.data &&
			length == msgToCmp.length &&
			regime == msgToCmp.regime);
}

bool CANMsg_t::operator!=(const CANMsg_t & msgToCmp) const
{
	return (ID != msgToCmp.ID ||
			data != msgToCmp.data ||
			length != msgToCmp.length ||
			regime != msgToCmp.regime);
}

bool CANMsg_t::TestToAndFromStrExt()
{
	bool correct = true;
	bool printResAlwause = false;
	//printResAlwause = true;

	std::vector<CANMsg_t> inputs;
	std::vector<int> encs;
	std::vector<QString> convertResults;

	inputs.emplace_back(CANMsg_t(0x1010101, {8,7,6,5,4,3,2,1}, 8, 0b100, 0));
	encs.emplace_back(2);
	convertResults.emplace_back("EFF     BIN 00000001000000010000000100000001 8 "
								"00001000 00000111 00000110 00000101 00000100 00000011 00000010 00000001 0000000000");

	inputs.emplace_back(CANMsg_t(0x1010101, {8,7,6,5,4,3}, 6, 0b100, 0));
	encs.emplace_back(2);
	convertResults.emplace_back("EFF     BIN 00000001000000010000000100000001 6 "
								"00001000 00000111 00000110 00000101 00000100 00000011 0000000000");

	inputs.emplace_back(CANMsg_t(0x1010101, {8,7,6,5,4,3}, 6, 0b101, 0));
	encs.emplace_back(2);
	convertResults.emplace_back("EFF RTR BIN 00000001000000010000000100000001 6 "
								"00001000 00000111 00000110 00000101 00000100 00000011 0000000000");

	inputs.emplace_back(CANMsg_t(0x1010101, {}, 0, 0b001, 0));
	encs.emplace_back(2);
	convertResults.emplace_back("SFF RTR BIN 00000001000000010000000100000001 0 0000000000");

	inputs.emplace_back(CANMsg_t(0x1010101, {}, 0, 0b000, 0));
	encs.emplace_back(2);
	convertResults.emplace_back("SFF     BIN 00000001000000010000000100000001 0 0000000000");

	inputs.emplace_back(CANMsg_t(0x1010101, {8,7,6,5,4,3,2,1}, 8, 0b100, 254));
	encs.emplace_back(10);
	convertResults.emplace_back("EFF     DEC 0016843009 8 008 007 006 005 004 003 002 001 0000000254");

	inputs.emplace_back(CANMsg_t(0x1010101, {8,7,6,5,4,3}, 6, 0b101, 0));
	encs.emplace_back(10);
	convertResults.emplace_back("EFF RTR DEC 0016843009 6 008 007 006 005 004 003 0000000000");

	inputs.emplace_back(CANMsg_t(0x1010101, {}, 0, 0b001, 0));
	encs.emplace_back(10);
	convertResults.emplace_back("SFF RTR DEC 0016843009 0 0000000000");

	inputs.emplace_back(CANMsg_t(0x1010101, {8,7,6,5,4,3,2,1}, 8, 0b100, 0));
	encs.emplace_back(16);
	convertResults.emplace_back("EFF     HEX 01010101 8  08  07  06  05  04  03  02  01 0000000000");

	inputs.emplace_back(CANMsg_t(0x1010101, {8,7,6,5,4,3}, 6, 0b101, 0));
	encs.emplace_back(16);
	convertResults.emplace_back("EFF RTR HEX 01010101 6  08  07  06  05  04  03 0000000000");

	inputs.emplace_back(CANMsg_t(0x1010101, {}, 0, 0b001, 0));
	encs.emplace_back(16);
	convertResults.emplace_back("SFF RTR HEX 01010101 0 0000000000");

	for(uint i=0; i<inputs.size(); i++)
	{
		if(inputs[i].ToStrExt(encs[i]) != convertResults[i])
		{
			correct = false;
			qDebug() << "Тест "+QString::number(i+1)+" ToStrExt2("+inputs[i].ToStr()+") выдал неожиданный результат!"
						+"\n\tрезультат <" + inputs[i].ToStrExt(encs[i]) + "> а ожидается <" + convertResults[i] + ">";
		}
		else if(printResAlwause) qDebug() << "Тест1 ToStrExt2("+inputs[i].ToStr()+") "
											 +"выдал ожидаемый результат " + convertResults[i];

		if(inputs[i] != CANMsg_t().FromStrExt(inputs[i].ToStrExt(2),2))
		{
			qDebug() << "Тест2 "+QString::number(i+1)+" FromStrExt2("+inputs[i].ToStrExt(2)+") выдал неожиданный результат!"
						+"\n\tрезультат <" + CANMsg_t().FromStrExt(inputs[i].ToStrExt(2)).ToStr()
						+ "> а ожидается <" + inputs[i].ToStr() + ">";
		}
		else if(printResAlwause) qDebug() << "Тест2 FromStrExt2("+inputs[i].ToStr()+") "
											 +"выдал ожидаемый результат " + inputs[i].ToStr();

		if(inputs[i] != CANMsg_t().FromStrExt(inputs[i].ToStrExt(10),10))
		{
			qDebug() << "Тест10 "+QString::number(i+1)+" FromStrExt2("+inputs[i].ToStrExt(10)+") выдал неожиданный результат!"
						+"\n\tрезультат <" + CANMsg_t().FromStrExt(inputs[i].ToStrExt(10)).ToStr()
						+ "> а ожидается <" + inputs[i].ToStr() + ">";
		}
		else if(printResAlwause) qDebug() << "Тест10 FromStrExt2("+inputs[i].ToStr()+") "
											 +"выдал ожидаемый результат " + inputs[i].ToStr();

		if(inputs[i] != CANMsg_t().FromStrExt(inputs[i].ToStrExt(16),16))
		{
			qDebug() << "Тест16 "+QString::number(i+1)+" FromStrExt2("+inputs[i].ToStrExt(16)+") выдал неожиданный результат!"
						+"\n\tрезультат <" + CANMsg_t().FromStrExt(inputs[i].ToStrExt(16)).ToStr()
						+ "> а ожидается <" + inputs[i].ToStr() + ">";
		}
		else if(printResAlwause) qDebug() << "Тест16 FromStrExt2("+inputs[i].ToStr()+") "
											 +"выдал ожидаемый результат " + inputs[i].ToStr();
	}

	return correct;
}

QString ICANChannel::StatusToStr(int code)
{
	switch (code)
	{
	case STATUS_ERROR : return "STATUS_ERROR";
	case UNAVIABLE : return "UNAVIABLE";
	case AVIABLE : return "AVIABLE";
	case STARTED : return "STARTED";
	default: return "Wrong code!";
	}
}

int ICANChannel::StatusStrToInt(QString statusStr)
{
	if(statusStr == "UNAVIABLE") return UNAVIABLE;
	if(statusStr == "AVIABLE") return AVIABLE;
	if(statusStr == "STARTED") return STARTED;
	else return STATUS_ERROR;
}

QString ICANChannel::ErrorCodeToStr(int errorCode)
{
	switch (errorCode)
	{
	case NO_ERRORS : return "NO_ERRORS";
	case NO_SPECIFIED : return "Unknoun error";
	case BUSY : return "Device is busy";
	case MEMORY_ERROR : return "Memory error";
	case STATE_ERROR : return "Device state error";
	case CALL_ERROR : return "Call error";
	case INVALID_PARAMETR : return "Parametr error";
	case ACCESS_ERROR : return "Ошибка доступа к ресурсу";
	case NO_RESOURCES : return "Resourses error";
	case NOT_IMPLEMENT : return "Function error";
	case IO_ERROR : return "Input/output error";
	case NO_DEVICE : return "Device not found";
	case INTERRUPT : return "Interrupt event";
	case RESOURCE_ERROR : return "Нет ресурсов";
	case TYMEOUT : return "Timeout error";
	case MOCK_ERROR : return "Вызов нереализованной функции";
	default : return "Wrong error code";
	}
}

QString ICANChannel::BaudToStr(int code)
{
	switch (code)
	{
	case BR_ERROR : return "BR_ERROR";
	case BR_125K : return "BR_125K";
	case BR_250K : return "BR_250K";
	case BR_500K : return "BR_500K";
	case BR_1M : return "BR_1M";
	default: return "Wrong code!";
	}
}

int ICANChannel::BaudStrToInt(QString baudStr)
{
	if(baudStr == "BR_125K") return BR_125K;
	if(baudStr == "BR_250K") return BR_250K;
	if(baudStr == "BR_500K") return BR_500K;
	if(baudStr == "BR_1M") return BR_1M;
	else return BR_ERROR;
}

QString ICANChannel::RegimeToStr(int code)
{
	switch (code)
	{
	case REG_ERROR : return "REG_ERROR";
	case REG_CAN11 : return "REG_CAN11";
	case REG_CAN29 : return "REG_CAN29";
	case REG_CAN11_29 : return "REG_CAN11_29";
	default: return "Wrong code!";
	}
}

int ICANChannel::RegimeStrToInt(QString regimeStr)
{
	if(regimeStr == "REG_CAN11") return REG_CAN11;
	if(regimeStr == "REG_CAN29") return REG_CAN29;
	if(regimeStr == "REG_CAN11_29") return REG_CAN11_29;
	else return REG_ERROR;
}

QString ICANChannel::CrChannelName(int numberAbs, int numberOnInt, QString interface)
{
	return QString("Channel ") + QString::number(numberAbs) + " : " + QString::number(numberOnInt) + " on " + interface;
}

bool ICANChannelTests::AllTests()
{
	bool ok = true;
	if(!CANMsg_t::TestToAndFromStrExt()) ok = false;

	if(!CANMsgIDFilter_t::TestCompare()) ok = false;
	if(!CANMsgIDFilter_t::Test_set_non_intersecting_id_filters()) ok = false;

	if(!CANMsgDataFilter_t::TestCompare()) ok = false;

	return ok;
}

#endif // ICANCHANNEL_H
