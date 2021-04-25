
#ifndef   EXPMENU_H
#define   EXPMENU_H

#include "main.h"
#include "button.h"
uint16_t * getExpImage();

uint8_t selectedParameter;
float range, ei, er1, er2, v, scan, resolution, qtime;
uint8_t cell, channel;
enum Method {CYC, DPV, SWV, LSV, NPV, CHR, AMP };
enum Method method;
void checkExperimentButtons();
void drawExperimentMenu(uint8_t mode);
#endif
