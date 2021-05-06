/*
 * plot.c
 *
 *  Created on: Apr 12, 2021
 *      Author: bbari
 */

#include "plot.h"

void plotBackHandler(){
	state = MAINMENU;
	dataCount = 0;
	X = -49.0;
}

void experimentsBHandler(){

}
void newExpHandler(){

}
void startHandler(){

}

Button plotBackButton ={ 0, 40, 0, 30, "", 0x00f0, plotBackHandler };
Button experimentsButton = { 43, 85, 29, 61, "", 0x00f0, experimentsBHandler};
Button newExpButton = { 85, 128, 29, 61, "", 0x00f0, newExpHandler };
Button startExpButton = {85, 128, 29, 61, "", 0x00f0, startHandler };

void checkPlotButtons() {
	if (isPressed(plotBackButton)) {
		plotBackButton.btnHandler();
	}

}

void drawPlot() {
	if (oldState != PLOT) {
		exp_init();
		oldState = PLOT;
	}
	read_plot();

}

void drawPoint(float x, float y) {

	dataCount++;
	expDataYch1[dataCount] = y;

	clearGraphArea();

	drawWholeGraph();
	char numberString[6];
	char *tmpSign = (maxY < 0) ? "-" : "";
	float tmpVal = (maxY < 0) ? -maxY : maxY;

	int tmpInt1 = tmpVal;                  // Get the integer (678).
	float tmpFrac = tmpVal - tmpInt1;      // Get fraction (0.0123).
	int tmpInt2 = trunc(tmpFrac * 10);  // Turn into integer (123).
	sprintf(numberString, "%s%d.%d", tmpSign, tmpInt1, tmpInt2);
	ILI9163_drawString(0, 40, Font_7x10, BLACK, numberString);
	ILI9163_drawLine(0, 35, 128, 35, BLACK);
	tmpSign = (minY < 0) ? "-" : "";
	tmpVal = (minY < 0) ? -minY : minY;

	tmpInt1 = tmpVal;                  // Get the integer (678).
	tmpFrac = tmpVal - tmpInt1;      // Get fraction (0.0123).
	tmpInt2 = trunc(tmpFrac * 10);  // Turn into integer (123).
	sprintf(numberString, "%s%d.%d", tmpSign, tmpInt1, tmpInt2);
	ILI9163_drawString(0, 100, Font_7x10, BLACK, numberString);
	ILI9163_drawLine(0, 115, 128, 115, BLACK);

	ILI9163_drawString(20, 120, Font_7x10, BLACK, "1.4");

	ILI9163_drawString(100, 120, Font_7x10, BLACK, "1.5");

}

void clearGraphArea(){
	ILI9163_fillRect(0, 27,128, 114, WHITE);
}
void drawWholeGraph() {
	//clear graph
	//ILI9163_newFrame();
	float max = -999.0f, min = 999.0f;
	for (int i = 2; i < dataCount-2; i++) {
		if ((expDataYch1[i - 2] + expDataYch1[i - 1] + expDataYch1[i] + expDataYch1[i + 1]
				+ expDataYch1[i + 2]) / 5 < min) {
			min = (expDataYch1[i - 2] + expDataYch1[i - 1] + expDataYch1[i] + expDataYch1[i + 1]
					+ expDataYch1[i + 2]) / 5;
			;
		}
		if ((expDataYch1[i - 2] + expDataYch1[i - 1] + expDataYch1[i] + expDataYch1[i + 1]
				+ expDataYch1[i + 2]) / 5 > max) {
			max = (expDataYch1[i - 2] + expDataYch1[i - 1] + expDataYch1[i] + expDataYch1[i + 1]
					+ expDataYch1[i + 2]) / 5;
		}
	}
	minY = min;
	maxY = max;
	for (int i = 2; i < dataCount - 3; i++) {
		float val = (expDataYch1[i - 2] + expDataYch1[i - 1] + expDataYch1[i]
				+ expDataYch1[i + 1] + expDataYch1[i + 2]) / 5;
		float nextVal = (expDataYch1[i - 1] + expDataYch1[i] + expDataYch1[i + 1]
				+ expDataYch1[i + 2] + expDataYch1[i + 3]) / 5;
		ILI9163_drawLine((i * 128 / dataCount),
				32 + 80 - ((val-minY) * 80 / (maxY - minY)),
				(i * 128 / dataCount + 128 / dataCount),
				32 + 80 - ((nextVal- minY) * 80 / (maxY - minY)),
				ORANGE);
	}
}
