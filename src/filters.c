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

void derirative()
{

}

void squaring()
{

}

void movingWindow()
{

}

