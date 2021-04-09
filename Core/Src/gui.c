#include "gui.h"

//BUTTONS
Button expButton1 = { 0 };

//BUTTONS

//BUTTON HANDLERS

// BUTTON HANDLERS

void GUI_init() {
	ILI9163_init(1);
	ILI9163_render();
	XPT2046_TouchGetCoordinates(&x, &y);
}

void EXTI15_10_IRQHandler(void) {
	ILI9163_drawPixel(x, y, GREEN);
	XPT2046_TouchGetCoordinates(&x, &y);
	scrolling = 0;
	while (!HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_11)) {
		uint16_t xLast, yLast;
		XPT2046_TouchGetCoordinates(&xLast, &yLast);

		if (HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_11)) {
			break;
		}
		scrolling = -(yLast - y - 20);
		//read_exp_menu(scrolling+position);
		drawExperimentMenu(1);
		ILI9163_render();

	}
	position = position + scrolling;
	if (position < 0) {
		position = 0;
	}
	if (position > 140)
		position = 140;
	switch (state) {
	case MAINMENU:
		checkMainButtons();
		break;
	case EXPMENU:

		//checkExperimentButtons();

		break;
	case PLOT:
		break;
	case NUMPAD:
		checkNumpadButtons();

		break;
	case PASTMENU:
		break;
	case ABOUT:
		break;

	}
	switch (state) {
	case MAINMENU:
		drawMainButtons();
		break;
	case EXPMENU:
		drawExperimentMenu(0);

		break;
	case PLOT:
		read_plot();
			break;
	case NUMPAD:
		position = 0;
		drawNumpad();

		break;
	case PASTMENU:
		drawGraph();
		break;
	case ABOUT:
		break;

	}

	ILI9163_render();
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_11);
}
void GUI_drawGUI(UART_HandleTypeDef huart) {

	// need to call for interrupts

}

void drawMainMenu() {

}

void drawExpMenu() {

}

void drawPoint(float x, float y) {

	dataCount++;
	expData[dataCount] = y;
	drawWholeGraph();

}

void drawWholeGraph() {
	//clear graph
	ILI9163_newFrame();
	float max = -999.0f, min = 999.0f;
	for (int i = 0; i < dataCount; i++) {
		if (expData[i] < min) {
			min = expData[i];
		}
		if (expData[i] > max) {
			max = expData[i];
		}
	}
	minY = min;
	maxY = max;
	for (int i = 2; i < dataCount - 3; i++) {
		float val = (expData[i - 2] + expData[i - 1] + expData[i]
				+ expData[i + 1] + expData[i + 2]) / 5;
		float nextVal = (expData[i - 1] + expData[i] + expData[i + 1]
				+ expData[i + 2] + expData[i + 3]) / 5;
		ILI9163_drawLine(i * 128 / dataCount, val * 128 / (maxY - minY),
				i * 128 / dataCount + 128 / dataCount,
				nextVal * 128 / (maxY - minY), BLACK);
	}
}

void drawGraph() {

	//test data
	float data[] = { 0.0056, 0.0103961, 0.02415, 0.03572, 0.04311, 0.052359,
			0.05763, 0.0609, 0.06253, 0.0624, 0.060879, 0.05807, 0.05404,
			0.0491, 0.0434, 0.0372472, 0.03007, 0.02333, 0.01689, 0.0103,
			0.0035, 0.06093, 0.062531, 0.06241, 0.0608, 0.05807, 0.0540,
			0.04917, 0.02704, 0.0372, 0.0306, 0.0237, 0.005624, 0.01031,
			0.02418, 0.0357, 0.0431, 0.052399, 0.0573, 0.0609, 0.062, 0.06242,
			0.0608, 0.05806, 0.0540, 0.049, 0.04347, 0.03724, 0.03062, 0.0237,
			0.0168, 0.0100, 0.0035, 0.0609, 0.062, 0.0624, 0.0608, 0.0580,
			0.0540, 0.0491, 0.0434, 0.0372, 0.0306, 0.0237, 0.0035, 0.06093,
			0.062531, 0.06241, 0.0608, 0.05807, 0.0540, 0.04917, 0.02704,
			0.0372, 0.0306, 0.0237, 0.005624, 0.01031, 0.02418, 0.0357, 0.0431,
			0.052399, 0.0573, 0.0609, 0.062, 0.06242, 0.0608, 0.05806, 0.0540,
			0.049, 0.04347, 0.03724, 0.03062, 0.0237, 0.0168, 0.0100, 0.0035,
			0.0609, 0.062, 0.0624, 0.0608, 0.0580, 0.0540, 0.0491, 0.0434,
			0.0372, 0.0306, 0.0237, 0.0035, 0.06093, 0.062531, 0.06241, 0.0608,
			0.05807, 0.0540, 0.04917, 0.02704, 0.0372, 0.0306, 0.0237, 0.005624,
			0.01031, 0.02418, 0.0357, 0.0431, 0.052399, 0.0573, 0.0609, 0.062,
			0.06242, 0.0608, 0.05806, 0.0540, 0.049, 0.04347, 0.03724, 0.03062,
			0.0237, 0.0168, 0.0100, 0.0035, 0.0609, 0.062, 0.0624, 0.0608,
			0.0580, 0.0540, 0.0491, 0.0434, 0.0372, 0.0306, 0.0237, 0.0035,
			0.06093, 0.062531, 0.06241, 0.0608, 0.05807, 0.0540, 0.04917,
			0.02704, 0.0372, 0.0306, 0.0237, 0.005624, 0.01031, 0.02418, 0.0357,
			0.0431, 0.052399, 0.0573, 0.0609, 0.062, 0.06242, 0.0608, 0.05806,
			0.0540, 0.049, 0.04347, 0.03724, 0.03062, 0.0237, 0.0168, 0.0100,
			0.0035, 0.0609, 0.062, 0.0624, 0.0608, 0.0580, 0.0540, 0.0491,
			0.0434, 0.0372, 0.0306, 0.0237, 0.0035, 0.06093, 0.062531, 0.06241,
			0.0608, 0.05807, 0.0540, 0.04917, 0.02704, 0.0372, 0.0306, 0.0237,
			0.005624, 0.01031, 0.02418, 0.0357, 0.0431, 0.052399, 0.0573,
			0.0609, 0.062, 0.06242, 0.0608, 0.05806, 0.0540, 0.049, 0.04347,
			0.03724, 0.03062, 0.0237, 0.0168, 0.0100, 0.0035, 0.0609, 0.062,
			0.0624, 0.0608, 0.0580, 0.0540, 0.0491, 0.0434, 0.0372, 0.0306,
			0.0237 };
	float max = 0.0f, min = 999.0f;
	for (int i = 0; i < 100; i++) {
		if (*(data + i) < min) {
			min = *(data + i);
		}
		if (*(data + i) > max) {
			max = *(data + i);
		}
	}
	uint16_t pixVal = 0;
	uint16_t nextVal = 0;
	for (int i = 0; i < 100; i++) {
		pixVal = *(data + i) * 128 / (max - min);
		nextVal = *(data + i + 1) * 128 / (max - min);
		if (pixVal <= nextVal)
			ILI9163_drawLine(i * 2, pixVal, (i + 1) * 2, nextVal, WHITE);
		else
			ILI9163_drawLine(i * 2, pixVal, (i + 1) * 2, nextVal, WHITE);
	}
}

int isPressed(Button button) {
	return (x > button.x1 && x < button.x2 && y - position > button.y1
			&& y - position < button.y2);
}

