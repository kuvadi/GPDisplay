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
#include "comm.h"

FATFS fs;
FIL fil;
FRESULT fresult;
FILINFO fno;
UINT br, bw;

DWORD fre_clust;
uint32_t total, free_space;

void sd_init() {
	fresult = f_mount(&fs, "/", 1);
}
void read_exp_menu(uint8_t offset) {
	uint16_t *fb = get_buffer();
	fresult = f_mount(&fs, "", 0);
	fresult = f_open(&fil, "exp_menu.dat", FA_OPEN_ALWAYS | FA_READ);
	fresult = f_lseek(&fil, offset * 128 * 2);
	f_read(&fil, fb, 128 * 160 * 2, &br);
	f_close(&fil);

}
void read_numpad() {
	uint16_t *fb = get_buffer();
	fresult = f_mount(&fs, "", 0);
	fresult = f_open(&fil, "numpad.dat", FA_OPEN_ALWAYS | FA_READ);
	fresult = f_lseek(&fil, 0);
	f_read(&fil, fb, 128 * 160 * 2, &br);
	ILI9163_render();

	f_close(&fil);
}

void read_plot() {
	uint16_t *fb = get_buffer();
	fresult = f_open(&fil, "plot.dat", FA_OPEN_ALWAYS | FA_READ);
	fresult = f_lseek(&fil, 0);
	f_read(&fil, fb, 128 * 160 * 2, &br);
	ILI9163_render();
	f_close(&fil);
}

void writeFile(uint16_t *fb) {
	fresult = f_open(&fil, "plot.dat", FA_CREATE_ALWAYS | FA_WRITE);
	fresult = f_write(&fil, fb, 160 * 128 * 2, &bw);
	f_close(&fil);
}

void scan_sd(char *pat) {
	DIR dir;
	UINT i;
	char *path = malloc(20 * sizeof(char));
	sprintf(path, "%s", pat);
	uint8_t counter = 0;
	uint8_t fileCount = 0;
	fresult = f_opendir(&dir, path); /* Open the directory */
	if (fresult == FR_OK) {
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

void init_exp_file(char *name) {
	char *filename = malloc(strlen(name) + 3);
	//add .gpe extension to file
	strcpy(filename, name);
	filename[strlen(name)] = '.';
	filename[strlen(name) + 1] = 'g';
	filename[strlen(name) + 2] = 'p';
	filename[strlen(name) + 3] = 'e';
	filename[strlen(name) + 4] = '\0';
	fresult = f_open(&fil, filename, FA_CREATE_ALWAYS | FA_WRITE);

	//add header to experiment file
	char *buf = malloc(250); //235 character for header hardcoded!
	//may vary with experiment id
	uint8_t len = 0;
	switch(method){
	case CV:
		len=31;
		break;
	case LSV:
		len = 29;
		break;
	case DPV :
		len = 31;
		break;
	case NPV:
		len = 29;
		break;
	case SWV:
		len = 31;
		break;
	case AMP:
		len = 27;
		break;
	case CA:
		len = 43;
		break;
	case EIS:
		len = 35;
		break;
	}
	char *protocol = formProtocol();
	char *output = malloc(100);
	int loop = 0;
	for (int i = 0; i < len; ++i) {
		sprintf((char*) (output + loop), "%02X", protocol[i]);
		loop+=2;
	}


	//insert NULL at the end of the output string
	output[loop++] = '\0';
	sprintf(buf,
			"\tVendor\t\t:SolarBiotec\r\n\tDevice\t\t:GalvanoPlot\r\n\tVersion\t\t:3.0\r\n\r\n\tUser\t\t:Guest\r\n\tExported at\t:2020.12.24 - 16:11:01\r\n\r\n\tGalvanoplot ID\t:HDD\r\n\tExperiment ID\t:%s\r\n\tProtocol\t\t:%s\r\n\tFilter\t\t:0\r\nVoltage_Domain_ch1_DATA\r\n",
			filename, output);
	fresult = f_write(&fil, buf, strlen(buf), &bw);
	free(output);
	free(protocol);
}

void add_record_experiment(float x, float y) {
	//add record as formatted like in gpe files
	// data count\tx y\r\n
	char *buffer = malloc(20*sizeof(char));
	sprintf(buffer, "%d\t%g %g\r\n", dataCount, x, y);
	fresult = f_write(&fil, buffer, strlen(buffer), &bw);
	//fresult = f_lseek(&fil, flastp);
	//fresult = f_write(&fil, &x, sizeof(x), &bw);
	//fresult = f_lseek(&fil, flastp + MAXDATACOUNT * 4);
	//fresult = f_write(&fil, &y, sizeof(y), &bw);
	flastp += 4;
	free(buffer);
}

void close_file() {
	f_close(&fil);
}

void read_config_file() {
	//kayıtlı protokoller
	//dosyaları numaralandırırken kullanılan enumerator
	//.
	//.
	//.
}

void write_config_file() {

}

void parse_experiment_file(char *filename) {
	fresult = f_open(&fil, filename, FA_OPEN_ALWAYS | FA_READ);
	unsigned long fileSize = fil.fsize;
	char *file = malloc(fileSize);
	f_read(&fil, file, fileSize, &br);
	/*
	 * plotted graph will be time domain or voltage domain
	 * it will be determined by the method type
	 * method type is embedded in protocol string*/
	int recordCount = 0;
	//count in a while with strtok using delimeter "\r\n"
	char *fileSplit = strtok(file, "\r\n");
	while (fileSplit != NULL) {
		fileSplit = strtok(NULL, "\r\n");
		recordCount++;
	}
	recordCount = recordCount - 14; // 10 line header 4 lines data def
	recordCount = recordCount / 4; // 2 channel 2 domain
	dataCount = recordCount;
	expDataXch1 = malloc(recordCount * sizeof(float));
	expDataYch1 = malloc(recordCount * sizeof(float));
	expDataXch2 = malloc(recordCount * sizeof(float));
	expDataYch2 = malloc(recordCount * sizeof(float));
	//then read again the file to file
	f_close(&fil);
	fresult = f_open(&fil, filename, FA_OPEN_ALWAYS | FA_READ);
	fresult = f_read(&fil, file, fileSize, &br);

	fileSplit = strtok(file, "\r\n");
	while (fileSplit[1] != 'P') {
		fileSplit = strtok(NULL, "\r\n");
	}
	int voltageOrTime = decodeMethod(fileSplit);
	fileSplit = strtok(NULL, "\r\n");
	fileSplit = strtok(NULL, "\r\n");
	//Voltage domain channel 1
	fileSplit = strtok(NULL, "\r\n"); //skipping datadef

	int pointerArrayCounter = 0;
	while (fileSplit[0] != 'V') {
		char *xArray = malloc(10);
		char *yArray = malloc(10);
		int index = 0;
		while (1) {
			if (fileSplit[index] == ' ' || fileSplit[index] == '\t')
				break;
			index++;
		}
		index++;
		while (1) {
			if (fileSplit[index] == ' ' || fileSplit[index] == '\t')
				break;
			xArray[index - 2] = fileSplit[index];
			index++;
		}
		xArray[index - 2] = '\0';
		if (!voltageOrTime)
			expDataXch1[pointerArrayCounter] = atof(xArray); // converting and assigning float value to array
		index++;

		int yIndex = 0;
		while (fileSplit[index] != '\0') {
			yArray[yIndex] = fileSplit[index];
			index++;
			yIndex++;
		}
		if (!voltageOrTime)
			expDataYch1[pointerArrayCounter] = atof(yArray); // converting and assigning float value to array

		fileSplit = strtok(NULL, "\r\n");

		free(xArray);
		free(yArray);
		pointerArrayCounter++;
	}
	//Voltage domain channel 2
	fileSplit = strtok(NULL, "\r\n"); //skipping datadef
	pointerArrayCounter = 0;
	while (fileSplit[0] != 'T') {
		char *xArray = malloc(10);
		char *yArray = malloc(10);
		int index = 0;
		while (1) {
			if (fileSplit[index] == ' ' || fileSplit[index] == '\t')
				break;
			index++;
		}
		index++;
		while (1) {
			if (fileSplit[index] == ' ' || fileSplit[index] == '\t')
				break;
			xArray[index - 2] = fileSplit[index];
			index++;
		}
		xArray[index - 2] = '\0';
		if (!voltageOrTime)
			expDataXch2[pointerArrayCounter] = atof(xArray); // converting and assigning float value to array

		index++;

		int yIndex = 0;
		while (fileSplit[index] != '\0') {
			yArray[yIndex] = fileSplit[index];
			index++;
			yIndex++;
		}
		if (!voltageOrTime)
			expDataYch2[pointerArrayCounter] = atof(yArray); // converting and assigning float value to array

		fileSplit = strtok(NULL, "\r\n");

		free(xArray);
		free(yArray);
		pointerArrayCounter++;
	}
	//Time domain channel 1
	fileSplit = strtok(NULL, "\r\n"); //skipping datadef
	pointerArrayCounter = 0;

	while (fileSplit[0] != 'T') {
		char *xArray = malloc(10);
		char *yArray = malloc(10);
		int index = 0;
		while (1) {
			if (fileSplit[index] == ' ' || fileSplit[index] == '\t')
				break;
			index++;
		}
		index++;
		while (1) {
			if (fileSplit[index] == ' ' || fileSplit[index] == '\t')
				break;
			xArray[index - 2] = fileSplit[index];
			index++;
		}
		xArray[index - 2] = '\0';
		index++;
		if (voltageOrTime)
			expDataXch1[pointerArrayCounter] = atof(xArray); // converting and assigning float value to array

		int yIndex = 0;
		while (fileSplit[index] != '\0') {
			yArray[yIndex] = fileSplit[index];
			index++;
			yIndex++;
		}
		if (voltageOrTime)
			expDataYch1[pointerArrayCounter] = atof(yArray);
		fileSplit = strtok(NULL, "\r\n");

		free(xArray);
		free(yArray);
	}
	drawWholeGraph();
	//Time domain channel 2
	fileSplit = strtok(NULL, "\r\n"); //skipping datadef
	pointerArrayCounter = 0;

	int dummyCounter = recordCount;
	while (dummyCounter != 0) {
		char *xArray = malloc(10);
		char *yArray = malloc(10);
		int index = 0;
		while (1) {
			if (fileSplit[index] == ' ' || fileSplit[index] == '\t')
				break;
			index++;
		}
		index++;
		while (1) {
			if (fileSplit[index] == ' ' || fileSplit[index] == '\t')
				break;
			xArray[index - 2] = fileSplit[index];
			index++;
		}
		xArray[index - 2] = '\0';
		index++;
		if (!voltageOrTime)
			expDataXch2[pointerArrayCounter] = atof(xArray);

		int yIndex = 0;
		while (fileSplit[index] != '\0') {
			yArray[yIndex] = fileSplit[index];
			index++;
			yIndex++;
		}
		if (voltageOrTime)
			expDataYch2[pointerArrayCounter] = atof(yArray);
		fileSplit = strtok(NULL, "\r\n");

		free(xArray);
		free(yArray);
		dummyCounter--;
	}

	free(file);

}

int decodeMethod(char *protocol) {
	char hex[4];
	hex[0] = protocol[16];
	hex[1] = protocol[17];
	hex[2] = protocol[14];
	hex[3] = protocol[15];
	int method = (int) strtol(hex, NULL, 16);
	int a;
	switch (method) {
	case METHOD_CV: //voltage domain
		return 0;
		break;
	case METHOD_DPV: //voltage domain
		return 0;
		break;
	case METHOD_SWV: //voltage domain
		return 0;
		break;
	case METHOD_LSV: //voltage domain
		return 0;
		break;
	case METHOD_NPV: //voltage domain
		return 0;
		break;
	case METHOD_CA: //time domain
		return 1;
		break;
	case METHOD_AMP: //time domain
		return 1;
		break;
	}
}

