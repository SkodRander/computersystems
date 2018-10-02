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

int main() {
	//int clocksPerSec = CLOCKS_PER_SEC;
	//clock_t start, end;
	//double cpu_time_used;
	//double startOfProgram = clock();
	FILE *file;                  // Pointer to a file object
	file = openfile("ECG.txt");
	int unfiltered[13] = { };
	int *pUnfiltered = unfiltered;
	int sizeOfUnfiltered = sizeof(unfiltered) / sizeof(int);

	int lowfiltered[33] = { };
	int *pLowfiltered = lowfiltered;
	int sizeOfLowfiltered = sizeof(lowfiltered) / sizeof(int);

	int highFiltered[5] = { };
	int *pHighFiltered = highFiltered;
	int sizeOfHighFiltered = sizeof(highFiltered) / sizeof(int);

	int squaredFiltered[31] = { };
	int *pSquaredFiltered = squaredFiltered;
	int sizeOfSquared = sizeof(squaredFiltered) / sizeof(int);

	int movingWindowFiltered[31] = { };
	int *pMovingWindowFiltered = movingWindowFiltered;
	int sizeOfMovingWindow = sizeof(movingWindowFiltered) / sizeof(int);

	int signal, eofChecker;
	int *pSignal = &signal;
	QRS_params qrsParams = { .SPKF = 0, .NPKF = 0, .THRESHOLD1 = 0,
			.THRESHOLD2 = 0, .count = 0, .point = 0, .lastPoint = 1000,
			.nextPoint = 0, .low = 0, .high = 0, .miss = 0, .currentRR = 0,
			.lastPeak = 0, .missedRR = 0 };

	/*double lowPassFilterTime = 0;
	double highPassFilterTime = 0;
	double derivativeTime = 0;
	double squaringTime = 0;
	double movingWindowTime = 0;
	double peakDetectionTime = 0;
	double getNextDataTime = 0;*/

	//double beforeWhileLoopTime = ((double) (clock() - startOfProgram)
		//	/ clocksPerSec);
	while (1) {
		//start = clock();
		signal = getNextData(file, &eofChecker);

		if (eofChecker == EOF) {
			break;
		}

		rotateArrayOnce(pUnfiltered, sizeOfUnfiltered);
		unfiltered[0] = signal;
		//end = clock();
		//getNextDataTime += ((double) (end - start) / clocksPerSec);

		//start = clock();
		lowPassFilter(pUnfiltered, pLowfiltered, pSignal);        // Filter Data
		rotateArrayOnce(pLowfiltered, sizeOfLowfiltered);
		lowfiltered[0] = signal;
		//end = clock();
		//lowPassFilterTime += ((double) (end - start) / clocksPerSec);

		//start = clock();
		highPassFilter(pLowfiltered, pHighFiltered, pSignal);
		rotateArrayOnce(pHighFiltered, sizeOfHighFiltered);
		pHighFiltered[0] = signal;
		//end = clock();
		//highPassFilterTime += ((double) (end - start) / clocksPerSec);

		//start = clock();
		derivative(highFiltered, pSignal);
		//end = clock();
		//derivativeTime += ((double) (end - start) / clocksPerSec);

		//start = clock();
		squaring(signal, pSignal);
		rotateArrayOnce(pSquaredFiltered, sizeOfSquared);
		pSquaredFiltered[0] = signal;
		//end = clock();
		//squaringTime += ((double) (end - start) / clocksPerSec);

		//start = clock();
		signal = movingWindow(pSquaredFiltered);
		rotateArrayOnce(pMovingWindowFiltered, sizeOfMovingWindow);
		pMovingWindowFiltered[0] = signal;
		//end = clock();
		//movingWindowTime += ((double) (end - start) / clocksPerSec);

		//start = clock();
		qrsParams.nextPoint = signal;
		peakDetection(&qrsParams); // Perform Peak Detection
		qrsParams.count++;
		qrsParams.lastPoint = qrsParams.point;
		qrsParams.point = qrsParams.nextPoint;
		//end = clock();
		//peakDetectionTime += ((double) (end - start) / clocksPerSec);
	}

	//double endOfProgram = clock();
	//double timeOfProgram = ((double) (endOfProgram - startOfProgram)/ clocksPerSec);

	/*double getNextDataProcent = getNextDataTime / timeOfProgram * 100;
	double lowpassProcent = lowPassFilterTime / timeOfProgram * 100;
	double highpassProcent = highPassFilterTime / timeOfProgram * 100;
	double derivativeProcent = derivativeTime / timeOfProgram * 100;
	double squaringProcent = squaringTime / timeOfProgram * 100;
	double movingWindowProcent = movingWindowTime / timeOfProgram * 100;
	double peakDetectionProcent = peakDetectionTime / timeOfProgram * 100;
	double beforeWhileLoopProcent = beforeWhileLoopTime / timeOfProgram * 100;
	double summationOfFunctionsProcent = getNextDataProcent + lowpassProcent
			+ highpassProcent + derivativeProcent + squaringProcent
			+ movingWindowProcent + peakDetectionProcent + beforeWhileLoopProcent;

	printf("Time used getNextData: %f\n", getNextDataTime);
	printf("Time used Lowpass: %f\n", lowPassFilterTime);
	printf("Time used HighPass: %f\n", highPassFilterTime);
	printf("Time used Derivative: %f\n", derivativeTime);
	printf("Time used Squaring: %f\n", squaringTime);
	printf("Time used MovingWindow: %f\n", movingWindowTime);
	printf("Time used PeakDetection: %f\n", peakDetectionTime);*/
	//printf("Total time of the program: %f\n", timeOfProgram);

	/*printf("Time used getNextData in procent: %f\n",
			getNextDataProcent / summationOfFunctionsProcent * 100);
	printf("Time used Lowpass in procent: %f\n",
			lowpassProcent / summationOfFunctionsProcent * 100);
	printf("Time used HighPass in procent: %f\n",
			highpassProcent / summationOfFunctionsProcent * 100);
	printf("Time used Derivative in procent: %f\n",
			derivativeProcent / summationOfFunctionsProcent * 100);
	printf("Time used Squaring in procent: %f\n",
			squaringProcent / summationOfFunctionsProcent * 100);
	printf("Time used MovingWindow in procent: %f\n",
			movingWindowProcent / summationOfFunctionsProcent * 100);
	printf("Time used PeakDetection in procent: %f\n",
			peakDetectionProcent / summationOfFunctionsProcent * 100);
	printf("Time used before whileloop in procent: %f\n", beforeWhileLoopProcent / summationOfFunctionsProcent * 100);
	printf("Summation of the functions: %f\n", summationOfFunctionsProcent);
	printf("Total time of the program in procent: %f\n",
			timeOfProgram / timeOfProgram * 100);*/

	printf("The program is finished");
	return 0;
}
