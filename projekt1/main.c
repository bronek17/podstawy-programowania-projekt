#include <stdio.h>
#include "matrix.h"
#include "matrix_io.h"

int main(void)
{
    double A[MAX][MAX];
    double B[MAX][MAX];
    double C[MAX][MAX];
    int wA, kA, wB, kB, wC, kC;
    int op, kod;

    kod = wczytaj_macierz("dane/A.txt", A, &wA, &kA);
    if (kod != OK) {
        fprintf(stderr, "Blad: %s\n", opis_bledu(kod));
        return 1;
    }

    kod = wczytaj_macierz("dane/B.txt", B, &wB, &kB);
    if (kod != OK) {
        fprintf(stderr, "Blad: %s\n", opis_bledu(kod));
        return 1;
    }

    printf("Operacja: 1 - dodawanie, 2 - odejmowanie, 3 - mnozenie\n");
    if (scanf("%d", &op) != 1) {
        op = 0;
    }

    kod = wykonaj(op, A, wA, kA, B, wB, kB, C, &wC, &kC);
    if (kod != OK) {
        fprintf(stderr, "Blad: %s\n", opis_bledu(kod));
        return 1;
    }

    wypisz(C, wC, kC);

    kod = zapisz_macierz("wynik.txt", C, wC, kC);
    if (kod != OK) {
        fprintf(stderr, "Blad: %s\n", opis_bledu(kod));
        return 1;
    }

    printf("Wynik zapisano do pliku wynik.txt\n");
    return 0;
}