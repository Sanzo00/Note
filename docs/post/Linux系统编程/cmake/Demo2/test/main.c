#include "add.h"
#include <stdio.h>

int main() {
	double a = 1;
	double b = 1;
	printf("%.1lf + %.1lf = %.1lf\n", a, b, add(a, b));
}
