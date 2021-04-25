#include "gui.h"

//BUTTONS
Button expButton1 = { 0 };

//BUTTONS

//BUTTON HANDLERS

// BUTTON HANDLERS

void GUI_init() {
	ILI9163_init(1);
	XPT2046_TouchGetCoordinates(&x, &y);
}

void EXTI15_10_IRQHandler(void) {
	ILI9163_drawPixel(x, y, GREEN);
	XPT2046_TouchGetCoordinates(&x, &y);
	scrolling = 0;
	uint8_t scrolled = 0;
	int counter = 0;
	while (!HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_11) && state == EXPMENU) {
		uint16_t xLast, yLast;
		XPT2046_TouchGetCoordinates(&xLast, &yLast);
		XPT2046_TouchGetCoordinates(&xLast, &yLast);
		// Check if scrolling

		if (HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_11)) {
			break;
		}
		scrolled = 1;

		scrolling = -(yLast - y );
		if(scrolling+position > 160){
			scrolling = 160-position;
		}
		else if(scrolling+position < 0){
			scrolling = -position;
		}

		//read_exp_menu(scrolling+position);
		drawExperimentMenu(1);
		ILI9163_drawRect(0, ((scrolling+position)*140)/160, 4, (((scrolling+position)*140)/160)+20, 3, GREEN); // scroll bar


		counter++;

	}
	position = position + scrolling;
	if (position < 0) {
		position = 0;
	}
	if (position > 160)
		position = 160;
	if(scrolled == 1 && scrolling > 5) //yanlış mantık eğer scroll edip aynı pozisyona gelirse buton çalışır
		return;
	switch (state) {
	case MAINMENU:
		checkMainButtons();
		break;
	case EXPMENU:

		checkExperimentButtons();

		break;
	case PLOT:
		checkPlotButtons();


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
		ILI9163_drawRect(0, ((position)*140)/160, 4, (((position)*140)/160)+20, 3, GREEN); // scroll bar
		break;
	case PLOT:
		drawPlot();
		break;
	case NUMPAD:
		position = 0;
		if(	oldState != NUMPAD)
			read_numpad();
		drawNumpad();

		break;
	case PASTMENU:
		break;
	case ABOUT:

		break;

	}

	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_11);
}
void GUI_drawGUI(UART_HandleTypeDef huart) {

	// need to call for interrupts
	/*
	if (X > 50.0)
		return;
	float y = (float) ((rand() % 1000)/2 );
	X = X + 1.0;
	exp_isr(X, y);
	ILI9163_render();
	 * */

}

void drawMainMenu() {

}

void drawExpMenu() {

}


int isPressed(Button button) {
	return (x > button.x1 && x < button.x2 && y + position > button.y1
			&& y + position < button.y2);
}

