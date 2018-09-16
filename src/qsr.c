#include "../headerfiles/qsr.h"
#include <stdio.h>
#include <stdlib.h>
#include <arrayFunctions.h>

void peakDetection(QRS_params *params)
{
	if (isThereAPeak(params->pArrayWithPeak) == 1) {
		if (isItRPeak(params->pArrayWithPeak[1],params->THRESHOLD1) == 1) {
			rotateArrayOnce(params->pRRIntervalWithRPeaks, params->sizeOfRRIntervalWithPeaks);
			rotateArrayOnce(params->pRRIntervalAll, params->sizeOfRRIntervalAll);
			params->pRRIntervalWithRPeaks[0] = params->RRIntervalWithRPeaksCounter;
			params->pRRIntervalAll[0] = params->RRIntervalAllCounter;

		} else {
			rotateArrayOnce(params->pRRIntervalAll, params->sizeOfRRIntervalAll);
			params->pRRIntervalAll[0] = params->RRIntervalAllCounter;
		}
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

int calculateRR()
