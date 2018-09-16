#include "../headerfiles/filters.h"
#include "../headerfiles/arrayFunctions.h"

// Feel free to change return statement and arguments
int lowPassFilter(int *unfilteredArray, int *filteredArray)
{
	int tmp = 2*filteredArray[0]-filteredArray[1]+((unfilteredArray[0]-2*unfilteredArray[6]+unfilteredArray[12])/32);
	return tmp;
}

void highPassFilter()
{

}

int derirative(int *highpassFilteredArray)
{
	int tmp = (2*highpassFilteredArray[0]+highpassFilteredArray[1]-highpassFilteredArray[3]-2*highpassFilteredArray[4])/8;
	return tmp;
}

void squaring()
{

}

int movingWindow(int *squaringFiltered)
{
	int temp;
	int N = 30;
	for(int i = 0; i < N; i++) {
		squaringFiltered[0+(N-(i+1))];
	}
	temp = temp/N;
	return temp;
}

