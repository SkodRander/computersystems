#include "../headerfiles/qsr.h"
#include <stdio.h>
#include <stdlib.h>
#include "../headerfiles/arrayFunctions.h"

#define allPeaksSize 100
#define peakTimeSize 100
#define rPeaksSize 100
#define rrIntervalsSize 8


int allPeaks[allPeaksSize] = {};
int peakTime[peakTimeSize] = {};
int rPeaks[rPeaksSize] = {};
int rrIntervals[rrIntervalsSize] = {150, 150, 150, 150, 150, 150, 150, 150};
int rrIntervalsAll[rrIntervalsSize] ={150, 150, 150, 150, 150, 150, 150, 150};

//Main function of QRS
void peakDetection(QRS_params *params)
{

	int result;
	isThereAPeak(params, &result);
	if (result == 0) {
		//If there is no peak return
		return;
	}
	//Inserts peak and time of peak into arrays
	rotateArrayOnce(allPeaks, allPeaksSize);
	allPeaks[0] = params->point;
	rotateArrayOnce(peakTime, peakTimeSize);
	peakTime[0] = params->count;

	isItRPeak(params, &result);
	if (result == 0) {
		//If it's not an R peak classify as noicepeak
		noicePeakDetected(params);
		return;
	}


	isRRIntervalBetweenLowAndHigh(params, &result);
	if (result == 1) {
		//If RR interval is between low and high classify as Regular RPeak
		params->missedRR = 0;
		regularRPeakDetected(params);
		return;
	}
	params->missedRR++;
	if(params->missedRR > 4) {
		printf("Warning! More than 4 successive RR intervals is not between RR-low and RR-high\n");
	}

	isRRIntervalLargerThanMiss(params, &result);
	if (result == 0) {return;}
	//If RR interval is larger than miss do searchback else nothing.
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
	} else {
		*result = 0;
	}
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

//Calculates pulse
void getPulse(){
	float pulse = 0.0;
	float sum_size = 0.0;
	for (int i = 0; i < rrIntervalsSize; i++) {
		//printf("%d \n", pRRIntervalAll[i]);
		if (rrIntervalsAll[i] != 0) {
			pulse += (float) rrIntervalsAll[i];
			sum_size += 1.0;
		}

	}
	pulse = pulse/250.0;
	//if (pulse == 0.0){printf("Pulse is 0");65 return;}
	pulse = sum_size/pulse;
	pulse = pulse*60.0;
	printf("\tPulse: %f", pulse);


}

//Updates parameters when RPeak is detected
void regularRPeakDetected(QRS_params *params) {
	printf("Time of R-Peak:\t%i\tValue of R-Peak: %i", params->count, params->point);
	params->SPKF = 0.125*params->point+0.875*(params->SPKF);
	rotateArrayOnce(rrIntervals, rrIntervalsSize);
	rrIntervals[0] = params->currentRR;
	rotateArrayOnce(rrIntervalsAll, rrIntervalsSize);
	rrIntervalsAll[0] = params->currentRR;
	params->lastPeak = params->count;
	updateParameters(params, 1);
	getPulse();
	checkIfPeakUnder2000(params->point);
	printf("\n");

}


void checkIfPeakUnder2000(int peak) {
	if (peak < 2000) {
		printf("\tWarning! RPeak is under 2000!");
	}
}


void searchback(QRS_params *params){

	for (int i = 1; i< allPeaksSize; i++){
		if (allPeaks[i] > params->THRESHOLD2) {
			params->currentRR = peakTime[i] -params->lastPeak;

			printf("Time of R-Peak:\t%i\tValue of R-Peak: %i", peakTime[i], allPeaks[i]);

			rotateArrayOnce(rrIntervalsAll, rrIntervalsSize);
			rrIntervalsAll[0] = params->currentRR;


			//Updates parameters
			params->lastPeak = peakTime[i];
			params->SPKF = 0.125*(allPeaks[i])+0.875*(params->SPKF);
			updateParameters(params, 2);
			getPulse();
			checkIfPeakUnder2000(allPeaks[i]);
			printf("\n");
			break;
		}
	}


}

void updateParameters(QRS_params *params, int whatAverage) {

	float sum = 0.0;
	float sumSize = 0.0;
	int i = 0;

	while(sumSize < 8) {
		//Calculates average1 or 2
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
	params->miss = 1.66*average;
	params->THRESHOLD1 = params->NPKF + 0.25*(params->SPKF - params->NPKF);
	params->THRESHOLD2 = 0.5 * params->THRESHOLD1;


}

