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

void arrayInsert(int *pArray, int sizeOfArray, int *pInsertionValue) {
	rotateArrayOnce(pArray,sizeOfArray);
	pArray[0] = pInsertionValue;

}

int arrayAverage(int array, sizeOfArray){
	int sum = 0;
	for (int i = 0; i < sizeOfArray; i++){
		sum +=array[i];
	}
	int avg = sum/sizeOfArray;
	return avg;
}





