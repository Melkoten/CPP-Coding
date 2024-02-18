#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>


void Scan—oef(float* a, float* b, float* c) {
	*a = 0;
	while(*a==0) {
	printf("\nEnter coefficient 'a': ");
	scanf_s("%f", a);
	 if (*a == 0) printf("Coef 'a' shouldn't be zero");
	}
	printf("\nEnter coefficient 'b': ");
	scanf_s("%f", b);
	printf("\nEnter coefficient 'c': ");
	scanf_s("%f", c);
	printf("\nYour ecuation: %f*x^2+(%f*x)+(%f)", *a, *b, *c);
}
void PrintX(int flag, float X[2]) {
	if (flag == 0) printf("\nThere are no Real roots of ecuation");
	if (flag == 1) printf("\nRoot is: X=%f", X[0]);
	if (flag == 2) printf("\nRoots are: X1=%f, X2=%f", X[0], X[1]);
}
void SolveEcuation(float a, float b, float c) {
	float D;
	float X[2];
	int flag = 0;
	D = b * b - 4 * a * c;
	if (D == 0) {
		flag = 1;
		X[0] = - b / 2 / a;
	}
	if (D > 0) {
		flag = 2;
		X[0] = (-b + sqrt(D)) / 2 / a;
		X[1] = (-b - sqrt(D)) / 2 / a;
	}
	PrintX(flag, X);
}

int main(void) {
	float a, b, c;
	Scan—oef(&a, &b, &c);
	SolveEcuation(a, b, c);
	return 0;
}