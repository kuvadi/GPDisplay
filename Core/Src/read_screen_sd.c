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
FILINFO fno;
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

void Scan_SD (char* pat)
{
    DIR dir;
    UINT i;
    char *path = malloc(20*sizeof (char));
    sprintf (path, "%s",pat);
    uint8_t counter = 0;
    fresult = f_opendir(&dir, path);                       /* Open the directory */
    if (fresult == FR_OK)
    {
        for (;;)
        {
            f_readdir(&dir, &fno);                   /* Read a directory item */
            if (fresult != FR_OK || fno.fname[0] == 0) break;  /* Break on error or end of dir */
            if (fno.fattrib & AM_DIR)     /* It is a directory */
            {
            	if (!(strcmp ("SYSTEM~1", fno.fname))) continue;
            	char *buf = malloc(30*sizeof(char));
            	sprintf (buf, "Dir: %s\r\n", fno.fname);

            	free(buf);
                i = strlen(path);
                sprintf(&path[i], "/%s", fno.fname);
                Scan_SD(path);                     /* Enter the directory */

                path[i] = 0;
            }
            else
            {   /* It is a file. */
           	   char *buf = malloc(30*sizeof(char));
               sprintf(buf,"File: %s/%s\n", path, fno.fname);
               ILI9163_drawString(0, 10+counter*10, Font_7x10, GREEN,
               			buf);

               free(buf);
               counter++;
            }
        }
        f_closedir(&dir);
    }
    free(path);
}

void init_exp_file(char* name){
	char* filename = malloc(strlen(name)+4);
	//add .gpe extension to file
	strcpy(filename, name);
	filename[strlen(name)] = '.';
	filename[strlen(name)+1] = 'g';
	filename[strlen(name)+2] = 'p';
	filename[strlen(name)+3] = 'e';
	filename[strlen(name)+4] = '\0';
	fresult = f_open(&fil, filename, FA_CREATE_ALWAYS | FA_WRITE);

	//add header to experiment file
	char* buf = malloc(250); //235 character for header hardcoded!
	//may vary with experiment id
	sprintf(buf,"\tVendor\t\t:SolarBiotec\r\n\tDevice\t\t:GalvanoPlot\r\n\tVersion\t\t:3.0\r\n\r\n\tUser\t\t:Guest\r\n\tExported at\t:2020.12.24 - 16:11:01\r\n\r\n\tGalvanoplot ID\t:HDD\r\n\tExperiment ID\t:%s\r\n\tProtocol\t\t:6b6b000100c8007605023228001400010100000064\r\n\tFilter\t\t:0\r\n",filename);
	fresult = f_write(&fil, buf, strlen(buf), &bw);
}

void add_record_experiment(float x, float y) {
	//add record as formatted like in gpe files
	// data count\tx y\r\n
	char* buf = malloc(20);
	sprintf(buf,"%d\t%g %g\r\n", dataCount, x, y);
	fresult = f_write(&fil, buf, strlen(buf), &bw);
	//fresult = f_lseek(&fil, flastp);
	//fresult = f_write(&fil, &x, sizeof(x), &bw);
	//fresult = f_lseek(&fil, flastp + MAXDATACOUNT * 4);
	//fresult = f_write(&fil, &y, sizeof(y), &bw);
	flastp += 4;
}

void close_file(){
	f_close(&fil);
}

