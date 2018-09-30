#include "../headerfiles/sensor.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int getNextData(FILE *file, int* eofChecker)
{
	int value;
	*eofChecker = fscanf(file,"%i",&value);
   	return value; // return sensor value


}

FILE* openfile(const char* filename)
{
	char path[] = "Datafiles/";
	char *mode = "r";
	char* filenameConc = strcat(path,filename);
	FILE *file = fopen(filenameConc, mode); // Replace NULL with the actual file object
   	return file;
}
