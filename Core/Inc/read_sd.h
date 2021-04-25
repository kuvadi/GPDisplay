/*
 * read_screen_sd.h
 *
 *  Created on: Apr 2, 2021
 *      Author: bbari
 */

#ifndef INC_READ_SD_H_
#define INC_READ_SD_H_

#include "main.h"
#include "string.h"
#include "stdio.h"
#include "ff.h"

void read_exp_menu(uint8_t offset);
void read_numpad();
void read_plot();
void scan_sd (char* pat);
void init_exp_file(char* name);
void add_record_experiment(float x, float y);
void close_file();
void read_config_file();
void write_config_file();
void parse_experiment_file(char* filename);
#endif /* INC_READ_SCREEN_SD_H_ */
