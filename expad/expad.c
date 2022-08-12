#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char** argv)
{
	if (argc != 6)
	{
		fprintf(stderr, "insufficient arguments.\n");
		fprintf(stderr, "Usage: expad duration number-of-points start-value end-value T\n");

		return 1;
	}

	double duration = atof(argv[1]);
	if (duration < -0.0)
	{
		fprintf(stderr, "Error: duration must be positive.\n");
		return 1;
	}

	int points = atoi(argv[2]);
	if (points <= 0)
	{
		fprintf(stderr, "Error: number-og-points must be a positive number.\n");
		return 1;
	}

	double ystart = atof(argv[3]);
	double yend = atof(argv[4]);
	if (yend == ystart)
	{
		fprintf(stderr, "Warning: start and end values are the same!\n");
	}

	const double TIME = atof(argv[5]);
	double k = duration / points; // so called "sample rate"
	double a = exp(-k / TIME);

	double thisStep = 0.0;
	double thisValue = ystart;
	fprintf(stderr, "a = %.6lf\n", a);

	// Make normalised curve scaled to input and range

	int index;
	for (index = 0; index < points; index++)
	{
		printf("%.4lf\t%.8lf\n", thisStep, thisValue);
		thisValue = a * thisValue + (1.0 - a) * yend;
		thisStep += k;
	}
	// final value
	printf("%.4lft%.8lf\n", thisStep, thisValue);
	fprintf(stderr, "done\n");
	return 0;
}

// why is argv[0] never used?