/*
 ============================================================================
 Name        : Lab05_1.c
 Author      : Priano Isabella S258356
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX 5
#define N 256
#define FILE_IN "brani.txt"

typedef struct tabella_ {
  int n_brani;
  char brani[MAX][N];
} tabella_t;

tabella_t *leggiBrani(char *nomefile, int *n_amici);
void generaPL(int *v, int c, int i_max, tabella_t *scelte);
void makePL(char *nomefile);

int main(void)
{
  makePL(FILE_IN);
  return 0;
}

tabella_t *leggiBrani(char *nomefile, int *n_amici) {
  int i, j, n_brani;
  tabella_t *dati;

  FILE *in = fopen(nomefile, "r");
  if (in == NULL)
    exit(EXIT_FAILURE);

  fscanf(in, "%d", n_amici);

  dati = (tabella_t *) malloc(sizeof(tabella_t) * (*n_amici));

  for (i=0; i<(*n_amici); i++) {
   fscanf(in, "%d", &n_brani);
   dati[i].n_brani = n_brani;
   for (j = 0; j < n_brani; j++)
	   fscanf(in, "%s", dati[i].brani[j]); }

  return dati;
}

void makePL(char *nomefile){   // funzione ausiliaria per il lancio di generaPL
	tabella_t *elenco;
	int i, n_amici, *vett;
	elenco = leggiBrani(nomefile, &n_amici);
	vett = (int *) malloc(sizeof(int) * n_amici);
	for (i = 0; i < n_amici; i++)
		vett[i]=elenco[i].n_brani;
	generaPL(vett, 0, n_amici - 1, elenco);
}

void generaPL(int *v, int c, int i_max, tabella_t *scelte)
{
  if (c == i_max){
       for (int i = v[c]; i > 0; i--){
         for (int k = 0; k < i_max; k++)
        	 printf("%s ", scelte[k].brani[v[k]-1]);
    	 printf("%s\n", scelte[c].brani[i - 1]);}
      }
  else
	{ int count = v[c];
	  for (int j = count; j > 0; j--){
        generaPL(v, c+1, i_max, scelte);
	    if (v[c] > 1)
	    	  v[c] = v[c] - 1;
	    else
	       v[c] = count;}
	}
}

