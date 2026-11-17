#include <stdio.h>

#define MAX 20

#define OK 0
#define BLAD_OTWARCIA 1
#define BLAD_BRAK_WYMIAROW 2
#define BLAD_ZAKRES 3
#define BLAD_ZA_MALO 4
#define BLAD_ELEMENT 5
#define BLAD_NIEZGODNE 6
#define BLAD_OPERACJA 7
#define BLAD_ZAPISU 8

int wymiary_poprawne(int w, int k)
{
    return w >= 1 && w <= MAX && k >= 1 && k <= MAX;
}

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

    for (i = 0; i < w; i++)
    {
        for (j = 0; j < k; j++)
        {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

void odejmij(double A[MAX][MAX], double B[MAX][MAX], double D[MAX][MAX], int w, int k)
{
    int i, j;

    for (i = 0; i < w; i++)
    {
        for (j = 0; j < k; j++)
        {
            D[i][j] = A[i][j] - B[i][j];
        }
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

int wykonaj(int op, double A[MAX][MAX], int wA, int kA, double B[MAX][MAX], int wB, int kB, double C[MAX][MAX], int *wC, int *kC)
{
    if (op == 1)
    {
        if (wA == wB && kA == kB)
        {
            dodaj(A, B, C, wA, kA);
            *wC = wA;
            *kC = kA;
            return OK;
        }
        return BLAD_NIEZGODNE;
    }
    if (op == 2)
    {
        if (wA == wB && kA == kB)
        {
            odejmij(A, B, C, wA, kA);
            *wC = wA;
            *kC = kA;
            return OK;
        }
        return BLAD_NIEZGODNE;
    }
    if (op == 3)
    {
        if (kA == wB)
        {
            pomnoz(A, B, C, wA, kA, kB);
            *wC = wA;
            *kC = kB;
            return OK;
        }
        return BLAD_NIEZGODNE;
    }
    return BLAD_OPERACJA;
}

const char *opis_bledu(int kod)
{
    switch (kod)
    {
        case OK:
            return "ok";
        case BLAD_OTWARCIA:
            return "nie mozna otworzyc pliku";
        case BLAD_BRAK_WYMIAROW:
            return "brak wymiarow";
        case BLAD_ZAKRES:
            return "wymiary poza zakresem 1-20";
        case BLAD_ZA_MALO:
            return "za malo elementow";
        case BLAD_ELEMENT:
            return "element nie jest poprawna liczba";
        case BLAD_NIEZGODNE:
            return "niezgodne wymiary dla wybranej operacji";
        case BLAD_OPERACJA:
            return "nieznana operacja";
        case BLAD_ZAPISU:
            return "nie mozna zapisac wyniku";
        default:
            return "nieznany blad";
    }
}

static int czytaj_dane(FILE *f, double M[MAX][MAX], int *w, int *k)
{
    int i, j, wynik;

    if (fscanf(f, "%d %d", w, k) != 2)
    {
        return BLAD_BRAK_WYMIAROW;
    }
    if (!wymiary_poprawne(*w, *k))
    {
        return BLAD_ZAKRES;
    }
    for (i = 0; i < *w; i++)
    {
        for (j = 0; j < *k; j++)
        {
            wynik = fscanf(f, "%lf", &M[i][j]);
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
    return OK;
}

int wczytaj_macierz(const char *nazwa, double M[MAX][MAX], int *w, int *k)
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

int zapisz_macierz(const char *nazwa, double M[MAX][MAX], int w, int k)
{
    FILE *f;
    int i, j, blad;

    f = fopen(nazwa, "w");
    if (f == NULL)
    {
        return BLAD_ZAPISU;
    }
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
}

int main(void)
{
    int wA, kA, wB, kB, wC, kC;
    int op, kod;
    char plikA[256], plikB[256], plikWynik[256];
    double A[MAX][MAX];
    double B[MAX][MAX];
    double C[MAX][MAX];

    printf("Plik macierzy A: ");
    if (scanf("%255s", plikA) != 1)
    {
        fprintf(stderr, "Blad: %s\n", opis_bledu(BLAD_OTWARCIA));
        return 1;
    }
    kod = wczytaj_macierz(plikA, A, &wA, &kA);
    if (kod != OK)
    {
        fprintf(stderr, "Blad: %s\n", opis_bledu(kod));
        return 1;
    }

    printf("Plik macierzy B: ");
    if (scanf("%255s", plikB) != 1)
    {
        fprintf(stderr, "Blad: %s\n", opis_bledu(BLAD_OTWARCIA));
        return 1;
    }
    kod = wczytaj_macierz(plikB, B, &wB, &kB);
    if (kod != OK)
    {
        fprintf(stderr, "Blad: %s\n", opis_bledu(kod));
        return 1;
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

    printf("Plik wynikowy: ");
    if (scanf("%255s", plikWynik) != 1)
    {
        fprintf(stderr, "Blad: %s\n", opis_bledu(BLAD_ZAPISU));
        return 1;
    }
    kod = zapisz_macierz(plikWynik, C, wC, kC);
    if (kod != OK)
    {
        fprintf(stderr, "Blad: %s\n", opis_bledu(kod));
        return 1;
    }

    printf("Zapisano wynik do pliku %s\n", plikWynik);
    return 0;
}