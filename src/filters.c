#include "../headerfiles/filters.h"
#include "../headerfiles/arrayFunctions.h"

// Feel free to change return statement and arguments
void lowPassFilter(int *unfilteredArray, int *filteredArray, int *pSignal)
{
	*pSignal = 2*filteredArray[0]-filteredArray[1]+((unfilteredArray[0]-2*unfilteredArray[6]+unfilteredArray[12])/32);
}

void highPassFilter(int *lowFilteredArray, int *highFilteredArray, int *pSignal)
{
	*pSignal = highFilteredArray[0]-lowFilteredArray[0]/32+lowFilteredArray[16]-lowFilteredArray[17]+(lowFilteredArray[32])/32;


}

void derivative(int *highpassFilteredArray, int *pSignal)
{
	*pSignal = (2*highpassFilteredArray[0]+highpassFilteredArray[1]-highpassFilteredArray[3]-2*highpassFilteredArray[4])/8;

}


void squaring(int value, int *pSignal)
{
	*pSignal = value*value;

}

int movingWindow(int *squaringFiltered)
{
	int temp = 0;
	int N = 30;
	for(int i = 0; i < N; i++) {
		temp = temp + (squaringFiltered[0+(N-(i+1))]/N);
	}

	return temp;
}

