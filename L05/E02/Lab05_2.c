/*
 ============================================================================
 Name        : Lab05_2.c
 Author      : Priano Isabella S258356
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#define FILE_IN "mat.txt"

enum {FALSE, TRUE};
typedef int bool;

int **malloc2dR(int nr, int nc);
void free2d(int **m, int nr);
int **leggiMatDaFile(char *nomeFile, int *nr, int *nc);
bool isPari(int numero);
void separa(int **mat, int nr, int nc, int *vb, int *vn);

int main(void) {
	int nr, nc, B_size, N_size;
	int i, j;

	// leggiMatDaFile legge e alloca dinamicamente la matrice da file dati
	// e restituisce il puntatore alla matrice al main
	int **mat = leggiMatDaFile(FILE_IN, &nr, &nc);

	if (isPari(nr * nc))
		B_size = N_size = nr * nc / 2;
	else{
		B_size = nr * nc / 2 + 1;
		N_size = nr * nc / 2; }

    printf("Stampa matrice caricata:\n");
	for(i = 0; i < nr; i++){
	 for(j = 0; j < nc; j++)
		printf("%d ", mat[i][j]);
	 printf("\n");}

    int *Bvett = malloc(B_size * sizeof(int));
    int *Nvett = malloc(N_size * sizeof(int));

    separa(mat, nr, nc, Bvett, Nvett);

    printf("\nElementi scacchiera su caselle BIANCHE\n");
    for (i = 0; i < B_size; i++)
      printf("%d ", Bvett[i]);

    printf("\nElementi scacchiera su caselle NERE\n");
    for (i = 0; i < N_size; i++)
      printf("%d ", Nvett[i]);

    printf("\nEsecuzione terminata");

	return EXIT_SUCCESS;
}

int **malloc2dR(int nr, int nc){
	int **m;
	int i;
	m = malloc (nr * sizeof(int *));
	for (i = 0; i < nr; i++)
		 m[i]= malloc(nc * sizeof(int));
	return m;
}


bool isPari(int numero){
	return (numero % 2 == 0 ? TRUE : FALSE );
}

void free2d(int **m, int nr){
	int i;
	for(i = 0; i < nr; i++)
		free(m[i]);
	free(m);
}

int **leggiMatDaFile(char *nomeFile, int *nr, int *nc){
      int i, j;
	  FILE *fp = fopen(nomeFile, "r");

	  if (fp == NULL){
		perror("\nErrore in apertura del file ");
	    exit(EXIT_FAILURE); }

	  fscanf(fp, "%d%d", nr, nc);

	  int **m = malloc2dR(*nr,*nc);


	  for (i = 0; i < *nr; i++)
		for (j = 0; j < *nc; j++)
	      fscanf(fp, "%d", &m[i][j]);

	  fclose(fp);

	  return m;
	}

void separa(int **mat, int nr, int nc, int *vb, int *vn){
	int i,j, i_bianco = 0, i_nero = 0;

	  for (i = 0; i < nr; i++)
		for (j = 0; j < nc; j++){
			if (isPari(i + j))
				vb[i_bianco++] = mat[i][j];
			else
				vn[i_nero++] = mat[i][j];
		}
}
