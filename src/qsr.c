#include "../headerfiles/qsr.h"
#include <stdio.h>
#include <stdlib.h>
#include "../headerfiles/arrayFunctions.h"

void peakDetection(QRS_params *params)
{
	int result;
	isThereAPeak(params->pPeakCheckArray, &result, params->allPeaks, &params->sizeOfAllPeaks);
	if (result == 0) {return;}


	isItRPeak(params->pPeakCheckArray[1], &params->THRESHOLD1, &result);
	if (result == 0) {
		noicePeakDetected(&params->THRESHOLD1, &params->THRESHOLD2, &params->NPKF, &params->SPKF, params->pPeakCheckArray[1]);
		return;
	}

	int average2;
	calculateAverage2(params->pRRInterval, params->sizeOfRRInterval, &params->THRESHOLD1, &average2);
	isRRIntervalBetweenLowAndHigh(params->pRRInterval[0], average2, &result);
	if (result == 1) {
		regularRPeakDetected(params, params->pPeakCheckArray[1]);
		return;
	}

	isRRIntervalLargerThanMiss(params->pRRInterval[0], average2, &result);
	if (result == 0) {return;}
	printf("test");
	searchback(params, average2);


}

void isThereAPeak(int *peakCheckArray, int *result, int *allPeaks, int *sizeOfAllPeaks) {
	if (peakCheckArray[1] > peakCheckArray[0] && peakCheckArray[1] > peakCheckArray[2]) {
		arrayInsert(allPeaks, *sizeOfAllPeaks, &peakCheckArray[0]);
		*result = 1;
	} else {
		*result = 0;
	}

}

void isItRPeak(int peak, int *threshold1, int *result) {
	if (peak > *threshold1) {
		*result = 1;
	} else {
		*result = 0;
	}
}

void insertRR(int *pRRInterval, int *sizeOfRRInterval, int *RRIntervalCounter) {
	rotateArrayOnce(pRRInterval,*sizeOfRRInterval);
	pRRInterval[0] = *RRIntervalCounter;
	*RRIntervalCounter = 0;

}

void calculateAverage2(int *pRRInterval, int sizeOfRRInterval, int *threshold1, int *result) {
	*result = 0;
	int runUntil8 = 0;
	int arrayCounter = 0;
	while (runUntil8 != 8) {
		*result = *result + pRRInterval[arrayCounter];
		runUntil8++;
	}

	*result = *result/8;
}

void isRRIntervalBetweenLowAndHigh(int rrInterval, int average2,int *result) {
	int low = 0.92*(average2);
	int high = 1.16*(average2);
	if (rrInterval > low && rrInterval < high) {
		*result = 1;
	} else {
		*result = 0;
	}

}

void isRRIntervalLargerThanMiss(int rrInterval, int average2, int *result) {
	int miss = 1.66*average2;
	if (rrInterval > miss) {
		*result = 1;
	} else {
		*result = 0;
	}
}


void noicePeakDetected(int *threshold1, int *threshold2, int *NPKF, int *SPKF, int peak) {
	*threshold1 = *NPKF + ((*SPKF)-(*NPKF))/4;
	*threshold2 = (*threshold1)/2;
	*NPKF = 0.125*peak+0.875*(*NPKF);
}

void regularRPeakDetected(QRS_params *params, int peak) {
	printf("%i\n", peak);
	rotateArrayOnce(params->pRPeakArray, params->sizeOfRPeakArray);
	params->pRPeakArray[0] = peak;
	params->SPKF = 0.125*peak+0.875*(params->SPKF);
	insertRR(params->pRRInterval, &params->sizeOfRRInterval, &params->RRIntervalCounter);
	insertRR(params->pRRIntervalAll, &params->sizeOfRRIntervalAll, &params->RRIntervalAllCounter);
	params->THRESHOLD1 = params->NPKF + 0.25*(params->SPKF-params->NPKF);
	params->THRESHOLD2 = (params->THRESHOLD1)/2;

}


void searchback(QRS_params *params, int average2){
	for (int i = 0; i< params->sizeOfAllPeaks; i++){
		if (params->allPeaks[i] > params->THRESHOLD2) {
			params->pRPeakArray[0] = params->allPeaks[i];
			break;
		}
	}
	int low = 0.92*(average2);
	int high = 1.16*(average2);
	int miss = 1.66*average2;
	int average1 = arrayAverage(params->pRRIntervalAll,params->sizeOfRRIntervalAll);
	params->SPKF = 0.125*params->pRPeakArray[0]+0.875*(params->SPKF);
	params->THRESHOLD1 = params->NPKF+0.25*(params->SPKF-params->NPKF);

}

