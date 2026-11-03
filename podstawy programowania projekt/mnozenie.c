#include <stdio.h>
#define MAX 20

void wypisz(double M[MAX][MAX], int w, int k)
{
    int i, j;

    for (i = 0; i < w; i++)
    {
        for (j = 0; j < k; j++)
        {
            printf("%8.2f", M[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void dodaj(double A[MAX][MAX], double B[MAX][MAX], double C[MAX][MAX], int w, int k)
{
    int i, j;

    for (i = 0 ; i < w; i++)
    {
        for (j = 0; j < k; j++)
        {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

void zgodne_do_sumy(double A[MAX][MAX], double B[MAX][MAX], double C[MAX][MAX], int wA, int kA, int wB, int kB)
{
    if (wA == wB && kA == kB)
    {
        dodaj(A, B, C, wA, kA);
        wypisz(C, wA, kB);
    }
    else
    {
        printf("Nie mozna wykonac operacji dodawania: niezgodne wymiary.\n\n");
    }
}

void odejmij(double A[MAX][MAX], double B[MAX][MAX], double D[MAX][MAX], int w, int k)
{
    int i, j;

    for (i = 0 ; i < w; i++)
    {
        for (j = 0; j < k; j++)
        {
            D[i][j] = A[i][j] - B[i][j];
        }
    }
}

void zgodne_do_roznicy(double A[MAX][MAX], double B[MAX][MAX], double D[MAX][MAX], int wA, int kA, int wB, int kB)
{
    if (wA == wB && kA == kB)
    {
        odejmij(A, B, D, wA, kA);
        wypisz(D, wA, kB);
    }
    else
    {
        printf("Nie mozna wykonac operacji odejmowania: niezgodne wymiary.\n\n");
    }
}

void pomnoz(double A[MAX][MAX], double B[MAX][MAX], double E[MAX][MAX], int wA, int kA, int kB)
{
    int i, j, n;
    double suma;

    for (i = 0; i < wA; i++)
    {
        for (j = 0; j < kB; j++)
        {
            suma = 0.0;
            for (n = 0; n < kA; n++)
            {
                suma = suma + A[i][n] * B[n][j];
            }
            E[i][j] = suma;
        }
    }
}

void zgodne_do_mnozenia(double A[MAX][MAX], double B[MAX][MAX], double E[MAX][MAX], int wA, int kA, int wB, int kB)
{
    if (kA == wB)
    {
        pomnoz(A, B, E, wA, kA, kB);
        wypisz(E, wA, kB);
    }
    else
    {
        printf("Nie mozna wykonac operacji mnozenia: niezgodne wymiary.\n\n");
    }
}

/*
int main(void)
{
    int wA = 2, kA = 3, wB = 2, kB = 2;
    double A[MAX][MAX] = {{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}};
    double B[MAX][MAX] = {{5.0, 6.0}, {7.0, 8.0}};
    double C[MAX][MAX];
    double D[MAX][MAX];
    double E[MAX][MAX];
    
    wypisz(A, wA, kA);
    wypisz(B, wB, kB);

    zgodne_do_sumy(A, B, C, wA, kA, wB, kB);
    zgodne_do_roznicy(A, B, D, wA, kA, wB, kB);
    zgodne_do_mnozenia(A, B, E, wA, kA, wB, kB);
    return 0;
}
*/

int main(void)
{
    int wA = 2, kA = 2, wB = 2, kB = 2;
    double A[MAX][MAX] = {{1.0, 2.0}, {3.0, 4.0}};
    double B[MAX][MAX] = {{5.0, 6.0}, {7.0, 8.0}};
    double C[MAX][MAX];
    double D[MAX][MAX];
    double E[MAX][MAX];

    wypisz(A, wA, kA);
    wypisz(B, wB, kB);

    zgodne_do_sumy(A, B, C, wA, kA, wB, kB);
    zgodne_do_roznicy(A, B, D, wA, kA, wB, kB);
    zgodne_do_mnozenia(A, B, E, wA, kA, wB, kB);
    return 0;
}