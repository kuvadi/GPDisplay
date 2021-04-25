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
	state = PLOT;
}
void aboutHandler() {
	state = ABOUT;
}

void expButtonHandler(int i ){
	//open ith file and plot
}
void pastHandler() {
	//öncelikle sd card scan edilmeli
	//init fonksiyonuna scan sd bölümünü ekle ve ekrana bastırmayı sil
	//ekranı temizlemeyi unutma
	expFileButtons = malloc(expFileCount* sizeof(Button*));
	for(int i = 0; i < expFileCount; ++i) {
		expFileButtons[i] = malloc(sizeof(Button));
		Button exp = { 0, 128, 0, 40+ i*40, files[i], 0x00f0, expButtonHandler };
		expFileButtons[i] = &exp;
		ILI9163_drawButton(&exp);
	}
}
Button exp = { 0, 128, 0, 40, "Experiment", 0x00f0, expHandler };
Button expplot =  {  0, 128, 40, 80, "Draw Plot", 0x00f0, expplotHandler };
Button past = {  0, 128, 80, 120, "Past Experiments", 0x00f0, pastHandler };
Button about = {  0, 128, 120, 160, "About", 0x00f0, aboutHandler };



//BUTTON CONTROL
void checkMainButtons() {
	if (isPressed(exp)) {
		exp.btnHandler();
	} else if (isPressed(expplot)) {
		expplot.btnHandler();
	} else if (isPressed(about)) {
		about.btnHandler();
	}
	else if (isPressed(past)) {
		past.btnHandler();
		}
}
void drawMainButtons() {
	 ILI9163_drawButton(&exp);
	 ILI9163_drawButton(&expplot);
	 ILI9163_drawButton(&past);
	 ILI9163_drawButton(&about);
}

