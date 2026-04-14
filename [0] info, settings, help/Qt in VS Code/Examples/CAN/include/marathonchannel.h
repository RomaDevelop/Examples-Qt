#ifndef MARATHONCHANNEL_H
#define MARATHONCHANNEL_H

#include <queue>
#include <thread>
#include <mutex>

#include <QTimer>

#include "chai.h"
#include "icanchannel.h"
#include "marathoninterface.h"

#include "MarathonInterface_global.h"

class MarathonChannel : public ICANChannel
{
	int numberOnInterface;
	int numberAbsolut;
	QString name;
	bool started_us;
	int regime;
	int baud;
	unsigned long appFilter;
	unsigned long appMask;
	unsigned long progFilter;
	unsigned long progMask;

	// CBF_t CBFMessage;	// не тербуется, используется функционал CHAI
	// CBF_t CBFError;		// не тербуется, используется функционал CHAI
	CBFunctionWriteLog_t CBFLog = nullptr;
	FunctionWriteTraffic_t FunctionWriteTraffic = nullptr;

	std::thread *threadCBMsg = nullptr;
	bool threadCBMsgStop = false;
	std::thread *threadCBErr = nullptr;
	bool threadCBErrStop = false;

	MarathonInterface *parentInterface;

public:
	MarathonChannel(int numberOnBoard_, int numberAbsolut_, QString name_, MarathonInterface *parentInterface_);
	~MarathonChannel() override;

	QString GetName() const override;
	int	GetNumberOnInterface() const override;
	int	GetNumberAbsolut() const override;
	int GetRegime() const override;
	int GetBaud() const override;
	void GetAppFilter(unsigned long &filter, unsigned long &mask) const override;
	void GetProgFilter(unsigned long &filter, unsigned long &mask) const override;

	// если started_us - STARTED
		// если нет, если CiOpen выдаёт ошибку - UNAVIABLE
			// если CiOpen, CiClose успешно - AVIABLE
				// если были ошибки - STATUS_ERROR
	int GetStatus() const override;
	// быстрая функция для проверки запущен ли
		// возвращает STARTED, UNAVIABLE или STATUS_ERROR
	int IsStarted() const;

	// если канал доступен - выставляет параметр
	// если канал запущен - останавливает, выставляет параметр, запускает
	int SetRegime(unsigned int regime) override;
	int SetBaud(unsigned int baud) override;
	int SetAppFilter(unsigned long filter, unsigned long mask) override;
	int SetProgFilter(unsigned long filter, unsigned long mask) override;

	// если статус определился корректно
		// если канал недоступен - возвращаем ошибку
			// если канал доступен - делаем опен(с режимом), скорость, фильтр и старт
				// если не удалось открыть - возвращаем ошибку
				// если удалось открыть  - устанавливаем SetBaudInt и CiSetFilter
				// если удалось установить скорость и фильтр - CiStart
					// если не удалось стартовать - возвращаем ошибку
					// если удалось стартовать - started_us, NO_ERROR
			// если статус == STARTED - возвращаем ошибку STATE_ERROR
	int Start() override;
	int Stop() override;

	virtual int Set(int regime, int baud, int status) override;

	int WriteMsg(const CANMsg_t *Msg) override;

	std::pair<int,int> GetMsgCnt() const override;
	std::pair<int,int> ReadMsg(CANMsg_t *Msg, unsigned int cnt = 1) override;

	/*
	В библиотеке: ограничится либо только вызовами CiSetCB(), либо только
	вызовами CiSetCBex. Поведение библиотеки при
	одновременном использовании функций CiSetCB() и
	CiSetCBex() не определено. */
	typedef void (*ci_cb)(_s16);
	//typedef void (*ci_cb_ex)(_u8, _s16, void*);

	int SetCBFunctionForError(CBFunction_t CBFunction) override;
	int SetCBFunctionForMessage(CBFunction_t CBFunction) override;
	int SetCBFunctionForMessage2(CBFunction2_t CBFunction, void *handler) override;
	int SetCBFunctionForLog(CBFunctionWriteLog_t CBFLog) override;
	int SetFunctionWriteTraffic(FunctionWriteTraffic_t FTraffic) override;

	///\brief вызывает функцию записи лога если она зарегистрирована
	void WriteLog(const QString &log) const;
	void WriteLogFromThread(const QString &log) const;
	///\brief вызывает CiSetBaud с указанной скоростью
	int SetBaudInt(int channel, int baud_);
	///\brief преобразует canmsg_t в CANMsg_t
	static void ConvertMsgChaiToCAN(const canmsg_t *chaiMSG, CANMsg_t *CANmsg);
	///\brief преобразует CANMsg_t в canmsg_t
	static void ConvertMsgCANToChai(const CANMsg_t *CANmsg, canmsg_t *chaiMSG);
	///\brief преобразует код ошибки chai в ICANChannel::ERROR_CODE
	int ConvertErrorCode(int sourceCode) const;

	void StopThread(std::thread **th, bool &stopFlag);

	static QString versionToStr(int version);
	static QString versionToStr(std::tuple<int,int,int> V_maj_min_sub);
	static std::tuple<int,int,int> GetVersion(int version);
	// if (V0_maj_min_sub > V1_maj_min_sub) return -1;
	// if (V0_maj_min_sub == V1_maj_min_sub) return 0;
	// if (V0_maj_min_sub < V1_maj_min_sub) return 1;
	int VersionCmp(std::tuple<int,int,int> V0_maj_min_sub, std::tuple<int,int,int> V1_maj_min_sub);
	enum RES_VERS_CMP
	{
		LEFT_NEWER = -1,
		SAME = 0,
		RIGHT_NEWER = 1
	};

private:
	mutable std::queue<QString> logsFromThread;
	mutable std::mutex mtxLogFromThread;
	std::unique_ptr<QTimer> logsFromThreadTimer;
	void LogsSend();
};
#endif // MARATHONCHANNEL_H
