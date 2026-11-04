#include <stdio.h>
#include <stdlib.h>
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
	printf("Bede probowal wczytac dane z pliku: %s\n", nazwa_pliku);
	
	FILE * fin = fopen(nazwa_pliku, "r");
	//m.k = 6;
	fscanf(fin, "%d", &m.w );
	//m.w = 3;
	fscanf(fin, "%d", &m.k );
	
	for (i=0; i < m.w; i++)
	{
		for (j=0; j < m.k; j++)
		{
			fscanf(fin, "%lf", &m.wartosci[i][j]);
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
			fprintf(fout, "%lf ", m.wartosci[i][j]);
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
	m2 = dodaj(m1,m1);
	zapisz(argv[2], m2);

	printf("test test");
	return 0;
}