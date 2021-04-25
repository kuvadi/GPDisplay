/*
 * read_screen_sd.c
 *
 *  Created on: Apr 2, 2021
 *      Author: bbari
 */


#include <read_sd.h>
#include "fatfs.h"
#include "fatfs_sd.h"
#include "expmenu.h"
#include "numpad.h"
FATFS fs;
FIL fil;
FRESULT fresult;
FILINFO fno;
UINT br, bw;


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
	fresult = f_mount(&fs, "", 0);
	fresult = f_open(&fil, "numpad.dat", FA_OPEN_ALWAYS | FA_READ);
	fresult = f_lseek(&fil, 0);
	f_read(&fil, fb, 128 * 40 * 2, &br);
	ILI9163_render1();
	fresult = f_lseek(&fil, BUFSIZE / 2);
	f_read(&fil, fb, 128 * 40 * 2, &br);
	ILI9163_render2();
	fresult = f_lseek(&fil, 2 * BUFSIZE / 2);
	f_read(&fil, fb, 128 * 40 * 2, &br);
	ILI9163_render3();
	fresult = f_lseek(&fil, 3 * BUFSIZE / 2);
	f_read(&fil, fb, 128 * 40 * 2, &br);
	ILI9163_render4();
	f_close(&fil);
}

void read_plot() {
	uint16_t *fb = get_buffer();
	fresult = f_open(&fil, "plot.dat", FA_OPEN_ALWAYS | FA_READ);
	fresult = f_lseek(&fil, 0);
	f_read(&fil, fb, 128 * 40 * 2, &br);
	ILI9163_render1();
	fresult = f_lseek(&fil, BUFSIZE/2);
	f_read(&fil, fb, 128 * 40 * 2, &br);
	ILI9163_render2();
	fresult = f_lseek(&fil, 2* BUFSIZE/2);
	f_read(&fil, fb, 128 * 40 * 2, &br);
	ILI9163_render3();
	fresult = f_lseek(&fil, 3* BUFSIZE/2);
	f_read(&fil, fb, 128 * 40 * 2, &br);
	ILI9163_render4();
	f_close(&fil);
}

void writeFile(uint16_t *fb){
	fresult = f_open(&fil, "plot.dat", FA_CREATE_ALWAYS | FA_WRITE);
	fresult = f_write(&fil, fb, 160*128*2, &bw);
	f_close(&fil);
}

void scan_sd (char* pat)
{
    DIR dir;
    UINT i;
    char *path = malloc(20*sizeof (char));
    sprintf (path, "%s",pat);
    uint8_t counter = 0;
    uint8_t fileCount = 0;
    fresult = f_opendir(&dir, path);                       /* Open the directory */
    if (fresult == FR_OK)
    {
        for (;;)
        {
            f_readdir(&dir, &fno);                   /* Read a directory item */
            if (fresult != FR_OK || fno.fname[0] == 0) break;  /* Break on error or end of dir */
            if (fno.fattrib & AM_DIR)     /* It is a directory */
			{
				if (!(strcmp("SYSTEM~1", fno.fname)))
					continue;

				i = strlen(path);
				sprintf(&path[i], "/%s", fno.fname);
				scan_sd(path); /* Enter the directory */

				path[i] = 0;
			} else { /* It is a file. */
				if (fno.fname[strlen(fno.fname) - 1] == 'e'
						&& fno.fname[strlen(fno.fname) - 2] == 'p'
						&& fno.fname[strlen(fno.fname) - 3] == 'g'
						&& fno.fname[strlen(fno.fname) - 4] == '.')
					counter++;
			}
		}
		fileCount = counter;
		counter = 0;
		//çirkin kod
		files = malloc(fileCount * sizeof(char*));
		fresult = f_opendir(&dir, path);
		for (;;) {
			f_readdir(&dir, &fno); /* Read a directory item */
			if (fresult != FR_OK || fno.fname[0] == 0)
				break; /* Break on error or end of dir */
			if (fno.fattrib & AM_DIR) /* It is a directory */
			{
				if (!(strcmp("SYSTEM~1", fno.fname)))
					continue;

				i = strlen(path);
				sprintf(&path[i], "/%s", fno.fname);

				path[i] = 0;
			} else { /* It is a file. */
				if (fno.fname[strlen(fno.fname) - 1] == 'e'
						&& fno.fname[strlen(fno.fname) - 2] == 'p'
						&& fno.fname[strlen(fno.fname) - 3] == 'g'
						&& fno.fname[strlen(fno.fname) - 4] == '.') {
					files[counter] = malloc(strlen(fno.fname) * sizeof(char));
					strcpy(files[counter], fno.fname);
					//file names will be assigned to a global char**

					counter++;
				}

			}
		}
		expFileCount = counter;

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

void read_config_file(){
	//kayıtlı protokoller
	//dosyaları numaralandırırken kullanılan enumerator
	//.
	//.
	//.
}

void write_config_file(){

}

void parse_experiment_file(char* filename){
	fresult = f_open(&fil, filename, FA_OPEN_ALWAYS | FA_READ);
	unsigned long fileSize = fil.fsize;
	char* file = malloc(fileSize);
	f_read(&fil, file, fileSize, &br);

	int recordCount;
	//count in a while with strtok using delimeter "\r\n"
	char* fileSplit = strtok(file, "\r\n");
	while(fileSplit != NULL){
		fileSplit = strtok(NULL, "\r\n");
		recordCount++;
	}
	recordCount = recordCount -12; // 12 line header
	expDataX = malloc(recordCount*sizeof(float));
	expDataY = malloc(recordCount*sizeof(float));
	//then read again the file to file
	f_read(&fil, file, fileSize, &br);


	fileSplit = strtok(file, "\r\n");
	while(fileSplit[1] != 'F'){
		fileSplit = strtok(NULL, "\r\n");
	}
	fileSplit = strtok(NULL, "\r\n");

	while (fileSplit != NULL) {
		char *xArray = malloc(10);
		char *yArray = malloc(10);
		int index = 2;
		while (fileSplit[index] != ' ') {
			xArray[index - 2] = fileSplit[index];
			index++;
		}
		xArray[index-2] = '\0';
		index++;

		int yIndex = 0;
		while (fileSplit[index] != '\r') {
			yArray[yIndex] = fileSplit[index];
			index++;
			yIndex++;
		}

		fileSplit = strtok(NULL, "\r\n");


		free(xArray);
		free(yArray);
	}
	free(file);
}

