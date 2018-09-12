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
	char path[] = "/home/feynman/workspace/assignmentcomp/Datafiles/";
	char *mode = "r";
	FILE *file = fopen(strcat(path, filename), mode); // Replace NULL with the actual file object
   	return file;
}
