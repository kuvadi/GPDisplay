/*
 * comm.cpp
 *
 *  Created on: Apr 30, 2021
 *      Author: bbari
 */

#include "comm.h"
#include "main.h"
#include <read_sd.h>

char* formProtocol(){
	char* protocol;
	union{float f; char c[4];}uni_f;
	union{uint16_t ui16; char c[2];}uni_ui16;
	union{int16_t i16; char c[2];}uni_i16;
	union{uint8_t ui8; char c[1];}uni_ui8;
	union{uint32_t ui32; char c[4];}uni_ui32;

	switch(method){
	case CV:
		protocol = malloc(31*sizeof(char));
		uni_ui16.ui16 = 2000;
		protocol[1] = uni_ui16.c[0];
		protocol[2] = uni_ui16.c[1];
		uni_ui16.ui16 = qtime;
		protocol[3] = uni_ui16.c[0];
		protocol[4] = uni_ui16.c[1];
		uni_ui8.ui8 = cell;
		protocol[5] = uni_ui8.c[0];
		uni_ui8.ui8 = range;
		protocol[6] = uni_ui8.c[0];
		uni_ui16.ui16 = repeat;
		protocol[7] = uni_ui16.c[0];
		protocol[8] = uni_ui16.c[1];
		uni_ui8.ui8 = channel;
		protocol[9] = uni_ui8.c[0];
		uni_i16.i16 = er1;
		protocol[10] = uni_i16.c[0];
		protocol[11] = uni_i16.c[1];
		uni_i16.i16 = er2;
		protocol[12] = uni_i16.c[0];
		protocol[13] = uni_i16.c[1];
		uni_i16.i16 = ei;
		protocol[14] = uni_i16.c[0];
		protocol[15] = uni_i16.c[1];
		uni_f.f = scan;
		protocol[16] = uni_f.c[0];
		protocol[17] = uni_f.c[1];
		protocol[18] = uni_f.c[2];
		protocol[19] = uni_f.c[3];
		uni_f.f = resolution;
		protocol[20] = uni_f.c[0];
		protocol[21] = uni_f.c[1];
		protocol[22] = uni_f.c[2];
		protocol[23] = uni_f.c[3];
		uni_f.f = bipotE;
		protocol[24] = uni_f.c[0];
		protocol[25] = uni_f.c[1];
		protocol[26] = uni_f.c[2];
		protocol[27] = uni_f.c[3];
		uni_ui8.ui8 = bipotMode;
		protocol[28] = uni_ui8.c[0];
		uni_ui8.ui8 = primeChannel;
		protocol[29] = uni_ui8.c[0];
		protocol[30] = STOP_BYTE;




		break;
	case LSV:

		protocol = malloc(29 * sizeof(char));
		uni_ui16.ui16 = 2003;
		protocol[1] = uni_ui16.c[0];
		protocol[2] = uni_ui16.c[1];
		uni_ui16.ui16 = qtime;
		protocol[3] = uni_ui16.c[0];
		protocol[4] = uni_ui16.c[1];
		uni_ui8.ui8 = cell;
		protocol[5] = uni_ui8.c[0];
		uni_ui8.ui8 = range;
		protocol[6] = uni_ui8.c[0];
		uni_ui16.ui16 = repeat;
		protocol[7] = uni_ui16.c[0];
		protocol[8] = uni_ui16.c[1];
		uni_ui8.ui8 = channel;
		protocol[9] = uni_ui8.c[0];
		uni_i16.i16 = er1;
		protocol[10] = uni_i16.c[0];
		protocol[11] = uni_i16.c[1];
		uni_i16.i16 = er2;
		protocol[12] = uni_i16.c[0];
		protocol[13] = uni_i16.c[1];
		uni_f.f = scan;
		protocol[14] = uni_f.c[0];
		protocol[15] = uni_f.c[1];
		protocol[16] = uni_f.c[2];
		protocol[17] = uni_f.c[3];
		uni_f.f = resolution;
		protocol[18] = uni_f.c[0];
		protocol[19] = uni_f.c[1];
		protocol[20] = uni_f.c[2];
		protocol[21] = uni_f.c[3];
		uni_f.f = bipotE;
		protocol[22] = uni_f.c[0];
		protocol[23] = uni_f.c[1];
		protocol[24] = uni_f.c[2];
		protocol[25] = uni_f.c[3];
		uni_ui8.ui8 = bipotMode;
		protocol[26] = uni_ui8.c[0];
		uni_ui8.ui8 = primeChannel;
		protocol[27] = uni_ui8.c[0];
		protocol[28] = STOP_BYTE;

		break;
	case DPV:
		protocol = malloc(31 * sizeof(char));
		uni_ui16.ui16 = 2001;
		protocol[1] = uni_ui16.c[0];
		protocol[2] = uni_ui16.c[1];
		uni_ui16.ui16 = qtime;
		protocol[3] = uni_ui16.c[0];
		protocol[4] = uni_ui16.c[1];
		uni_ui8.ui8 = cell;
		protocol[5] = uni_ui8.c[0];
		uni_ui8.ui8 = range;
		protocol[6] = uni_ui8.c[0];
		uni_ui16.ui16 = repeat;
		protocol[7] = uni_ui16.c[0];
		protocol[8] = uni_ui16.c[1];
		uni_ui8.ui8 = channel;
		protocol[9] = uni_ui8.c[0];
		uni_i16.i16 = er1;
		protocol[10] = uni_i16.c[0];
		protocol[11] = uni_i16.c[1];
		uni_i16.i16 = er2;
		protocol[12] = uni_i16.c[0];
		protocol[13] = uni_i16.c[1];
		uni_f.f = step;
		protocol[14] = uni_f.c[0];
		protocol[15] = uni_f.c[1];
		protocol[16] = uni_f.c[2];
		protocol[17] = uni_f.c[3];
		uni_ui16.ui16 = amplitude;
		protocol[18] = uni_ui16.c[0];
		protocol[19] = uni_ui16.c[1];
		uni_ui16.ui16 = period;
		protocol[20] = uni_ui16.c[0];
		protocol[21] = uni_ui16.c[1];
		uni_ui16.ui16 = width;
		protocol[22] = uni_ui16.c[0];
		protocol[23] = uni_ui16.c[1];
		uni_f.f = bipotE;
		protocol[24] = uni_f.c[0];
		protocol[25] = uni_f.c[1];
		protocol[26] = uni_f.c[2];
		protocol[27] = uni_f.c[3];
		uni_ui8.ui8 = bipotMode;
		protocol[28] = uni_ui8.c[0];
		uni_ui8.ui8 = primeChannel;
		protocol[29] = uni_ui8.c[0];
		protocol[30] = STOP_BYTE;

		break;
	case NPV:
		protocol = malloc(29 * sizeof(char));
		uni_ui16.ui16 = 2004;
		protocol[1] = uni_ui16.c[0];
		protocol[2] = uni_ui16.c[1];
		uni_ui16.ui16 = qtime;
		protocol[3] = uni_ui16.c[0];
		protocol[4] = uni_ui16.c[1];
		uni_ui8.ui8 = cell;
		protocol[5] = uni_ui8.c[0];
		uni_ui8.ui8 = range;
		protocol[6] = uni_ui8.c[0];
		uni_ui16.ui16 = repeat;
		protocol[7] = uni_ui16.c[0];
		protocol[8] = uni_ui16.c[1];
		uni_ui8.ui8 = channel;
		protocol[9] = uni_ui8.c[0];
		uni_i16.i16 = er1;
		protocol[10] = uni_i16.c[0];
		protocol[11] = uni_i16.c[1];
		uni_i16.i16 = er2;
		protocol[12] = uni_i16.c[0];
		protocol[13] = uni_i16.c[1];
		uni_f.f = step;
		protocol[14] = uni_f.c[0];
		protocol[15] = uni_f.c[1];
		protocol[16] = uni_f.c[2];
		protocol[17] = uni_f.c[3];
		uni_ui16.ui16 = period;
		protocol[18] = uni_ui16.c[0];
		protocol[19] = uni_ui16.c[1];
		uni_ui16.ui16 = width;
		protocol[20] = uni_ui16.c[0];
		protocol[21] = uni_ui16.c[1];
		uni_f.f = bipotE;
		protocol[22] = uni_f.c[0];
		protocol[23] = uni_f.c[1];
		protocol[24] = uni_f.c[2];
		protocol[25] = uni_f.c[3];
		uni_ui8.ui8 = bipotMode;
		protocol[26] = uni_ui8.c[0];
		uni_ui8.ui8 = primeChannel;
		protocol[27] = uni_ui8.c[0];
		protocol[28] = STOP_BYTE;

		break;
	case SWV:
		protocol = malloc(31 * sizeof(char));
		uni_ui16.ui16 = 2002;
		protocol[1] = uni_ui16.c[0];
		protocol[2] = uni_ui16.c[1];
		uni_ui16.ui16 = qtime;
		protocol[3] = uni_ui16.c[0];
		protocol[4] = uni_ui16.c[1];
		uni_ui8.ui8 = cell;
		protocol[5] = uni_ui8.c[0];
		uni_ui8.ui8 = range;
		protocol[6] = uni_ui8.c[0];
		uni_ui16.ui16 = repeat;
		protocol[7] = uni_ui16.c[0];
		protocol[8] = uni_ui16.c[1];
		uni_ui8.ui8 = channel;
		protocol[9] = uni_ui8.c[0];
		uni_i16.i16 = er1;
		protocol[10] = uni_i16.c[0];
		protocol[11] = uni_i16.c[1];
		uni_i16.i16 = er2;
		protocol[12] = uni_i16.c[0];
		protocol[13] = uni_i16.c[1];
		uni_f.f = step;
		protocol[14] = uni_f.c[0];
		protocol[15] = uni_f.c[1];
		protocol[16] = uni_f.c[2];
		protocol[17] = uni_f.c[3];
		uni_ui16.ui16 = amplitude;
		protocol[18] = uni_ui16.c[0];
		protocol[19] = uni_ui16.c[1];
		uni_f.f = frequency;
		protocol[20] = uni_f.c[0];
		protocol[21] = uni_f.c[1];
		protocol[22] = uni_f.c[2];
		protocol[23] = uni_f.c[3];
		uni_f.f = bipotE;
		protocol[24] = uni_f.c[0];
		protocol[25] = uni_f.c[1];
		protocol[26] = uni_f.c[2];
		protocol[27] = uni_f.c[3];
		uni_ui8.ui8 = bipotMode;
		protocol[28] = uni_ui8.c[0];
		uni_ui8.ui8 = primeChannel;
		protocol[29] = uni_ui8.c[0];
		protocol[30] = STOP_BYTE;

		break;
	case AMP:
		protocol = malloc(27 * sizeof(char));
		uni_ui16.ui16 = 2006;
		protocol[1] = uni_ui16.c[0];
		protocol[2] = uni_ui16.c[1];
		uni_ui16.ui16 = qtime;
		protocol[3] = uni_ui16.c[0];
		protocol[4] = uni_ui16.c[1];
		uni_ui8.ui8 = cell;
		protocol[5] = uni_ui8.c[0];
		uni_ui8.ui8 = range;
		protocol[6] = uni_ui8.c[0];
		uni_ui16.ui16 = repeat;
		protocol[7] = uni_ui16.c[0];
		protocol[8] = uni_ui16.c[1];
		uni_ui8.ui8 = channel;
		protocol[9] = uni_ui8.c[0];
		uni_i16.i16 = er1;
		protocol[10] = uni_i16.c[0];
		protocol[11] = uni_i16.c[1];
		uni_f.f = dataRate;
		protocol[12] = uni_f.c[0];
		protocol[13] = uni_f.c[1];
		protocol[14] = uni_f.c[2];
		protocol[15] = uni_f.c[3];
		uni_ui32.ui32 = runTime;
		protocol[16] = uni_ui32.c[0];
		protocol[17] = uni_ui32.c[1];
		protocol[18] = uni_ui32.c[2];
		protocol[19] = uni_ui32.c[3];
		uni_f.f = bipotE;
		protocol[20] = uni_f.c[0];
		protocol[21] = uni_f.c[1];
		protocol[22] = uni_f.c[2];
		protocol[23] = uni_f.c[3];
		uni_ui8.ui8 = bipotMode;
		protocol[24] = uni_ui8.c[0];
		uni_ui8.ui8 = primeChannel;
		protocol[25] = uni_ui8.c[0];
		protocol[26] = STOP_BYTE;
		break;
	case CA:
		protocol = malloc(43 * sizeof(char));
		uni_ui16.ui16 = 2005;
		protocol[1] = uni_ui16.c[0];
		protocol[2] = uni_ui16.c[1];
		uni_ui8.ui8 = cell;
		protocol[3] = uni_ui8.c[0];
		uni_ui8.ui8 = range;
		protocol[4] = uni_ui8.c[0];
		uni_ui16.ui16 = repeat;
		protocol[5] = uni_ui16.c[0];
		protocol[6] = uni_ui16.c[1];
		uni_ui8.ui8 = channel;
		protocol[7] = uni_ui8.c[0];
		uni_i16.i16 = ei;
		protocol[8] = uni_i16.c[0];
		protocol[9] = uni_i16.c[1];
		uni_i16.i16 = er1;
		protocol[10] = uni_i16.c[0];
		protocol[11] = uni_i16.c[1];
		uni_i16.i16 = er2;
		protocol[12] = uni_i16.c[0];
		protocol[13] = uni_i16.c[1];
		uni_i16.i16 = ef;
		protocol[14] = uni_i16.c[0];
		protocol[15] = uni_i16.c[1];
		uni_f.f = dataRate;
		protocol[16] = uni_f.c[0];
		protocol[17] = uni_f.c[1];
		protocol[18] = uni_f.c[2];
		protocol[19] = uni_f.c[3];
		uni_ui32.ui32 = ti;
		protocol[20] = uni_ui32.c[0];
		protocol[21] = uni_ui32.c[1];
		protocol[22] = uni_ui32.c[2];
		protocol[23] = uni_ui32.c[3];
		uni_ui32.ui32 = t1;
		protocol[24] = uni_ui32.c[0];
		protocol[25] = uni_ui32.c[1];
		protocol[26] = uni_ui32.c[2];
		protocol[27] = uni_ui32.c[3];
		uni_ui32.ui32 = t2;
		protocol[28] = uni_ui32.c[0];
		protocol[29] = uni_ui32.c[1];
		protocol[30] = uni_ui32.c[2];
		protocol[31] = uni_ui32.c[3];
		uni_ui32.ui32 = tf;
		protocol[32] = uni_ui32.c[0];
		protocol[33] = uni_ui32.c[1];
		protocol[34] = uni_ui32.c[2];
		protocol[35] = uni_ui32.c[3];
		uni_f.f = bipotE;
		protocol[36] = uni_f.c[0];
		protocol[37] = uni_f.c[1];
		protocol[38] = uni_f.c[2];
		protocol[39] = uni_f.c[3];
		uni_ui8.ui8 = bipotMode;
		protocol[40] = uni_ui8.c[0];
		uni_ui8.ui8 = primeChannel;
		protocol[41] = uni_ui8.c[0];
		protocol[42] = STOP_BYTE;
		break;
	case EIS:
		protocol = malloc(35 * sizeof(char));
		uni_ui16.ui16 = 2007;
		protocol[1] = uni_ui16.c[0];
		protocol[2] = uni_ui16.c[1];
		uni_ui16.ui16 = qtime;
		protocol[3] = uni_ui16.c[0];
		protocol[4] = uni_ui16.c[1];
		uni_ui8.ui8 = cell;
		protocol[5] = uni_ui8.c[0];
		uni_ui8.ui8 = range;
		protocol[6] = uni_ui8.c[0];
		uni_ui16.ui16 = repeat;
		protocol[7] = uni_ui16.c[0];
		protocol[8] = uni_ui16.c[1];
		uni_ui8.ui8 = channel;
		protocol[9] = uni_ui8.c[0];
		uni_f.f = fi;
		protocol[10] = uni_f.c[0];
		protocol[11] = uni_f.c[1];
		protocol[12] = uni_f.c[2];
		protocol[13] = uni_f.c[3];
		uni_f.f = ff;
		protocol[14] = uni_f.c[0];
		protocol[15] = uni_f.c[1];
		protocol[16] = uni_f.c[2];
		protocol[17] = uni_f.c[3];
		uni_f.f = e1Eis;
		protocol[18] = uni_f.c[0];
		protocol[19] = uni_f.c[1];
		protocol[20] = uni_f.c[2];
		protocol[21] = uni_f.c[3];
		uni_ui32.ui32 = ts;
		protocol[22] = uni_ui32.c[0];
		protocol[23] = uni_ui32.c[1];
		protocol[24] = uni_ui32.c[2];
		protocol[25] = uni_ui32.c[3];
		uni_ui16.ui16 = nf;
		protocol[26] = uni_ui16.c[0];
		protocol[27] = uni_ui16.c[1];
		uni_f.f = bipotE;
		protocol[28] = uni_f.c[0];
		protocol[29] = uni_f.c[1];
		protocol[30] = uni_f.c[2];
		protocol[31] = uni_f.c[3];
		uni_ui8.ui8 = bipotMode;
		protocol[32] = uni_ui8.c[0];
		uni_ui8.ui8 = primeChannel;
		protocol[33] = uni_ui8.c[0];
		protocol[34] = STOP_BYTE;
		break;

	}
	protocol[0] = START_BYTE;
	return protocol;
}