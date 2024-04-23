/*
#include <windows.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define NTHRD 3   // broj niti
#define N 10

double a[N][N];
long grp[NTHRD];  // granica po�etak
long grk[NTHRD];  // granica kraj
HANDLE hn[NTHRD]; // HANDLE-ovi niti
long ids[NTHRD];  // ID-ovi od niti (kre�u od 0,1,2,3,...)
double sp[NTHRD];  // parcijalne sume
volatile double long sm;

HANDLE semaphores[NTHRD];

DWORD WINAPI nit(VOID* p)
{
	int i, j;
	int* id = (int*)p;
	double long avg;
	sp[*id] = 0;

	DWORD next_thread = (*id + 1) % NTHRD;

	WaitForSingleObject(semaphores[*id], INFINITE);
	printf("nit %d je usla.\t", *id);

	if (*id == NTHRD - 1)
		grk[*id] = N;

	for (j = grp[*id]; j < grk[*id]; j++)
	{
		if (j != 0){
			avg = 0;
			for (i = 0; i < N; i++) {
				avg += a[i][j-1];
			}
			avg /= N;
		}

		for (i = 0; i < N; i++) {
			if (i == 0)
				a[i][j] = 0;
			else
			{
				if (j == 0) {
					a[i][j] = a[i - 1][j] + i * sin(j) - j * cos(i);
				}
				else
				{
					a[i][j] = avg + a[i - 1][j] + i * sin(j) - j * cos(i);
				}
				sp[*id] += a[i][j];
			}
		}
	}
	ReleaseSemaphore(semaphores[next_thread], 1, NULL);
	printf("nit %d je izasla.\n", *id);
	return 0;
}

int main()
{
	int i, j;
	double long avg = 0;
	clock_t t1, t2;
	sm = 0;
	t1 = clock();
	for (j = 0; j < N; j++)
	{
		for (i = 0; i < N; i++) {
			if (i == 0) 
				a[i][j] = 0;
			else
			{
				if (j == 0) {
					a[i][j] = a[i - 1][j] + i * sin(j) - j * cos(i);
				}
				else
				{
					a[i][j] = avg + a[i - 1][j] + i * sin(j) - j * cos(i);
				}
				sm += a[i][j];
			}
		}
		avg = 0;
		for (i = 0; i < N; i++) {
			avg += a[i][j];
		}
		avg /= N;
	}
	t2 = clock();

	printf("Sekvencijalno Vrijeme: %dms\n", t2 - t1);
	printf("Sekvencijalna suma: %.2f\n\n", sm);

	for (j = 0; j < N; j++)
	{
		for (i = 0; i < N; i++) {
			a[i][j] = 0;
		}
	}

	sm = 0;
	t1 = clock();
	long delta = floor( N / NTHRD);

	for (i = 0; i < NTHRD; i++) {
		semaphores[i] = CreateSemaphore(NULL, (i == 0) ? 1 : 0, 1, NULL);
	}

	for (i = 0; i < NTHRD; i++)
	{
		grp[i] = delta * i;
		grk[i] = delta * (i + 1);
		ids[i] = i;
		hn[i] = CreateThread(NULL, 0, nit, &ids[i], 0, NULL);
	}
	WaitForMultipleObjects(NTHRD, hn, TRUE, INFINITE);

	for (i = 0; i < NTHRD; i++) {
		CloseHandle(hn[i]);
		CloseHandle(semaphores[i]);
	}

	t2 = clock();


	for (i = 0; i < NTHRD; i++) sm += sp[i];
	printf("Vrijeme za %d niti: %dms\n", NTHRD, t2 - t1);
	printf("Visenitna suma: %.2f\n\n", sm);
}
*/