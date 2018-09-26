#include "../headerfiles/qsr.h"
#include <stdio.h>
#include <stdlib.h>
#include "../headerfiles/arrayFunctions.h"

void peakDetection(QRS_params *params)
{
	// HAR ÆNDRET RPEAKS ARRAY TIL AT INDHOLDE INDEX FOR TEST!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


	int result;
	isThereAPeak(params->pPeakCheckArray, &result, params->allPeaks, &params->sizeOfAllPeaks);
	if (result == 0) {return;}
	else if (result == 1) {
		rotateArrayOnce(params->pGlobalCounter, params->sizeOfGlobalCounter);
		params->pGlobalCounter[0] = params->RRIntervalCounterTotal;
	}


	//printf("%i\t%i\t%i\n",params->THRESHOLD1,params->RRIntervalCounter,params->pPeakCheckArray[0]);
	isItRPeak(params->pPeakCheckArray[1], &params->THRESHOLD1, &result);
	if (result == 0) {
		noicePeakDetected(&params->THRESHOLD1, &params->THRESHOLD2, &params->NPKF, &params->SPKF, params->pPeakCheckArray[1]);
		return;
	}



	//int average2;
	//calculateAverage2(params->pRRInterval, params->sizeOfRRInterval, &params->THRESHOLD1, &average2);
	isRRIntervalBetweenLowAndHigh(params->RRIntervalCounter, params->low, params->high, &result);
	if (result == 1) {
		regularRPeakDetected(params, params->pPeakCheckArray[1]);
		return;
	}

	isRRIntervalLargerThanMiss(params->RRIntervalCounter, params->miss, &result);
	if (result == 0) {return;}
	searchback(params);


}

void isThereAPeak(int *peakCheckArray, int *result, int *allPeaks, int *sizeOfAllPeaks) {
	if (peakCheckArray[1] > peakCheckArray[0] && peakCheckArray[1] > peakCheckArray[2]) {
		if(peakCheckArray[1] != allPeaks[0]) {
			arrayInsert(allPeaks, *sizeOfAllPeaks, &peakCheckArray[1]);
			*result = 1;
		} else {
			*result = 2;
		}

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

void calculateAverage2(int *pRRInterval, int sizeOfRRInterval, int *result) {
	*result = 0;
	int runUntil8 = 0;
	while (runUntil8 != 8) {
		*result = *result + pRRInterval[runUntil8];
		runUntil8++;
	}

	*result = *result/8;
}

void isRRIntervalBetweenLowAndHigh(int rrInterval, int low, int high,int *result) {
	if (rrInterval > low && rrInterval < high) {
		*result = 1;
	} else {
		*result = 0;
	}

}

void isRRIntervalLargerThanMiss(int rrInterval, int miss, int *result) {
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

void getPulse(int *pRRIntervalAll, int sizeOfRRIntervalAll){
	double pulse = 0.0;
	for (int i = 0; i < sizeOfRRIntervalAll; i++) {
		//printf("%d \n", pRRIntervalAll[i]);
		pulse += (double) pRRIntervalAll[i];

	}
	//printf("%f", pulse);
	pulse = pulse/250.0;
	//if (pulse == 0.0){printf("Pulse is 0"); return;}
	pulse = 8.0/pulse;
	pulse = pulse*60.0;
	printf("\tPulse: %f", pulse);




}

void regularRPeakDetected(QRS_params *params, int peak) {
	rotateArrayOnce(params->pRPeakArray, params->sizeOfRPeakArray);
	params->pRPeakArray[0] = params->RRIntervalCounterTotal;
	params->SPKF = 0.125*peak+0.875*(params->SPKF);
	int tempRRIntervalCounter = params->RRIntervalCounter;
	insertRR(params->pRRInterval, &params->sizeOfRRInterval, &params->RRIntervalCounter);
	rotateArrayOnce(params->RpeaksAllIndex, params->sizeOfRpeaksAllIndex);
	params->RpeaksAllIndex[0] = params->RRIntervalCounterTotal;
	insertRR(params->pRRIntervalAll, &params->sizeOfRRIntervalAll, &tempRRIntervalCounter);
	params->THRESHOLD1 = params->NPKF + (params->SPKF-params->NPKF)/4;
	params->THRESHOLD2 = (params->THRESHOLD1)/2;
	printf("%i\t%i",params->RRIntervalCounterTotal, peak);
	getPulse(params->pRRIntervalAll, params->sizeOfRRIntervalAll);
	printf("\n");
	calculateAverage2(params->pRRInterval, params->sizeOfRRInterval, &params->average2);
	calculateAverage2(params->pRRIntervalAll, params->sizeOfRRIntervalAll, &params->average1);
	params->low = 0.92*(params->average2);
	params->high = 1.16*(params->average2);
	params->miss = 1.66*(params->average2);

}


void searchback(QRS_params *params){
	//rotateArrayOnceBackwards(params->allPeaks, params->sizeOfAllPeaks);
	for (int i = 1; i< params->sizeOfAllPeaks; i++){
		if (params->allPeaks[i] > params->THRESHOLD2) {
			rotateArrayOnce(params->pRPeakArray,params->sizeOfRPeakArray);
			params->pRPeakArray[0] = params->allPeaks[i];
			printf("SEARCH BACK :%i\t%i",params->pGlobalCounter[i], params->allPeaks[i]);
			getPulse(params->pRRIntervalAll, params->sizeOfRRIntervalAll);
			printf("\n");
			int RR = params->pGlobalCounter[i] - params->RpeaksAllIndex[0];
			rotateArrayOnce(params->RpeaksAllIndex, params->sizeOfRpeaksAllIndex);
			params->RpeaksAllIndex[0] = RR;
			//printf("%i\n",RR);
			params->SPKF = 0.125*params->pRPeakArray[0]+0.875*(params->SPKF);
			insertRR(params->pRRIntervalAll, &params->sizeOfRRIntervalAll, &RR);
			params->average1 = arrayAverage(params->pRRIntervalAll,params->sizeOfRRIntervalAll);
			params->low = 0.92*(params->average1);
			params->high = 1.16*(params->average1);
			params->miss = 1.66*(params->average1);
			params->THRESHOLD1 = params->NPKF+(params->SPKF-params->NPKF)/4;
			params->THRESHOLD2 = (params->THRESHOLD1)/2;
			params->RRIntervalCounter = params->RRIntervalCounterTotal - params->pGlobalCounter[i];
			peakDetection(params);
			break;
		}
	}


}

