/*
 * protocols.h
 *
 *  Created on: Apr 30, 2021
 *      Author: bbari
 */

#ifndef INC_PROTOCOLS_H_
#define INC_PROTOCOLS_H_


// This file actually part of our_definitions.h

/* Galvanoplot Communication Protocol
*  _____________________________________________________________
*  | Start Byte(1) | Method(2) | Body(variable) | Stop Byte(1) |
*  -------------------------------------------------------------
*/

#define START_BYTE  107
#define STOP_BYTE  100
#define VARIABLE_LENGTH -1

//PC to Device Methods
#define METHOD_ASK_ID       7
#define METHOD_STAND_BY     8
#define METHOD_BLINK        9
#define METHOD_CLOSE        10
#define METHOD_SELECT       11
#define METHOD_SET_LED      12
#define METHOD_STOP         100
#define METHOD_ASK_SPECS    101

#define METHOD_CV           2000    //Cyclic Voltammetry
#define METHOD_DPV          2001    //Differential Pulse Voltammetry
#define METHOD_SWV          2002    //Square Wave Voltammetry
#define METHOD_LSV          2003    //Linear Sweep Voltammetry
#define METHOD_NPV          2004    //Normal Pulse Voltammetry
#define METHOD_CA           2005    //Choronoamperometry
#define METHOD_AMP          2006    //Amperometric


//Device to PC Methods
#define METHOD_EXPERIMENT_END       1000
#define METHOD_VOLTAMMETRY          1001
#define METHOD_AMPEROMETRY          1002
#define METHOD_SEND_ID              1007
#define METHOD_SEND_SPECS           1101
#define METHOD_SEND_POPUP_MESSAGE   10000
#define METHOD_SEND_PROCESS         10001
#define METHOD_SEND_DEBUG_MESSAGE   10002

#endif /* INC_PROTOCOLS_H_ */
