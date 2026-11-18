#ifndef MATRIX_H
#define MATRIX_H

#define MAX 20

#define OK 0
#define BLAD_OTWARCIA 1
#define BLAD_WYMIAROW 2
#define BLAD_ZAKRES 3
#define BLAD_ZA_MALO 4
#define BLAD_ELEMENT 5
#define BLAD_ZAPISU 6
#define BLAD_OPERACJI 7
#define BLAD_NIEZGODNE_WYMIARY 8

int wymiary_poprawne(int w, int k);
int zgodne_do_sumy(int wA, int kA, int wB, int kB);
int zgodne_do_iloczynu(int kA, int wB);
void dodaj(double A[MAX][MAX], double B[MAX][MAX], double C[MAX][MAX], int w, int k);
void odejmij(double A[MAX][MAX], double B[MAX][MAX], double D[MAX][MAX], int w, int k);
void pomnoz(double A[MAX][MAX], double B[MAX][MAX], double E[MAX][MAX], int wA, int kA, int kB);
int wykonaj(int op, double A[MAX][MAX], int wA, int kA, double B[MAX][MAX], int wB, int kB, double C[MAX][MAX], int *wC, int *kC);
const char *opis_bledu(int kod);

#endif