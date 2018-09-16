#include "../headerfiles/qsr.h"
#include <stdio.h>
#include <stdlib.h>
#include <arrayFunctions.h>

void peakDetection(QRS_params *params)
{
	if (isThereAPeak(params->pArrayWithPeak) == 0) {return;}

	if (isItRPeak(params->pArrayWithPeak[1],params->THRESHOLD1) == 1) {
		rotateArrayOnce(params->pRRInterval, params->sizeOfRRInterval);
		params->pRRInterval[0] = params->RRIntervalCounter;
		params->RRIntervalCounter = 0;


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

int isItRPeak(int peak, int threshold1) {
	int result;
	if (peak > threshold1) {
		result = 1;
	} else {
		result = 0;
	}
	return result;
}

int calculateAverage2(int *pRRInterval, int threshold1) {
	int average2 = 0;
	int runUntil8 = 0;
	int arrayCounter = 0;
	while (runUntil8 != 8) {
		if (pRRInterval[arrayCounter] > threshold1) {
			average2 = average2 + pRRInterval[arrayCounter];
		}
	}

	average2 = average2/8;
	return average2;
}

int isRRIntervalBetweenLowAndHigh(int rrInterval, int average2) {
	int result;
	int low = 0.92*average2;
	int high = 1.16*average2;
	if (rrInterval > low && rrInterval < high) {
		result = 1;
	} else {
		result = 2;
	}

	return result;
}

int isRRIntervalLargerThanMiss(int rrInterval, int miss) {
	int result;
	if (rrInterval > miss) {
		result = 1;
	} else {
		result = 2;
	}
	return result;
}

int noicePeakDetected(int *threshold1, int *threshold2, int *NPKF, int *SPKF, int peak) {
	*threshold1 = NPKF + 0.25*(SPKF-NPKF);
	*threshold2 = 0.5*threshold1;
	*NPKF = 0.125*peak+0.875*NPKF;
}

