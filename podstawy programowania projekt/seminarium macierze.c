#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 10

struct macierz
{
	int w;
	int k;
	double wartosci[MAX_SIZE][MAX_SIZE]
};

void wypisz(struct macierz m)
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

struct macierz wczytaj(char * nazwa_pliku)
{
	struct macierz m;
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

int main(int argc, char *argv[])
{
	struct macierz m1;
	m1 = wczytaj("macierz1.txt");
	printf("wymiar macierzy; wierwsze: %d kolumny: %d\n", m1.w, m1.k);
	//printf("%.1lf\n", m1.wartosci[2][3]);
	wypisz(m1);
	return 0;
}