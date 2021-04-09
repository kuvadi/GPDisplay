
#ifndef   BUTTON_H
#define   BUTTON_H
#include "main.h"
typedef void (*ButtonHandler)(void);
typedef struct Button {
	uint8_t x1;
	uint8_t x2;
	uint8_t y1;
	uint8_t y2;
	char* _string;
	uint16_t color;
	ButtonHandler btnHandler;
} Button;



#endif
