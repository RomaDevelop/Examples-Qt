#ifndef CAN_H
#define CAN_H

#include <QString>
#include "chai.h"

/*
iprocessingmessage.h
marathoncontroller
icanphisic
canfilter

S:\___Server\03 Users\MeluzovAL\Projects\CAN_Qt
CAN_Test
CAN_Test_2
CANFilter
*/

class CAN_PROCESSING_OBJECT
{
public:
	canmsg_t msg;

	static CAN_PROCESSING_OBJECT *CAN_processing_object;

	CAN_PROCESSING_OBJECT();


	virtual void RC_processing() = 0;
	// RC_processing - обработка одного кадра находящегося в msg

	virtual void Err_processing(int err_code) = 0;
	virtual void Success_processing(QString Success) = 0;
};

//----------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------

class CAN
{
public:
	bool inited;
	bool opened;
	bool started;
	bool event_RC_reged;
	int  channel;

	static int ev;
	static CAN *CAN_object;
	static CAN_PROCESSING_OBJECT *CAN_processing_object;

	CAN(CAN_PROCESSING_OBJECT *CAN_processing_object, int chanel);
	void set_chanel(int chanel);
	void open();
	void set_bound(_u8 bt0, _u8 bt1); // значения скорости BCI_1M, BCI_800K, BCI_500K, BCI_250K, BCI_125K, BCI_50K, BCI_20K, BCI_10K
	void close();
	void start();
	void stop();
	void transmit();

	static void read_msg();
	// read_msg считывает кадр и записывает в CAN_processing_object->msg

	void reg_event_RC();
	// reg_event_RC регистрирует RC_processing_static как обработчик события CIEV_RC

	static void RC_processing_static(_s16 ev);
	// RC_processing_static делает
	// 1. Вызывает CAN::read_msg()
	// 2. вызывается CAN::CAN_processing_object->RC_processing()

	static int  chanels_count();
	static bool is_chanel_free(int chanel);
};

#endif // CAN_H
