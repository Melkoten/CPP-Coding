#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

enum class Roots {NoRoots, OneRoot, TwoRoots};
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
	printf("\nYour ecuation: %f*x^2",*a);
	if (*b > 0.0) printf("+%f*x", *b);
	if (*b < 0.0) printf("%f*x", *b);
	if (*c > 0.0) printf("+%f", *c);
	if (*c < 0.0) printf("%f", *c);
}
void PrintX(double X[2], Roots Num) {
	if (Num==Roots::OneRoot) printf("\nRoot is: X=%lf", X[0]);
	if (Num==Roots::TwoRoots) printf("\nRoots are: X1=%lf, X2=%lf", X[0], X[1]);
	if (Num==Roots::NoRoots) printf("\n Discriminant is under 0, no real roots");
}
void SolveEcuation(double a, double b, double c, double *X, Roots *Num) {
	double D;
	D = b * b - 4.0 * a * c;
	if (D == 0.0) {
		X[0] = -b / (2.0 * a);
		*Num = Roots::OneRoot;
	}
	if (D > 0.0) {
		X[0] = (-b + sqrt(D)) / (2.0 * a);
		X[1] = (-b - sqrt(D)) / (2.0 * a);
		*Num = Roots::TwoRoots;
	}
}

int main(void) {
	Roots Num = Roots::NoRoots;
	double a, b, c;
	double X[2];
	Scan—oef(&a, &b, &c);
	SolveEcuation(a, b, c, X, &Num);
	PrintX(X, Num);
	return 0;
}