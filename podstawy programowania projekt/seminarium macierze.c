#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 10

typedef struct _macierz
{
	int w;
	int k;
	double wartosci[MAX_SIZE][MAX_SIZE]
} macierz;

void wypisz(macierz m)
{
	int i, j;
	printf("[ ");
	for (i = 0; i < m.w; i++)
	{
		if (i > 0)
			printf("  ");
		for (j = 0; j < m.k; j++)
		{
			printf("%.2lf ", m.wartosci[i][j]);
		}
		if (i < (m.w-1))
			printf("\n");
	}
	printf("]\n");
}

macierz wczytaj(char * nazwa_pliku)
{
	macierz m;
	int i, j;
	int ile;
	printf("Bede probowal wczytac dane z pliku: %s\n", nazwa_pliku);
	
	FILE * fin = fopen(nazwa_pliku, "r");
	if (fin == NULL)
	{
		printf("Blad: Nie moge otworzyc pliku: %s", nazwa_pliku);
		exit(2);
	}
	
	ile = fscanf(fin, "%d", &m.w );
	if (ile != 1)
	{
		printf("Nieprawizdlowy format pliku. Oczekiwalem liczby wierszy.");
		exit(4);
	}
	
	ile = fscanf(fin, "%d", &m.k );
	if (ile != 1)
	{
		printf("Nieprawizdlowy format pliku. Oczekiwalem liczby kolumn.");
		exit(5);
	}
	
	for (i=0; i < m.w; i++)
	{
		for (j=0; j < m.k; j++)
		{
			ile = fscanf(fin, "%lf", &m.wartosci[i][j]);
			if (ile != 1)
			{
				printf("Nieprawizdlowy format pliku dla i=%d, j=%d. Nie udalo mi sie wczytac kolejnej liczby.", i,j);
				exit(3);
			}
		}
	}
	
	fclose(fin);
	return m;
};

void zapisz(char *nazwa, macierz m)
{
	FILE * fout = fopen(nazwa, "w");
	int i,j;
	
	fprintf(fout, "%d\n", m.w);
	fprintf(fout, "%d\n", m.k);
	
	for (i=0; i < m.w; i++)
	{
		for (j=0; j < m.k; j++)
		{
			fprintf(fout, "%.2lf ", m.wartosci[i][j]);
		}
		
		if (i < (m.w-1))
		fprintf(fout, "\n");
	}
	
	fclose(fout);
}

macierz dodaj(macierz lewa, macierz prawa)
{
	macierz wynik;
	int i,j;
	
	if (lewa.k != prawa.k || lewa.w != prawa.w)
	{
		printf("Niezgodne wymiary macierzy w funkcji dodawania.\n");
		exit(2);
	}
	
	wynik.w = lewa.w;
	wynik.k = lewa.k;

	for (i=0; i < lewa.w; i++)
	{
		for (j=0; j < lewa.k; j++)
		{
			wynik.wartosci[i][j] = lewa.wartosci[i][j] + prawa.wartosci[i][j];
		}
	}
	
	return wynik;
}

macierz mnoz(macierz lewa, macierz prawa)
{
	macierz wynik;
	int i,j,k;
	double suma;
	
	if (lewa.k != prawa.w)
	{
		printf("Niezgodne wymiary macierzy w funkcji mnozenia.\n");
		exit(2);
	}
	
	wynik.w = lewa.w;
	wynik.k = prawa.k;

	for (i=0; i < lewa.w; i++)
	{
		
		for (j=0; j < prawa.k; j++)
		{
			suma = 0;
			for (k = 0; k < lewa.k; k++)
			{
				suma += lewa.wartosci[i][k] * prawa.wartosci[k][j];
			}
			wynik.wartosci[i][j] = suma;
		}
	}
	
	return wynik;
}

int main(int argc, char *argv[])
{
	macierz m1;
	macierz m2;
	macierz m3;

	if (argc < 3)
	{
		printf("Podaj argumenty. Na przyklad: sem3.exe macierz.txt wynik.txt\n");
		exit(1);
	}

	//m1 = wczytaj("macierz1.txt");
	//printf("wymiar macierzy; wierwsze: %d kolumny: %d\n", m1.w, m1.k);
	//printf("%.1lf\n", m1.wartosci[2][3]);
	m1 = wczytaj(argv[1]);
	wypisz(m1);

	if ( strcmp(argv[2], "+") == 0 )
	{
		if (argc > 3)
		{
			m2 = wczytaj(argv[3]);
			wypisz(m2);
			m3 = dodaj(m1,m2);
			
			if (argc > 4)
			{
				zapisz(argv[4], m3);
			} else
			{
				printf("Brak nazwy pliku wynikowego.");
				exit(5);
			}
		} else
		{
			printf("Operacja dodawania wymaga podania drugiego pliku.");
			exit(5);
		}
	}

	return 0;
}