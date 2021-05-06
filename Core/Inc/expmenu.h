
#ifndef   EXPMENU_H
#define   EXPMENU_H

#include "main.h"
#include "button.h"
uint16_t * getExpImage();

uint8_t selectedParameter;
float v, scan, resolution, bipotE, step, dataRate, frequency, fi, ff , e1Eis ;
int16_t er1, er2, ei, ef;
uint16_t repeat, qtime, amplitude, period, width, nf;
uint8_t cell, channel, range, bipotMode, primeChannel;
uint32_t runTime, ti, t1, t2, tf, ts;
enum Method {CV, DPV, SWV, LSV, NPV, CA, AMP, EIS };
enum Method method;
void checkExperimentButtons();
void drawExperimentMenu(uint8_t mode);
#endif
