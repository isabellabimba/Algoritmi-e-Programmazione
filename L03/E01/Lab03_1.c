/*
 ============================================================================
 Name        : Lab03_1.c
 Author      : Isabella Priano s258356
 Version     : 27/10/19
 Description : Laboratorio 3 esercizio 1 APA
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#define MAXR 50
#define MAXC 50

typedef struct {
	int xi, yi, base, altezza, area;
} regione;

typedef enum {FALSE, TRUE} boolean;

void leggiMatrice(int M[][MAXC], int max_righe, int* nr, int* nc);
boolean isVertice(int M[][MAXC], int r, int c);
boolean riconosciRegione(int M[][MAXC],int nr,int nc,int r, int c, int* b, int* h);


int main(void) {

	int  N_rows, N_cols, i, j, b, h;
	int  M[MAXR][MAXC];

	regione R_mb, R_mh, R_ma;

	leggiMatrice(M, MAXR, &N_rows, &N_cols);

	R_mb.base = R_mh.altezza = R_ma.area = 0;

	for (i = 0; i < N_rows; i++)
	   for (j = 0; j < N_cols; j++)
		if (riconosciRegione(M, N_rows, N_cols, i, j, &b, &h))
		  {
		   if(b > R_mb.base){
			 R_mb.xi = i; R_mb.yi = j; R_mb.base = b; R_mb.altezza = h; R_mb.area = b*h;}
		   if(h > R_mh.altezza){
			 R_mh.xi = i; R_mh.yi = j; R_mh.base = b; R_mh.altezza = h; R_mh.area = b*h;}
           if(b * h > R_ma.area){
  			 R_ma.xi = i; R_ma.yi = j; R_ma.base = b; R_ma.altezza = h; R_ma.area = b*h;}
          }

	if (R_ma.area > 0) {  // se esiste almeno una regione nera
	     printf("Max Base   : estr. sup. SX = <%d,%d>  b = %d, h = %d, Area = %d\n",
			     R_mb.xi, R_mb.yi, R_mb.base, R_mb.altezza, R_mb.area);
	     printf("Max Area   : estr. sup. SX = <%d,%d>  b = %d, h = %d, Area = %d\n",
				 R_ma.xi, R_ma.yi, R_ma.base, R_ma.altezza, R_ma.area);
	     printf("Max Altezza: estr. sup. SX = <%d,%d>  b = %d, h = %d, Area = %d\n",
					 R_mh.xi, R_mh.yi, R_mh.base, R_mh.altezza, R_mh.area);
	} else
		 printf("Non sono stati individuati rettangoli neri\n");

	return 0;
}


boolean riconosciRegione(int M[][MAXC],int nr,int nc,int r, int c, int* b, int* h)
{
	*b = *h = 0;
	if (M[r][c] == 0)   // M[r][c] rappresenta una casella bianca
	  return FALSE;
	else                // M[r][c] rappresenta una casella nera
	  if (isVertice(M, r, c)) { // se l'elemento M[r][c] e' un vertice di un rettangolo
		  *b = *h = 1;          // si individuano base ed altezza del rettangolo
	      int in_regione = 2;

	    	    // scansione verticale regione
	    	    while (r + *h < nr && in_regione == 2)
	    			if(M[r + *h][c] == 1)
	    				*h = *h + 1;
	    		    else
	    				in_regione = 1;

	    		// scansione orizzontale regione
	    		while (c + *b < nc && in_regione > 0)
	    			if (M[r + *h - 1][c + *b] == 1)
	    				*b = *b + 1;
	    			else
	    				in_regione = 0;

	    			  return TRUE;

	     } else   // l'elemento M[r][c] NON e' un vertice
	         return FALSE;
}


boolean isVertice(int M[][MAXC], int r, int c)
{
  if (c > 0)   // se il possibile vertice NON e' nella prima colonna di M
	if (M[r][c - 1] == 1)  // ed alla sua sx (stessa riga) c'e' una casella nera
		return FALSE;      // non si tratta di un vertice

  if (r > 0)   // se il possibile vertice NON e' nella prima riga di M
	if (M[r - 1][c] == 1)  // e nella riga sopra (stessa colonna) c'e' una casella nera
		return FALSE;      // non si tratta di un vertice

  return TRUE; // diversamente in <r,c> e' presente un vertice
}


void leggiMatrice(int M[][MAXC], int max_righe, int* nr, int* nc) {
	    FILE *fm;
		int i, j;

	    fm=fopen("matrice.txt", "r");
		if( fm==NULL) {
		   	    perror("Errore in apertura del file delle sequenze");
		   	    exit(EXIT_FAILURE);
		   	  }

		fscanf(fm, "%d%d", nr, nc);    // carica dimensioni matrice
		if (*nr > max_righe) {
			printf("\nLe righe della matrice superano il max consentito");
			exit(EXIT_FAILURE);
		}

		for (i = 0; i < *nr; i++)
			for (j = 0; j < *nc; j++)
				fscanf(fm, "%d", &M[i][j]);

		fclose(fm);
}
