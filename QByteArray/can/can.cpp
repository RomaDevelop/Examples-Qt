#include <memory>
#include "chai.h"
#include "can.h"

//----------------------------------------------------------------------------------------------------------
// инициализация статических полей в CAN_PROCESSING_OBJECT
CAN_PROCESSING_OBJECT *CAN_PROCESSING_OBJECT::CAN_processing_object=nullptr;
//----------------------------------------------------------------------------------------------------------
// инициализация статических полей в CAN
int CAN::ev {0};
CAN *CAN::CAN_object=nullptr;
CAN_PROCESSING_OBJECT *CAN::CAN_processing_object=nullptr;
//----------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------
// методы CAN_PROCESSING_OBJECT
//----------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------
CAN_PROCESSING_OBJECT::CAN_PROCESSING_OBJECT()
{
	CAN_processing_object=this;
}
//----------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------
// методы CAN
//----------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------
CAN::CAN(CAN_PROCESSING_OBJECT *CAN_processing_object_, int channel_)
{
	inited =  false;
	opened =  false;
	started = false;
	event_RC_reged = false;

	channel=channel_;

	CAN::CAN_object=this;
	CAN::CAN_processing_object=CAN_processing_object_;

	int ret;
	if((ret=CiInit()) < 0)
		CAN::CAN_processing_object->Err_processing(ret);
		else
		{
			inited=true;
			CAN_processing_object->Success_processing("CAN() Success");
		}
}
//----------------------------------------------------------------------------------------------------------
void CAN::set_chanel(int channel_)
{
	channel=channel_;
}
//----------------------------------------------------------------------------------------------------------
void CAN::open()
{
	int ret;
	if((ret=CiOpen(channel,CIO_CAN11|CIO_CAN29)) < 0) CAN::CAN_processing_object->Err_processing(ret);
		else
		{
			opened=true;
			CAN_processing_object->Success_processing("open() Success");
		}
}
//----------------------------------------------------------------------------------------------------------
void CAN::set_bound(_u8 bt0, _u8 bt1) // значения скорости BCI_1M, BCI_800K, BCI_500K, BCI_250K, BCI_125K, BCI_50K, BCI_20K, BCI_10K
{
	int ret;
	if((ret = CiSetBaud(channel, bt0, bt1)) < 0) CAN::CAN_processing_object->Err_processing(ret);
	else {
		CAN_processing_object->Success_processing("set_bound() Success");
	}

}
//----------------------------------------------------------------------------------------------------------
void CAN::close()
{
	int ret;
	if((ret=CiClose(channel)) < 0) CAN::CAN_processing_object->Err_processing(ret);
		else
		{
			opened=false;
			CAN_processing_object->Success_processing("close() Success");
		}
}
//----------------------------------------------------------------------------------------------------------
void CAN::start()
{
	int ret;
	if((ret=CiStart(channel)) < 0) CAN::CAN_processing_object->Err_processing(ret);
		else
		{
			started=true;
			CAN_processing_object->Success_processing("start() Success");
		}
}
//----------------------------------------------------------------------------------------------------------
void CAN::stop()
{
	int ret;
	if((ret=CiStop(channel)) < 0) CAN::CAN_processing_object->Err_processing(ret);
	else
	{
		started=false;
		CAN_processing_object->Success_processing("stop() Success");
	}
}
//----------------------------------------------------------------------------------------------------------
void CAN::transmit()
{
	int ret;
	if((ret=CiWrite(CAN_object->channel, &(CAN::CAN_processing_object->msg), 1)) < 0) CAN::CAN_processing_object->Err_processing(ret);
	else
	{
		CAN_processing_object->Success_processing("transmit() Success");
	}
}
//----------------------------------------------------------------------------------------------------------
void CAN::read_msg()
{
	int ret;
	if((ret=CiRead(CAN_object->channel, &(CAN::CAN_processing_object->msg), 1)) < 0) CAN::CAN_processing_object->Err_processing(ret);
}
//----------------------------------------------------------------------------------------------------------
void CAN::reg_event_RC()
{
	int ret;
	if((ret=CiSetCB(channel, CIEV_RC, CAN::RC_processing_static)) < 0) CAN::CAN_processing_object->Err_processing(ret);
	else
	{
		event_RC_reged=true;
		CAN_processing_object->Success_processing("reg_event_RC() Success");
	}
}
//----------------------------------------------------------------------------------------------------------
void CAN::RC_processing_static(_s16 ev_)
{
	CAN::ev=ev_;
	CAN::read_msg();
	CAN::CAN_processing_object->RC_processing();
}
//----------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------
