/*
 * arrayFunctions.c
 *
 *  Created on: 12 Sep 2018
 *      Author: feynman
 */
#include "../headerfiles/arrayFunctions.h"

//Rotates an array to the right by 1 index and looses last point.
void rotateArrayOnce(int *arraypoint, int sizeOfArray)
{

	for(int i = sizeOfArray-1; i >= 0 ; i--){
		arraypoint[i] = arraypoint[i-1];
	}


}
//Rotates an array to the left by 1 index and looses last point.
void rotateArrayOnceBackwards(int *arraypoint, int sizeOfArray)
{
	for(int i = 0; i < sizeOfArray-1 ; i--){
		arraypoint[i] = arraypoint[i+1];
	}

}

//Inserts value in array on index 0 after rotate
void arrayInsert(int *pArray, int sizeOfArray, int *pInsertionValue) {
	rotateArrayOnce(pArray,sizeOfArray);
	pArray[0] = *pInsertionValue;

}

//Takes average of an array.
int arrayAverage(int *array, int sizeOfArray){
	int sum = 0;
	for (int i = 0; i < sizeOfArray; i++){
		sum += array[i];
	}
	int avg = sum/sizeOfArray;
	return avg;
}





