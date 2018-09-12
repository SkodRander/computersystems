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


