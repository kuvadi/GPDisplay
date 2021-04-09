/*
 * mainmenu.c
 *
 *  Created on: Apr 3, 2021
 *      Author: bbari
 */
#include "mainmenu.h"

void expHandler() {
	state = EXPMENU;

}
void expplotHandler() {
	state = PASTMENU;
}
void aboutHandler() {

}
Button exp = { 0, 128, 0, 50, "Experiment", 0x00f0, expHandler };
Button expplot =  {  0, 128, 50, 100, "Draw Plot", 0x00f0, expplotHandler };
Button about = {  0, 128, 100, 150, "About", 0x00f0, aboutHandler };



//BUTTON CONTROL
void checkMainButtons() {
	if (isPressed(exp)) {
		exp.btnHandler();
	} else if (isPressed(expplot)) {
		expplot.btnHandler();
	} else if (isPressed(about)) {
		about.btnHandler();
	}
}
void drawMainButtons() {
	 ILI9163_drawButton(&exp);
	 ILI9163_drawButton(&expplot);
	 ILI9163_drawButton(&about);
}

