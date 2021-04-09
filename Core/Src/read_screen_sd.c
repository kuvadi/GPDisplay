/*
 * read_screen_sd.c
 *
 *  Created on: Apr 2, 2021
 *      Author: bbari
 */


#include "read_screen_sd.h"
#include "fatfs.h"
#include "fatfs_sd.h"
#include "expmenu.h"
#include "numpad.h"
FATFS fs;
FIL fil;
FRESULT fresult;

UINT br, bw;

FATFS *pfs;
DWORD fre_clust;
uint32_t total, free_space;


void sd_init(){
	 fresult = f_mount(&fs, "/", 1);
}
void read_exp_menu(uint8_t offset){
	uint16_t * fb = get_buffer();
	fresult = f_mount(&fs, "" ,0);
	fresult = f_open(&fil, "exp_menu.dat", FA_OPEN_ALWAYS | FA_READ);
	fresult = f_lseek(&fil, offset*128*2);
	f_read (&fil, fb, 128*160*2, &br);
	f_close(&fil);

}
void read_numpad(){
	uint16_t * fb = get_buffer();
	fresult = f_mount(&fs, "" ,0);
	fresult = f_open(&fil, "numpad.dat", FA_OPEN_ALWAYS | FA_READ);
	//fresult = f_lseek(&fil, offset*128*2);
	f_read (&fil, fb, 128*160*2, &br);
	f_close(&fil);
}

void read_plot(){
	uint16_t *fb = get_buffer();
	fresult = f_open(&fil, "plot.dat", FA_OPEN_ALWAYS | FA_READ);
	//fresult = f_lseek(&fil, offset*128*2);
	f_read(&fil, fb, 128 * 160 * 2, &br);
	f_close(&fil);
}

void writeFile(uint16_t *fb){
	fresult = f_open(&fil, "plot.dat", FA_CREATE_ALWAYS | FA_WRITE);
	fresult = f_write(&fil, fb, 160*128*2, &bw);
	f_close(&fil);
}

