/*
#include <windows.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define NTHRD 4   // broj niti
#define N 10000

double a[N][N];
long grp[NTHRD];  // granica po�etak
long grk[NTHRD];  // granica kraj
HANDLE hn[NTHRD]; // HANDLE-ovi niti
long ids[NTHRD];  // ID-ovi od niti (kre�u od 0,1,2,3,...)
double sp[NTHRD];  // parcijalne sume
volatile double sm;

DWORD WINAPI nit(VOID* p)
{
	int i, j;
	int* id = (int*)p;
	sp[*id] = 0;

	for (j = grp[*id]; j < grk[*id]; j++)
	{
		for (i = 0; i < N; i++) {
			if (i == 0) {
				a[i][j] = i * sin(j) - j * cos(i);
			}
			else
			{
				a[i][j] = a[i - 1][j] + i * sin(j) - j * cos(i);
			}
			sp[*id] += a[i][j];
		}
	}
	return 0;
}

int main()
{
	int i, j;
	clock_t t1, t2;
	sm = 0;
	t1 = clock();
	for (j = 0; j < N; j++)
	{
		for (i = 0; i < N; i++) {
			if (i == 0) {
				a[i][j] = i * sin(j) - j * cos(i);
			}
			else
			{
				a[i][j] = a[i - 1][j] + i * sin(j) - j * cos(i);
			}
			sm += a[i][j];
		}
	}
	t2 = clock();

	printf("Sekvencijalno Vrijeme: %dms\n", t2 - t1);
	printf("Sekvencijalna suma: %.2f\n\n", sm);

	sm = 0;
	t1 = clock();
	long delta = N / NTHRD;
	for (i = 0; i < NTHRD; i++)
	{
		grp[i] = delta * i;
		grk[i] = delta * (i + 1);
		ids[i] = i;
		hn[i] = CreateThread(NULL, 0, nit, &ids[i], 0, NULL);
	}
	WaitForMultipleObjects(NTHRD, hn, TRUE, INFINITE);
	t2 = clock();
	for (i = 0; i < NTHRD; i++)
		sm += sp[i];
	printf("Vrijeme za %d niti: %dms\n", NTHRD, t2 - t1);
	printf("Visenitna suma: %.2f\n\n", sm);
}
*/