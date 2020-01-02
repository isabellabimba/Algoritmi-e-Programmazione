/*
 ============================================================================
 Name        : Lab06_1.c
 Author      : Priano Isabella S258356
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#define FILE_IN "grafo.txt"


int** leggiGrafo(char* nomefile, int *n_vertici);
void  trovaVertexCover(int v[], int si[], int k, int n, int** GRAFO);
int   isVCover(int si[],int n, int** GRAFO);

int main(){

    int *v, *si, **GRAFO, n_vertici = 0;

    GRAFO = leggiGrafo (FILE_IN, &n_vertici); // carica il grafo da file e acquisice n_vertici

    v  = (int *) malloc(sizeof(int) * n_vertici); // alloca spazio in memoria per il vettore
    si = (int *) calloc(n_vertici, sizeof(int));  // v dei vertici e si dei loro sottoinsiemi

  for (int i = 0; i < n_vertici; i++)  // costruisce il vettore con gli n_vertici del grafo
    	    v[i] = i;                  // v = { 0, 1, 2, 3 ..... n_vertici }

    // trovaVertexCover va chiamata passandole i vettori
    // v ed si, -1, la dimensione n dei vettori (n_vertici) ed il grafo da analizzare
  printf("Trovati i seguenti vertex cover:\n");
    trovaVertexCover(v, si, -1, n_vertici, GRAFO);
  printf("\nFine elaborazione\n");

    return 0;
}

int** leggiGrafo(char* nomefile, int *n_vertici) {

	int n_archi, nodo_iniz, nodo_fine, r;
	FILE *in = fopen(nomefile, "r");
	  if (in == NULL)
	    exit(EXIT_FAILURE);

	fscanf(in, "%d%d", n_vertici, &n_archi);
	int **MG;    // creazione matrice grafo
	             // come matrice delle adiacenze
	MG = calloc(*n_vertici, sizeof(int *));
	  for(r  = 0 ; r < *n_vertici ; r++)
		  MG[r] = calloc(*n_vertici, sizeof(int));
    for (r = 0; r < n_archi; r++){
    	fscanf(in, "%d%d", &nodo_iniz, &nodo_fine);
    	MG[nodo_iniz][nodo_fine] = 1;
    	MG[nodo_fine][nodo_iniz] = 1;
    }

   return MG;
}

int isVCover(int si[],int n, int** GRAFO){
	int* vr, i, j;
	vr = (int *) calloc(n, sizeof(int));

	for (i = 0; i < n; i++)
	 for (j = 0; j < n; j++)
	  if (GRAFO[i][j] == 1 && !(si[i] == 1 || si[j] == 1))
	    { free(vr);    // si esce se non viene soddisfatta anche una sola condizione
		  return 0; }  // di appartenenza di almeno un vertice degli archi alla possibile vcover

	free(vr);
	return 1;
}

void trovaVertexCover(int v[], int si[], int k, int n, int** GRAFO){
    int i= 0;
    if(k == n - 1){
        if (isVCover(si, n, GRAFO)){  // viene stampato il sottoinsieme di vertici
    	for(i = 0; i < n; i++){     // che rappesenta un vetex cover
        	if(si[i] == 1){
                printf("%d ", v[i]);
            }
        }
        printf("\n");}
    }
    else
        for(i = 0; i <= 1; i++){
            si[k + 1] = i;
            trovaVertexCover(v, si, k + 1, n, GRAFO);
        }
}


