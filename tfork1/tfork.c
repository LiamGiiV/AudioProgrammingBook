// tfork.c virtual tuning fork combining sinetxt.c and expdecay.c
#define _CRT_SECURE_NO_WARNINGS // Visual Studio jank
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifndef M_PI
#define M_PI (3.141592654)
#endif // !M_PI

enum {ARGUMENT_NAME,ARGUMENT_OUTFILE,ARGUMENT_DURATION,ARGUMENT_HERTZ,ARGUMENT_SAMPLE_RATE,ARGUMENT_SLOPE,ARGUMENT_NUMBER_OF_ARGUMENTS};

int main(int argc, char** argv) {
	int argumentCount = argc;
	char** argumentValuePointerPointer = argv;
	int sr;
	double sample;
	double twicePi = 2.0 * M_PI;
	double maxSample = 0.0;
	FILE* filePointer = NULL;

	if (argumentCount != ARGUMENT_NUMBER_OF_ARGUMENTS) {
		printf("Usage: tfork1 outfile.txt duration frequency(in hertz) sample-rate slope\n");
		return 1;
	}

	filePointer = fopen(argumentValuePointerPointer[ARGUMENT_OUTFILE], "w");
	if (filePointer == NULL) {
		fprintf(stderr, "Error creating output file %s\n", argumentValuePointerPointer[ARGUMENT_OUTFILE]);
		return 1;
	}

	double duration = atof(argumentValuePointerPointer[ARGUMENT_DURATION]);
	double frequency = atof(argumentValuePointerPointer[ARGUMENT_HERTZ]);
	double sampleRate = atof(argumentValuePointerPointer[ARGUMENT_SAMPLE_RATE]);
	double slope = atof(argumentValuePointerPointer[ARGUMENT_SLOPE]);
	int numberOfSamples = (int)(duration * sampleRate);
	double angleIncrease = twicePi * frequency / sampleRate;
	double k = duration / numberOfSamples;
	double a = exp(-k / slope);
	double x = 1.0;

	int index = 0;
	for (index = 0; index < numberOfSamples; index++) {
		sample = sin(angleIncrease * index);
		// apply exponential decay
		x *= a;
		sample *= x;
		fprintf(filePointer, "%.8lf\n", sample);
	}

	fclose(filePointer);
	printf("done\n");
	return 0;
}