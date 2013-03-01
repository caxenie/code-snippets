#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <float.h>
#include <stdbool.h>
#include <assert.h>

// Usable AlmostEqual function
bool compare_doubles(double A, double B, int maxUlps)
{
    // Make sure maxUlps is non-negative and small enough that the
    // default NAN won't compare as equal to anything.
    assert(maxUlps > 0 && maxUlps < 4 * 1024 * 1024);
    int aInt = *(int*)&A;
    // Make aInt lexicographically ordered as a twos-complement int
    if (aInt < 0)
        aInt = 0x80000000 - aInt;
    // Make bInt lexicographically ordered as a twos-complement int
    int bInt = *(int*)&B;
    if (bInt < 0)
        bInt = 0x80000000 - bInt;
    int intDiff = abs(aInt - bInt);
    if (intDiff <= maxUlps)
        return true;
    return false;
}

int main(int argc, char**argv)
{
 	double v1 = strtod(argv[1], NULL);
	double v2 = strtod(argv[2], NULL);

	if(compare_doubles(v1, v2, 180)==true)
		printf("Numbers are equal\n");
	else
		printf("Numbers are not equal\n");

	return EXIT_SUCCESS;
}
