/*
* can-echocb.c - example program to work with CHAI in callbacks mode.
* Program recieve frames from CAN-network (baudrate = 500K)
* and send it back.
*
* Copyright (C) 2002-2008 Marathon Ltd. Moscow
*
*/
#include <stdio.h>
#include <chai.h> /* includes declarations to work with CHAI */
#ifdef WIN32
#include <windows.h> // for Sleep()
#endif
_u8 chan;
/* callbacks forward definitions */
void cbrcv(_s16 sig);
void cberr(_s16 sig);
/* sleep function forward definitions */
void mysleep(unsigned int millisec);
int main(int argc, char **argv)
{
	int ret;
	if (argc != 2) {
		fprintf(stderr, "Usage: %s X \n", argv[0]);
		fprintf(stderr, " where X=0,1,2 ...\n");
		exit(1);
	}
	chan = atoi(argv[1]);
	if ((ret = CiInit()) < 0) {
		CiPerror(ret, "CHAI library initialization failed");
		exit(1);
	}
	/* open channel
* After operation complete we have one RC queues (with size
* CIQUE_DEFSIZE_RC of frames) with filter that accepts all frames.
* CAN controller will accept both 11bit and 29bit identifiers.
*/
	if ((ret = CiOpen(chan, CIO_CAN11 | CIO_CAN29)) < 0) {
		fprintf(stderr, "Error opening CAN channel %s\n", argv[1]);
		CiPerror(ret, "CiOpen");
		exit(1);
	}
	/* set baudrate to 500Kbit */
	if ((ret = CiSetBaud(chan, BCI_500K) < 0)) {
		CiPerror(ret, "can't set baud");
		CiClose(chan);
		exit(1);
	}

	/* Set callback cbrcv() on CIEV_RC (recieve frame from CAN) event. */
			if ((ret = CiSetCB(chan, CIEV_RC, cbrcv)) < 0) {
		CiPerror(ret, "can't set callback on CIEVRC");
		CiClose(chan);
		exit(1);
	}
	/* Set callback cberr() on CIEV_CANERR (error occured) event.
*/
	if ((ret = CiSetCB(chan, CIEV_CANERR, cberr)) < 0) {
		CiPerror(ret, "can't set callback on CIEV_CANERR");
		CiClose(chan);
		exit(1);
	}
	/* start CAN-controller
* After operation CAN-controller will be in RUNNING mode,
* i.e. it will send ACK and ERROR frames on the bus, so it will be
* "visible" by other nodes on the bus. Events start here also. */
	CiStart(chan);
	/* enter to main loop */
	while (1) {
		/* do nothing */
		mysleep(1);
	}
	/* never reach this point */
	exit(0);
}
/* this callback is called by CHAI each time
* CAN-frame arrive from the bus. */
void cbrcv(_s16 sig)
{
	canmsg_t rx;
	int ret;
	int i;
	ret = CiRead(chan, &rx, 1); /* read one frame from channel (RCqueue)*/
	if (ret > 0) {
		if (msg_iseff(&rx))
			printf("EFF ");
		else
			printf("SFF "); /* check frame format */
		printf("id=%#lx data:", rx.id); /* print frame identifier */
		if (msg_isrtr(&rx)) /* check frame is RTR */
			printf(" RTR ");
		else
			for (i = 0; i < rx.len; i++) /* print data field of the frame */
				printf(" %#x", rx.data[i]);
		printf("\n");
		rx.id = rx.id - 1;
		if (CiWrite(chan, &rx, 1) < 1) { /* write modified frame back to CAN */
			CiPerror(ret, "can't send frame back to CAN");
		}
	} else if (ret < 0) {
		CiPerror(ret, "error recieving frame from CAN");
	}
}
/* this callback will be called by CHAI each time
* error occured. Callback will recieve event code via
* sig argument. Event codes for CIEV_CANERR are
* defined in chai.h: CIEV_EWL, CIEV_BOFF, CIEV_HOVR,
* CIEV_WTOUT, CIEV_SOVR
*/
void cberr(_s16 sig)
{
	if (sig == CIEV_WTOUT) {
		printf("\n write timeout occured\n");
	} else if (sig == CIEV_EWL) {
		printf("\n Error Warning Limit occured\n");
	} else if (sig == CIEV_BOFF) {
		printf("\n Bus Off occured\n");
	} else if (sig == CIEV_HOVR) {
		printf("\n hardware overrun occured\n");
	} else if (sig == CIEV_SOVR) {
		printf("\n software overrun occured\n");
	}
}
void mysleep(unsigned int millisec)
{
#ifdef WIN32
	Sleep(millisec);
#else // LINUX
	usleep(1000*millisec);
#endif
}
