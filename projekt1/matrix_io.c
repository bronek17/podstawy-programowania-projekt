#include <stdio.h>
#include "matrix_io.h"

void wypisz(double M[MAX][MAX], int w, int k)
{
    int i, j;
    for (i = 0; i < w; i++) {
        for (j = 0; j < k; j++) {
            printf("%8.2f", M[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

static int czytaj_dane(FILE *f, double M[MAX][MAX], int *w, int *k)
{
    int i, j, wynik;
    if (fscanf(f, "%d %d", w, k) != 2) {
        return BLAD_WYMIAROW;
    }
    if (!wymiary_poprawne(*w, *k)) {
        return BLAD_ZAKRES;
    }
    for (i = 0; i < *w; i++) {
        for (j = 0; j < *k; j++) {
            wynik = fscanf(f, "%lf", &M[i][j]);
            if (wynik == EOF) {
                return BLAD_ZA_MALO;
            }
            if (wynik != 1) {
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
    if (f == NULL) {
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
    if (f == NULL) {
        return BLAD_OTWARCIA;
    }
    fprintf(f, "%d %d\n", w, k);
    for (i = 0; i < w; i++) {
        for (j = 0; j < k; j++) {
            if (j > 0) {
                fprintf(f, " ");
            }
            fprintf(f, "%.2f", M[i][j]);
        }
        fprintf(f, "\n");
    }
    blad = ferror(f);
    if (fclose(f) != 0) {
        blad = 1;
    }
    return blad ? BLAD_ZAPISU : OK;
}