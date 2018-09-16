/*
 * arrayFunctions.c
 *
 *  Created on: 12 Sep 2018
 *      Author: feynman
 */
#include "../headerfiles/arrayFunctions.h"


void rotateArrayOnce(int *arraypoint, int sizeOfArray)
{

	for(int i = sizeOfArray-1; i >= 0 ; i--){
		arraypoint[i] = arraypoint[i-1];
	}


}

int isThereAPeak(int *arrayWithPeak) {
	int result;
	if (arrayWithPeak[1] > arrayWithPeak[0] && arrayWithPeak[1] > arrayWithPeak[2]) {
		result = 1;
	} else {
		result = 0;
	}

	return result;


}


