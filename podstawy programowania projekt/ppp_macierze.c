#include <stdio.h>
#define MAX 20
#define OK 0
#define BLAD_OTWARCIA 1
#define BLAD_ZAKRES 2
#define BLAD_ZA_MALO 3
#define BLAD_ELEMENT 4
#define BLAD_ZAPISU 5

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

void operacja_dodaj(double A[MAX][MAX], double B[MAX][MAX], double C[MAX][MAX], int wA, int kA, int wB, int kB)
{
    if (wA == wB && kA == kB)
    {
        dodaj(A, B, C, wA, kA);
        wypisz(C, wA, kA);
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

void operacja_odejmij(double A[MAX][MAX], double B[MAX][MAX], double D[MAX][MAX], int wA, int kA, int wB, int kB)
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

void operacja_pomnoz(double A[MAX][MAX], double B[MAX][MAX], double E[MAX][MAX], int wA, int kA, int wB, int kB)
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

    operacja_dodaj(A, B, C, wA, kA, wB, kB);
    operacja_odejmij(A, B, D, wA, kA, wB, kB);
    operacja_pomnoz(A, B, E, wA, kA, wB, kB);

    FILE *f;
    int w, k;

    f = fopen("dane/A.txt", "r");
    if (f == NULL)
    {
        printf("Blad: nie mozna otworzyc pliku\n");
        return 1;
    }
    if (fscanf(f, "%d %d", &w, &k) != 2)
    {
        printf("Blad: brak wymiarow\n");
        fclose(f);
        return 1;
    }
    printf("Wymiary: %d x %d\n", w, k);
    fclose(f);

        if (!wymiary_poprawne(*w, *k))
    {
        return BLAD_ZAKRES;
    }
    for (int i = 0; i < w; i++)
    {
        for (int j = 0; j < k; j++)
        {
            int wynik = fscanf(f, "%lf", &M[i][j]);
            if (wynik == EOF)
            {
                return BLAD_ZA_MALO;
            }
            if (wynik != 1)
            {
                return BLAD_ELEMENT;
            }
        }
    }
    int wczytaj_macierz(const char *nazwa, double M[][MAX], int *w, int *k)
    {
        FILE *f;
        int kod;

        f = fopen(nazwa, "r");
        if (f == NULL)
        {
            return BLAD_OTWARCIA;
     }
        kod = czytaj_dane(f, M, w, k);
        fclose(f);
        return kod;
    }

    printf("Operacja: 1 - dodawanie, 2 - odejmowanie, 3 - mnozenie\n");
    if (scanf("%d", &op) != 1)
    {
       op = 0;
    }
    kod = wykonaj(op, A, wA, kA, B, wB, kB, C, &wC, &kC);
    if (kod != OK)
    {
        fprintf(stderr, "Blad: %s\n", opis_bledu(kod));
     return 1;
    }
    wypisz(C, wC, kC);

    fprintf(f, "%d %d\n", w, k);
    for (i = 0; i < w; i++)
    {
        for (j = 0; j < k; j++)
        {
            if (j > 0)
            {
                fprintf(f, " ");
            }
            fprintf(f, "%.2f", M[i][j]);
        }
        fprintf(f, "\n");
    }
    blad = ferror(f);
    if (fclose(f) != 0)
    {
        blad = 1;
    }
    return blad ? BLAD_ZAPISU : OK;

    return 0;
}