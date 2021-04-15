#include "numpad.h"

void oneHandler() {
	if (isFloat) {
		number += 1.0 * pow(10.0, --fractionCount);

	} else {
		number = number * 10.0 + 1.0;
	}
	digitNumber++;

	oldState = NUMPAD;

}
void twoHandler() {
	if (isFloat) {
		number += 2.0 * pow(10.0, --fractionCount);

	} else {
		number = number * 10.0 + 2.0;
	}
	digitNumber++;

	oldState = NUMPAD;
}
void threeHandler() {
	if (isFloat) {
		number += 3.0 * pow(10.0, --fractionCount);

	} else {
		number = number * 10.0 + 3.0;
	}
	digitNumber++;

	oldState = NUMPAD;
}
void fourHandler() {
	if (isFloat) {
		number += 4.0 * pow(10.0, --fractionCount);

	} else {
		number = number * 10.0 + 4.0;
	}
	digitNumber++;

	oldState = NUMPAD;
}
void fiveHandler() {
	if (isFloat) {
		number += 5.0 * pow(10.0, --fractionCount);

	} else {
		number = number * 10.0 + 5.0;
	}
	digitNumber++;

	oldState = NUMPAD;
}
void sixHandler() {
	if (isFloat) {
		number += 6.0 * pow(10.0, --fractionCount);

	} else {
		number = number * 10.0 + 6.0;
	}
	digitNumber++;

	oldState = NUMPAD;
}
void sevenHandler() {
	if (isFloat) {
		number += 7.0 * pow(10.0, --fractionCount);

	} else {
		number = number * 10.0 + 7.0;
	}
	digitNumber++;

	oldState = NUMPAD;
}
void eightHandler() {
	if (isFloat) {
		number += 8.0 * pow(10.0, --fractionCount);

	} else {
		number = number * 10.0 + 8.0;
	}
	digitNumber++;

	oldState = NUMPAD;
}
void nineHandler() {
	if (isFloat) {
		number += 9.0 * pow(10.0, --fractionCount);

	} else {
		number = number * 10.0 + 9.0;
	}
	digitNumber++;

	oldState = NUMPAD;
}
void dotHandler() {
	if(isFloat ==0){
		isFloat = 1;
	}

	oldState = NUMPAD;
}
void zeroHandler() {
	if (number != 0.0) {
		if (isFloat) {
			fractionCount--;
		}
		else{
			number = number * 10.0;
		}

		digitNumber++;
	}

	oldState = NUMPAD;
}
void enterHandler() {
	number = 0;
	digitNumber = 0;
	isFloat = 0;
	fractionCount = 0;
	state = EXPMENU;
}
void removeHandler() {
	if (isFloat) {// problem
		int removedDigit = (int)(number * pow(10, -fractionCount)) % 10;
		number = number - removedDigit * pow(10, fractionCount);
		fractionCount++;
	}
	else{
		int removedDigit = (int) number % 10;
		number = number / 10.0;
		number = number - (0.1 * removedDigit);
	}

	digitNumber--;
	if (fractionCount == 0) {
		isFloat = 0;
	}
	if (fractionCount == 0 && digitNumber == 0) {
		number = 0.0;
	}
	oldState = NUMPAD;
}
//NUMPAD BUTTONS
Button oneButton = { 0, 42, 29, 61, "", 0x00f0, oneHandler };
Button twoButton = { 43, 85, 29, 61, "", 0x00f0, twoHandler };
Button threeButton = { 85, 128, 29, 61, "", 0x00f0, threeHandler };

Button fourButton = { 0, 42, 62, 94, "", 0x00f0, fourHandler };
Button fiveButton = { 43, 85, 62, 94, "", 0x00f0, fiveHandler };
Button sixButton = { 85, 128, 62, 94, "", 0x00f0, sixHandler };

Button sevenButton = { 0, 42, 95, 127, "", 0x00f0, sevenHandler };
Button eightButton = { 43, 85, 95, 127, "", 0x00f0, eightHandler };
Button nineButton = { 85, 128, 95, 127, "", 0x00f0, nineHandler };

Button dotButton = { 0, 42, 128, 160, "", 0x00f0, dotHandler };
Button zeroButton = { 43, 85, 128, 160, "", 0x00f0, zeroHandler };
Button enterButton = { 85, 128, 128, 160, "", 0x00f0, enterHandler };

Button removeButton = { 99, 121, 6, 27, "", 0x00f0, removeHandler };


//BUTTON CONTROL
void checkNumpadButtons() {
	if (isPressed(oneButton)) {
		oneButton.btnHandler();
	} else if (isPressed(twoButton)) {
		twoButton.btnHandler();
	} else if (isPressed(threeButton)) {
		threeButton.btnHandler();
	} else if (isPressed(fourButton)) {
		fourButton.btnHandler();
	} else if (isPressed(fiveButton)) {
		fiveButton.btnHandler();
	} else if (isPressed(sixButton)) {
		sixButton.btnHandler();
	} else if (isPressed(sevenButton)) {
		sevenButton.btnHandler();
	} else if (isPressed(eightButton)) {
		eightButton.btnHandler();
	} else if (isPressed(nineButton)) {
		nineButton.btnHandler();
	} else if (isPressed(dotButton)) {
		dotButton.btnHandler();
	} else if (isPressed(zeroButton)) {
		zeroButton.btnHandler();
	} else if (isPressed(enterButton)) {
		enterButton.btnHandler();
	}else if (isPressed(removeButton)) {
		removeButton.btnHandler();
		}
}
void drawNumpad() {

	char numberString[20];

	char *tmpSign = (number < 0) ? "-" : "";
	float tmpVal = (number < 0) ? -number : number;

	int tmpInt1 = tmpVal;                  // Get the integer (678).
	double tmpFrac = tmpVal - tmpInt1;      // Get fraction (0.0123).
	int tmpInt2 = trunc(tmpFrac * 10000);  // Turn into integer (123).

	// Print as parts, note that you need 0-padding for fractional bit.

	sprintf(numberString, "%g", number);
	ILI9163_fillRect(19, 5,92, 27, WHITE);
	ILI9163_drawButton(&removeButton);
	ILI9163_drawString(80 - digitNumber * 7, 10, Font_7x10, GREEN,
			numberString);
	switch (selectedParameter) {
	case 1:
		ILI9163_drawString(20, 10, Font_7x10, GREEN, "Range");
		break;
	case 2:
		ILI9163_drawString(20, 10, Font_7x10, GREEN, "Ei");
		break;
	case 3:
		ILI9163_drawString(20, 10, Font_7x10, GREEN, "E1");
		break;
	case 4:
		ILI9163_drawString(20, 10, Font_7x10, GREEN, "E2");
		break;
	case 5:
		ILI9163_drawString(20, 10, Font_7x10, GREEN, "V");
		break;
	}
}

