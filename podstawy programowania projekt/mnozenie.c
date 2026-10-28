#include <stdio.h>
#define MAX 20

int wymiary_poprawne(int w, int k);
int zgodne_do_sumy(int wA, int kA, int wB, int kB);
void dodaj(double A[][MAX], double B[][MAX], double C[][MAX], int w, int k);
void odejmij(double A[][MAX], double B[][MAX], double C[][MAX], int w, int k);

void wypisz(double M[][MAX], int w, int k)
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
    int wA = 2, kA = 2, wB = 2, kB = 2;
    double A[MAX][MAX] = {{1.0, 2.0}, {3.0, 4.0}};
    double B[MAX][MAX] = {{5.0, 6.0}, {7.0, 8.0}};

    double C[MAX][MAX];
    
    wypisz(A, wA, kA);
    wypisz(B, wB, kB);
    
    pomnoz(A, B, C, wA, kA, kB);
    wypisz(C, wA, kB);
    printf("Suma A + B:\n");
    return 0;
}