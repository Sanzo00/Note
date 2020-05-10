#include <stdio.h>
#include <stdlib.h>
#include "config.h"

#ifdef USE_MYPOW
	#include "pow.h"
#else
	#include <math.h>
#endif

int main(int argc , char *argv[]) {
	if (argc < 3) printf("argv error!");
	double x = atof(argv[1]);
	int y = atoi(argv[2]);
#ifdef USE_MYPOW
	printf("My pow:\n");
	double res = pow(x, y);
#else
	printf("standard pow:\n");
	double res = pow(x, y);
#endif

	printf("%g ^ %d = %g\n", x, y, res);
	return 0;
}
