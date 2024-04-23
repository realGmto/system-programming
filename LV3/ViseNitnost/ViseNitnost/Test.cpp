
#include <windows.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define NTHRD 4
#define N 500  // Size of the matrix

double A[N][N];
long grp[NTHRD];  // granica po�etak
long grk[NTHRD];  // granica kraj
HANDLE hn[NTHRD]; // HANDLE-ovi niti
long ids[NTHRD];  // ID-ovi od niti (kre�u od 0,1,2,3,...)
double sp[NTHRD];  // parcijalne sume

HANDLE semaphores[N];


double calculateAsps(int j) {
    if (j == 0) return 0;  // Base case when j = 0

    double sum = 0.0;
    // Computing the sum of elements in column j-1
    for (int i = 0; i < N; i++) {
        sum += A[i][j - 1];
    }
    // Calculating asps according to the formula
    return sum / N;
}

double calculateElement(int i, int j) {
    double sum = 0.0;
    for (int k = 0; k <= i; k++) {
        sum += k * sin(j) - j * cos(k);
    }
    return sum;
}

DWORD WINAPI nit(VOID* p)
{
    int i, j;
    int* id = (int*)p;

    //WaitForSingleObject(semaphores[*id], INFINITE);

    if (*id == NTHRD - 1)
        grk[*id] = N;

    for (j = 0; j < N; j++) {
        double asps = calculateAsps(j);
        WaitForSingleObject(semaphores[j-1], INFINITE);
        for (i = grp[*id]; i < grk[*id]; i++) {
            A[i][j] = asps + calculateElement(i, j);
            sp[*id] += A[i][j];
        }
        ReleaseSemaphore(semaphores[j], 1, NULL);
    }
    return 0;
}

int main() {
    double sum = 0;
    int i, j;
    clock_t t1, t2;
    t1 = clock();

    // Filling the matrix
    for (j = 0; j < N; j++) {
        double asps = calculateAsps(j);
        for (i = 0; i < N; i++) {
            A[i][j] = asps + calculateElement(i, j);
            sum += A[i][j];
        }
    }
    t2 = clock();

    printf("Sekvencijalno Vrijeme: %dms\n", t2 - t1);
    printf("Sekvencijalna suma: %.2f\n\n", sum);

    sum = 0;
    t1 = clock();

    long delta = floor(N / NTHRD);

    for (i = 0; i < N; i++) {
        semaphores[i] = CreateSemaphore(NULL, (i == 0) ? 1 : 0, 1, NULL);
    }

    for (i = 0; i < NTHRD; i++)
    {
        sp[i] = 0;
        grp[i] = delta * i;
        grk[i] = delta * (i + 1);
        ids[i] = i;
        hn[i] = CreateThread(NULL, 0, nit, &ids[i], 0, NULL);
    }
    WaitForMultipleObjects(NTHRD, hn, TRUE, INFINITE);

    for (i = 0; i < NTHRD; i++) {
        CloseHandle(hn[i]);
    }
    for (i = 0; i < N; i++) {
        CloseHandle(semaphores[i]);
    }

    t2 = clock();


    for (i = 0; i < NTHRD; i++) sum += sp[i];
    printf("Vrijeme za %d niti: %dms\n", NTHRD, t2 - t1);
    printf("Visenitna suma: %.2f\n\n", sum);

    return 0;
}
