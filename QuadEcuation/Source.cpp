#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void Scan—oef(double* a, double* b, double* c) {
	*a = 0;
	while(*a==0.0) {
	printf("\nEnter coefficient 'a': ");
	scanf_s("%lf", a);
	 if (*a == 0.0) printf("Coef 'a' shouldn't be zero");
	}
	printf("\nEnter coefficient 'b': ");
	scanf_s("%lf", b);
	printf("\nEnter coefficient 'c': ");
	scanf_s("%lf", c);
	printf("\nYour ecuation: %f*x^2+(%f*x)+(%f)", *a, *b, *c);
}
void PrintX(double X[2], double D) {
	if (D==0.0) printf("\nRoot is: X=%lf", X[0]);
	if (D>0.0) printf("\nRoots are: X1=%lf, X2=%lf", X[0], X[1]);
	if (D < 0.0) printf("\n Discriminant is under 0, no real roots");
}
void SolveEcuation(double a, double b, double c, double *D, double *X) {
	*D = b * b - 4.0 * a * c;
	if (*D >= 0.0) {
		X[0] = (-b + sqrt(*D)) / 2.0 / a;
		X[1] = (-b - sqrt(*D)) / 2.0 / a;
	}
}

int main(void) {
	double a, b, c, D;
	double X[2];
	Scan—oef(&a, &b, &c);
	SolveEcuation(a, b, c, &D, X);
	PrintX(X, D);
	return 0;
}