#include <stdio.h>
#define MAX 20

int wymiary_poprawne(int w, int k);
int zgodne_do_sumy(int wA, int kA, int wB, int kB);
void dodaj(double A[][MAX], double B[][MAX], double C[][MAX], int w, int k);
void odejmij(double A[][MAX], double B[][MAX], double C[][MAX], int w, int k);

void wypisz(double M[][MAX], int w, int k);
{
    int i, j;
    
    for (i = 0; i < w; i++) {
        for (j = 0; j < k; j++) {
            printf("%8.2f", M[i][j]);
        }
        printf("\n");
    }
}

void pomnoz(double A[][MAX], double B[][MAX], double C[][MAX], int wA, int kA, int kB)
{
    int i, j, n;
    double suma;
    
    for (i = 0; i < wA; i++) {
        for (j = 0; j < kB; j++) {
            suma = 0.0;
            for (n = 0; n < kA; n++) {
                suma = suma + A[i][n] * B[n][j];
            }
            C[i][j] = suma;
        }
    }
}

int main(void)
{
    wypisz(A, wA, kA);
    wypisz(B, wB, kB);
    
    return 0;
}