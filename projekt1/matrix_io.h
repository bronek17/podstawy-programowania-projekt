#ifndef MATRIX_IO_H
#define MATRIX_IO_H

#include "matrix.h"

void wypisz(double M[MAX][MAX], int w, int k);
int wczytaj_macierz(const char *nazwa, double M[MAX][MAX], int *w, int *k);
int zapisz_macierz(const char *nazwa, double M[MAX][MAX], int w, int k);

#endif