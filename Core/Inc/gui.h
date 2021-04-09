
#ifndef   GUI_H
#define   GUI_H
#include "main.h"
#include "ili9163.h"
#include "XPT2046_touch.h"
#include "button.h"
#include "numpad.h"
#include "expmenu.h"



//COORDINATE VARS
uint16_t x, y;
int scrolling, position;
void GUI_drawGUI( UART_HandleTypeDef huart);
void GUI_init();


void renderGui();
void drawButton();
void drawStringSolar();

void drawPoint(float x, float y);

int isPressed(Button button);


#endif
