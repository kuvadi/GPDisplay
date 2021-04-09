/*
 * XPT2046_touch.h
 *
 *  Created on: 20 sep. 2019 �.
 *      Author: Andriy Honcharenko
 */

#ifndef XPT2046_TOUCH_H_
#define XPT2046_TOUCH_H_

#include "main.h"
#include <stdbool.h>

/*** Redefine if necessary ***/

// Warning! Use SPI bus with < 2.5 Mbit speed, better ~650 Kbit to be save.

/**
 *
 *
 * HARDCODED!
 *
 *
 * */
#define XPT2046_SPI_PORT hspi1
extern SPI_HandleTypeDef XPT2046_SPI_PORT;



#define XPT2046_CS_Pin        GPIO_PIN_10
#define XPT2046_CS_GPIO_Port  GPIOE

#define XPT2046_IRQ_Pin		GPIO_PIN_11
#define XPT2046_IRQ_GPIO_Port GPIOE

// change depending on screen orientation
#define XPT2046_SCALE_X 128
#define XPT2046_SCALE_Y 160

/**
 *
 *
 * HARDCODED!
 *
 *
 * */

// to calibrate uncomment UART_Printf line in ili9341_touch.c
#define XPT2046_MIN_RAW_X 3400
#define XPT2046_MAX_RAW_X 29000
#define XPT2046_MIN_RAW_Y 3300
#define XPT2046_MAX_RAW_Y 30000

// call before initializing any SPI devices
bool XPT2046_TouchPressed();
bool XPT2046_TouchGetCoordinates(uint16_t* x, uint16_t* y);
bool XPT2046_TouchPressed();

#endif /* XPT2046_TOUCH_H_ */
