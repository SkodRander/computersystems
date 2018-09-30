#include "../headerfiles/qsr.h"
#include <stdio.h>
#include <stdlib.h>
#include "../headerfiles/arrayFunctions.h"

#define allPeaksSize 100
#define peakTimeSize 100
#define rPeaksSize 100
#define rrIntervalsSize 100


int allPeaks[allPeaksSize] = {};
int peakTime[peakTimeSize] = {};
int rPeaks[rPeaksSize] = {};
int rrIntervals[rrIntervalsSize] = {};
int rrIntervalsAll[rrIntervalsSize] ={};

void peakDetection(QRS_params *params)
{
	// HAR ÆNDRET RPEAKS ARRAY TIL AT INDHOLDE INDEX FOR TEST!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	int result;
	isThereAPeak(params, &result);
	if (result == 0) {
		return;
	}
	rotateArrayOnce(allPeaks, allPeaksSize);
	allPeaks[0] = params->point;
	rotateArrayOnce(peakTime, peakTimeSize);
	peakTime[0] = params->count;

	//printf("%i\t%i\t%i\n",params->THRESHOLD1,params->RRIntervalCounter,params->pPeakCheckArray[0]);
	isItRPeak(params, &result);
	if (result == 0) {
		noicePeakDetected(params);
		return;
	}

	//int average2;
	//calculateAverage2(params->pRRInterval, params->sizeOfRRInterval, &params->THRESHOLD1, &average2);
	isRRIntervalBetweenLowAndHigh(params, &result);
	if (result == 1) {
		params->missedRR = 0;
		regularRPeakDetected(params);
		return;
	}
	params->missedRR++;
	printf("%i\n",params->missedRR);
	if(params->missedRR > 4) {
		printf("Warning! More than 4 successive RR intervals is not between RR-low and RR-high\n");
	}

	isRRIntervalLargerThanMiss(params, &result);
	if (result == 0) {return;}
	searchback(params);


}

void isThereAPeak(QRS_params *params, int *result) {
	if (params->nextPoint < params->point && params->point > params->lastPoint) {
		*result = 1;
	} else {
		*result = 0;
	}

}

void isItRPeak(QRS_params *params, int *result) {
	if (params->point > params->THRESHOLD1) {
		*result = 1;
		checkIfPeakUnder2000(params->point);
	} else {
		*result = 0;
	}
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

void isRRIntervalBetweenLowAndHigh(QRS_params *params, int *result) {
	params->currentRR = params->count - params->lastPeak;
	if (params->currentRR > params->low && params->currentRR < params->high) {
		*result = 1;
	} else {
		*result = 0;
	}

}

void isRRIntervalLargerThanMiss(QRS_params *params, int *result) {
	if (params->currentRR > params->miss) {
		*result = 1;
	} else {
		*result = 0;
	}
}


void noicePeakDetected(QRS_params *params) {
	params->NPKF = 0.125 * (params->point) + 0.875 * (params->NPKF);
	params->THRESHOLD1 = params->NPKF + 0.25*((params->SPKF)-(params->NPKF));
	params->THRESHOLD2 = 0.50*(params->THRESHOLD1);
}

void getPulse(){
	double pulse = 0.0;
	for (int i = 0; i < rrIntervalsSize; i++) {
		//printf("%d \n", pRRIntervalAll[i]);
		pulse += (double) rrIntervalsAll[i];

	}
	pulse = pulse/250.0;
	//if (pulse == 0.0){printf("Pulse is 0"); return;}
	pulse = 8.0/pulse;
	pulse = pulse*60.0;
	printf("\tPulse: %f", pulse);




}

void regularRPeakDetected(QRS_params *params) {
	printf("%i\t%i", params->count, params->point);
	rotateArrayOnce(rPeaks, rPeaksSize);
	rPeaks[0] = params->point;
	params->SPKF = 0.125*params->point+0.875*(params->SPKF);
	rotateArrayOnce(rrIntervals, rrIntervalsSize);
	rrIntervals[0] = params->currentRR;
	rotateArrayOnce(rrIntervalsAll, rrIntervalsSize);
	rrIntervalsAll[0] = params->currentRR;
	params->lastPeak = params->count;
	updateParameters(params, 1);
	getPulse();
	//checkIfPeakUnder2000(params->point);
	printf("\n");

}

void insertRR(int *pRRInterval, int *sizeOfRRInterval, int RRIntervalCounter) {
	rotateArrayOnce(pRRInterval,*sizeOfRRInterval);
	pRRInterval[0] = RRIntervalCounter;

}

void checkIfPeakUnder2000(int peak) {
	if (peak < 2000) {
		printf("Warning! RPeak is under 2000!\n");
	}
}


void searchback(QRS_params *params){
	//rotateArrayOnceBackwards(params->allPeaks, params->sizeOfAllPeaks);
	for (int i = 1; i< allPeaksSize; i++){
		if (allPeaks[i] > params->THRESHOLD2) {
			rotateArrayOnce(rPeaks,rPeaksSize);
			rPeaks[0] = allPeaks[i];
			params->currentRR = peakTime[i] -params->lastPeak;
			printf("%i\t%i", peakTime[i], params->point);
			rotateArrayOnce(rrIntervalsAll, rrIntervalsSize);
			rrIntervalsAll[0] = params->currentRR;
			params->lastPeak = peakTime[i];
			params->SPKF = 0.125*params->point+0.875*(params->SPKF);
			updateParameters(params, 2);
			getPulse();
			//checkIfPeakUnder2000(params->point);
			printf("\n");
			//peakDetection(params);
			break;
		}
	}


}

void updateParameters(QRS_params *params, int whatAverage) {

	float sum = 0.0;
	float sumSize = 0.0;
	int i = 0;

	while(sumSize < 8) {
		if (whatAverage == 1) {
			if(rrIntervals[i] != 0) {
				sum += rrIntervals[i];
				sumSize++;
			} else {
				break;
			}
		} else if (whatAverage == 2){
			if(rrIntervalsAll[i] != 0) {
				sum += rrIntervalsAll[i];
				sumSize++;
			}else {
				break;
			}
		}
		i++;
	}

	float average = sum/sumSize;

	params->low = 0.92*average;
	params->high = 1.16*average;
	//printf("AVERAGE = %f\t high = %f ", average, params->high);
	params->miss = 1.66*average;
	params->THRESHOLD1 = params->NPKF + 0.25*(params->SPKF - params->NPKF);
	params->THRESHOLD2 = 0.5 * params->THRESHOLD1;


}

