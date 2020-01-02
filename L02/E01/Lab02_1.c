/*
 ============================================================================
 Name        : Lab02_1.c
 Author      : Isabella Priano s258356
 Version     : 27/10/19
 Description : Laboratorio 2 esercizio 1 APA
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_r 50
#define MAX_c 50

typedef struct {
	int xi, yi, base, altezza, area;
} regione;

// void stampamatrice(int M[][MAX_c], int r, int c);   // usata per debug

void ripristinamatrice(int M[][MAX_c], int r, int c);
regione cercaregioni(int M[][MAX_c], int r, int c);
void marcaregione(int M[][MAX_c],regione R);



int main(void) {

	FILE *fm;
	int  N_rows, N_cols, i, j;
	int  M[MAX_r][MAX_c];

	regione R, R_mb, R_mh, R_ma;

	fm=fopen("matrice.txt", "r");
	if(fm == NULL) {
	   	    perror("Errore in apertura del file delle sequenze ");
	   	    exit(EXIT_FAILURE);
	   	  }

	fscanf(fm, "%d%d", &N_rows, &N_cols);    // carica dimensioni effettive matrice dati
	for (i = 0; i < N_rows; i++)
		for (j = 0; j < N_cols; j++)
			fscanf(fm, "%d", &M[i][j]);

	fclose(fm);

	// stampamatrice (M, N_rows, N_cols);

	R_mb.base = R_mh.altezza = R_ma.area = 0;

	do {
	    R = cercaregioni(M, N_rows, N_cols);
	    if(R.base > R_mb.base)
	    	R_mb = R;
	    if(R.altezza > R_mh.altezza)
	    	R_mh = R;
	    if(R.area > R_ma.area)
	    	R_ma = R;
	   }
	while(R.area > 0);

	if (R_ma.area > 0) {  // se esiste almeno una regione nera
	    printf("Max Base   : estr. sup. SX = <%d,%d>  b = %d, h = %d, Area = %d\n",
			     R_mb.xi, R_mb.yi, R_mb.base, R_mb.altezza, R_mb.area);
	    printf("Max Area   : estr. sup. SX = <%d,%d>  b = %d, h = %d, Area = %d\n",
				 R_ma.xi, R_ma.yi, R_ma.base, R_ma.altezza, R_ma.area);
	    printf("Max Altezza: estr. sup. SX = <%d,%d>  b = %d, h = %d, Area = %d\n",
			     R_mh.xi, R_mh.yi, R_mh.base, R_mh.altezza, R_mh.area);
	} else
	    printf("Non sono stati individuati rettangoli neri\n");

	ripristinamatrice(M, N_rows, N_cols);

	return 0;
}

/* usata per debug
void stampamatrice(int M[][MAX_c], int r, int c)
{   int i, j;
	for (i = 0; i < r; i++){
				for (j = 0; j < c; j++)
					printf("%d ", M[i][j]);
				    printf("\n"); }
} */

regione cercaregioni(int M[][MAX_c], int r, int c)
{
	regione R;
	int in_regione;
	R.base = 0;
	R.altezza = 0;
	R.area = 0;

	int i, j;
	for (i = 0; i < r; i++)
	  for (j = 0; j < c; j++)
		if (M[i][j] == 1)  // se trovata una casella nera
			{ R.xi = i;
			  R.yi = j;
			  R.base = 1;
			  R.altezza = 1;

			  in_regione = 2;
			  // scansione veticale regione
			  while (i + R.altezza < r && in_regione == 2)
				  if(M[i + R.altezza][j] == 1)
				     R.altezza++;
				  else
					 in_regione = 1;

			  // scansione orizzontale regione
			  while (j + R.base < c && in_regione > 0)
				if (M[i + R.altezza - 1][j + R.base] == 1)
				    R.base++;
				else
					in_regione = 0;

              marcaregione(M,R);

			  R.area = R.base * R.altezza;
			  return R;
			  }
 return R;
}

void marcaregione(int M[][MAX_c],regione R) {
  for (int i = 0; i < R.altezza; i++)
	  for (int j = 0; j < R.base; j++)
		  M[R.xi + i][R.yi + j] = 2; }

void ripristinamatrice(int M[][MAX_c], int r, int c) {
    int i, j;
	for (i = 0; i < r; i++){
		for (j = 0; j < c; j++)
		  if (M[i][j] != 0)
			  M[i][j] = 1; }
}
