/*
 ============================================================================
 Name        : Lab04_2.c
 Author      : Priano Isabella S258356
 ============================================================================
 */

#include <stdlib.h>
#include <stdio.h>

#define MAX 300

int  leggi_array(int V[]);
int  majority( int *a, int N);

int main(void) {
  int N, V[MAX];
  N = leggi_array(V);
  printf("majority = %d\n", majority(V, N));

  return(0);
}


/*
 * Legge in input il numero n ed n numeri interi
 * che memorizza nell'array. Restituisce il numero
 * di elementi letti (N).
 */

int leggi_array(int V[]) {
  int N, i;
  printf("Numero di elementi: ");
  scanf("%d", &N);
  printf ("Digita gli elementi separati da uno spazio : ");
  for (i = 0; i < N; i++)
    scanf("%d", &V[i]);
  return(N);
}


int majority( int *a, int N) {

	if (N == 1) return(a[0]);

	int mid = N/2;
	int maj_l = majority (a, mid);
	int maj_r = majority (a + mid, N - mid);

	if (maj_l == maj_r) return (maj_l);

    int cl = 0, cr = 0;
	for(int i = 0; i < N; i++)  {
		 if (a[i] == maj_l) cl++;
		 if (a[i] == maj_r) cr++; }

	     if(cl > N/2)  return (maj_l);
	     if(cr > N/2)  return (maj_r);

	return (-1);  // non esiste maggioritario
}


