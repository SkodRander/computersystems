#include "../headerfiles/filters.h"
#include "../headerfiles/arrayFunctions.h"

// Feel free to change return statement and arguments
int lowPassFilter(int *unfilteredArray, int *filteredArray)
{
	int tmp = 2*filteredArray[0]-filteredArray[1]+((unfilteredArray[0]-2*unfilteredArray[6]+unfilteredArray[12])/32);
	return tmp;
}

int highPassFilter(int *lowFilteredArray, int *highFilteredArray)
{
	int highTmp = highFilteredArray[0]-lowFilteredArray[0]/32+lowFilteredArray[16]-lowFilteredArray[17]+(lowFilteredArray[32])/32;
	return highTmp;

}

int derivative(int *highpassFilteredArray)
{
	int tmp = (2*highpassFilteredArray[0]+highpassFilteredArray[1]-highpassFilteredArray[3]-2*highpassFilteredArray[4])/8;
	return tmp;
}

int squaring(int *derivativeFiltered)
{
	int temp;
	temp = derivativeFiltered[0]*derivativeFiltered[0];
	return temp;
}

int movingWindow(int *squaringFiltered)
{
	int temp = 0;
	int N = 30;
	for(int i = 0; i < N; i++) {
		temp = temp + squaringFiltered[0+(N-(i+1))];
	}
	temp = temp/N;
	return temp;
}

