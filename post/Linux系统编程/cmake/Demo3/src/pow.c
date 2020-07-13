#include "pow.h"
#include <stdio.h>

double pow(double x, int y) {
	if (y == 0) return 1.0;
	double res = x;
	for (int i = 0; i < y; ++i) {
		res = res * x;
	}
	return res;
}
