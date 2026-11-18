#include "matrix.h"

int wymiary_poprawne(int w, int k)
{
    return w >= 1 && w <= MAX && k >= 1 && k <= MAX;
}

int zgodne_do_sumy(int wA, int kA, int wB, int kB)
{
    return wA == wB && kA == kB;
}

int zgodne_do_iloczynu(int kA, int wB)
{
    return kA == wB;
}

void dodaj(double A[MAX][MAX], double B[MAX][MAX], double C[MAX][MAX], int w, int k)
{
    int i, j;
    for (i = 0; i < w; i++) {
        for (j = 0; j < k; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

void odejmij(double A[MAX][MAX], double B[MAX][MAX], double D[MAX][MAX], int w, int k)
{
    int i, j;
    for (i = 0; i < w; i++) {
        for (j = 0; j < k; j++) {
            D[i][j] = A[i][j] - B[i][j];
        }
    }
}

void pomnoz(double A[MAX][MAX], double B[MAX][MAX], double E[MAX][MAX], int wA, int kA, int kB)
{
    int i, j, n;
    double suma;
    for (i = 0; i < wA; i++) {
        for (j = 0; j < kB; j++) {
            suma = 0.0;
            for (n = 0; n < kA; n++) {
                suma = suma + A[i][n] * B[n][j];
            }
            E[i][j] = suma;
        }
    }
}

int wykonaj(int op, double A[MAX][MAX], int wA, int kA, double B[MAX][MAX], int wB, int kB, double C[MAX][MAX], int *wC, int *kC)
{
    if (op == 1) {
        if (!zgodne_do_sumy(wA, kA, wB, kB)) {
            return BLAD_NIEZGODNE_WYMIARY;
        }
        dodaj(A, B, C, wA, kA);
        *wC = wA;
        *kC = kA;
        return OK;
    }
    if (op == 2) {
        if (!zgodne_do_sumy(wA, kA, wB, kB)) {
            return BLAD_NIEZGODNE_WYMIARY;
        }
        odejmij(A, B, C, wA, kA);
        *wC = wA;
        *kC = kA;
        return OK;
    }
    if (op == 3) {
        if (!zgodne_do_iloczynu(kA, wB)) {
            return BLAD_NIEZGODNE_WYMIARY;
        }
        pomnoz(A, B, C, wA, kA, kB);
        *wC = wA;
        *kC = kB;
        return OK;
    }
    return BLAD_OPERACJI;
}

const char *opis_bledu(int kod)
{
    switch (kod) {
        case OK:
            return "brak bledu";
        case BLAD_OTWARCIA:
            return "nie mozna otworzyc pliku";
        case BLAD_WYMIAROW:
            return "brak wymiarow";
        case BLAD_ZAKRES:
            return "wymiary poza zakresem 1-20";
        case BLAD_ZA_MALO:
            return "za malo elementow";
        case BLAD_ELEMENT:
            return "element nie jest poprawna liczba";
        case BLAD_ZAPISU:
            return "nie mozna zapisac wyniku do pliku";
        case BLAD_OPERACJI:
            return "nieznana operacja";
        case BLAD_NIEZGODNE_WYMIARY:
            return "niezgodne wymiary dla wybranej operacji";
        default:
            return "nieznany blad";
    }
}