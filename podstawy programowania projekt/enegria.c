#include <stdio.h>
int main(void)
{
    int i;
    int poprawne = 1;
    int liczbaSesji = 3;
    double cenaKWh = 2.0;
    double energia[3] = {10.0, 0.0, 2.5};
    double koszty[3];
    double suma = 0.0;
    double maksimum = 0.0;

    for (i = 0; i < liczbaSesji; i++) {
        if (energia[i] < 0.0) {
            printf("Blad: energia nie moze byc ujemna.\n");
            poprawne = 0;
            break;
        }

        koszty[i] = energia[i] * cenaKWh;
        suma = suma + koszty[i];

        if (i == 0 || koszty[i] > maksimum) {
            maksimum = koszty[i];
        }
    }

    if (poprawne) {
        printf("Cena energii: %.2f zl/kWh\n", cenaKWh);
        for (i = 0; i < liczbaSesji; i++) {
            printf("Sesja %d: %.2f kWh, koszt %.2f zl\n",
                i + 1, energia[i], koszty[i]);
        }
        printf("Suma kosztow: %.2f zl\n", suma);
        printf("Najwiekszy koszt sesji: %.2f zl\n", maksimum);
    }

    return 0;
}