#include "../headerfiles/sensor.h"
#include "../headerfiles/filters.h"
#include "../headerfiles/qsr.h"
#include "../headerfiles/arrayFunctions.h"


#include <time.h>
#include <stdio.h>
#include <stdlib.h>

// Main function for organizing the program execution.
// The functions and object predefined are just for inspiration.
// Please change orden,names arguments to fit your solution.

int main()
{	
	//clock_t start, end;
	//double cpu_time_used;
	FILE *file;                  // Pointer to a file object
	file = openfile("ECG.txt");
	int unfiltered[13] = {};
	int *pUnfiltered = unfiltered;
	int sizeOfUnfiltered = sizeof(unfiltered)/sizeof(int);

	int lowfiltered[33] = {};
	int *pLowfiltered = lowfiltered;
	int sizeOfLowfiltered = sizeof(lowfiltered)/sizeof(int);

	int highFiltered[5] = {};
	int *pHighFiltered = highFiltered;
	int sizeOfHighFiltered = sizeof(highFiltered)/sizeof(int);


	int squaredFiltered[31] = {};
	int *pSquaredFiltered = squaredFiltered;
	int sizeOfSquared = sizeof(squaredFiltered)/sizeof(int);

	int movingWindowFiltered[31] = {};
	int *pMovingWindowFiltered = movingWindowFiltered;
	int sizeOfMovingWindow = sizeof(movingWindowFiltered)/sizeof(int);





	int signal, eofChecker;
	int *pSignal = &signal;
	QRS_params qrsParams = {
	.SPKF = 0,
	.NPKF = 0,
	.THRESHOLD1 =0,
	.THRESHOLD2 = 0,
	.count = 0,
	.point = 0,
	.lastPoint = 1000,
	.nextPoint = 0,
	.low = 0,
	.high = 0,
	.miss = 0,
	.currentRR = 0,
	.lastPeak = 0,
	.missedRR = 0};

	double lowPassFilterTime = 0;
	double highPassFilterTime = 0;
	double derivativeTime = 0;
	double squaringTime = 0;
	double movingWindowTime = 0;
	double peakDetectionTime = 0;


	while (1)
	{

		signal = getNextData(file, &eofChecker);


		if (eofChecker == EOF){ break;}

		rotateArrayOnce(pUnfiltered,sizeOfUnfiltered);
		unfiltered[0] = signal;

		//start = clock();
		lowPassFilter(pUnfiltered, pLowfiltered, pSignal);            // Filter Data
		rotateArrayOnce(pLowfiltered, sizeOfLowfiltered);
		lowfiltered[0] = signal;
		//end = clock();
		//lowPassFilterTime += ((double) (end - start) / CLOCKS_PER_SEC);

		//start = clock();
		highPassFilter(pLowfiltered,pHighFiltered, pSignal);
		rotateArrayOnce(pHighFiltered,sizeOfHighFiltered);
		pHighFiltered[0] = signal;
		//end = clock();
		//highPassFilterTime += ((double) (end - start) / CLOCKS_PER_SEC);

		//start = clock();
		derivative(highFiltered, pSignal);
		//end = clock();
		//derivativeTime += ((double) (end - start) / CLOCKS_PER_SEC);

		//start = clock();
		squaring(signal, pSignal);
		rotateArrayOnce(pSquaredFiltered, sizeOfSquared);
		pSquaredFiltered[0] = signal;
		//end = clock();
		//squaringTime += ((double) (end - start) / CLOCKS_PER_SEC);

		//start = clock();
		signal = movingWindow(pSquaredFiltered);
		rotateArrayOnce(pMovingWindowFiltered, sizeOfMovingWindow);
		pMovingWindowFiltered[0] = signal;
		//end = clock();
		//movingWindowTime += ((double) (end - start) / CLOCKS_PER_SEC);

		//start = clock();
		qrsParams.nextPoint = signal;
	    peakDetection(&qrsParams); // Perform Peak Detection
		qrsParams.count++;
		qrsParams.lastPoint = qrsParams.point;
		qrsParams.point = qrsParams.nextPoint;
		//end = clock();
		//speakDetectionTime += ((double) (end - start) / CLOCKS_PER_SEC);
	}


/*
	printf("Time used Lowpass: %f\n", lowPassFilterTime);
	printf("Time used HighPass: %f\n", highPassFilterTime);
	printf("Time used Derivative: %f\n", derivativeTime);
	printf("Time used Squaring: %f\n", squaringTime);
	printf("Time used MovingWindow: %f\n", movingWindowTime);
	printf("Time used PeakDetection: %f\n", peakDetectionTime);*/


	printf("The program is finished");
	return 0;
}
