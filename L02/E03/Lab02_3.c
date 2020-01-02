/*
 ============================================================================
 Name        : Lab02_3.c
 Author      : Isabella Priano s258356
 Version     : 27/10/19
 Description : Laboratorio 2 esercizio 3 APA
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define max_sequenze 20  // numero massimo di sequenze da leggere da file
#define max_chars_s   5  // numero massimo di caratteri di ogni sequenza
#define max_words    10  // numero massimo di parole da trovare contenenti una data sequenza
#define max_chars_w  25  // numero massimo di caratteri di ogni parola
#define dimbuf      200  // dimensione del buffer di lettura di ogni riga di testo
#define DELIM " !\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~’\n"  // anche \n e' inteso come delimitatore

typedef struct {
 int  parole_trovate;
 int  posizioni[max_words];
 char parola   [max_sequenze][max_chars_w];
} parole;

char* minuscolo(char string[]);
void analizzastringa(char *stringa, int *n, char seq[][max_chars_s], int n_seq, parole words[]);
void stampasequenze (int n_seq, char seq[][max_chars_s], parole words[]);

int main(void) {

	FILE   *fs, *ft;
	char   buf[dimbuf];
	char   sequenze[max_sequenze][max_chars_s];
	parole words[max_sequenze];
	int    N_sequenze, i, indice_par = 0;

	fs=fopen("sequenze.txt", "r");
	if(fs==NULL) {
	   	    perror("Errore in apertura del file delle sequenze");
	   	    exit(EXIT_FAILURE);  }

	fscanf(fs, "%d\n", &N_sequenze);

	if (N_sequenze == 0) {
	   		printf("Impossibile procedere: file sequenze vuoto");
	   	    exit(EXIT_FAILURE); }

	for(i = 0; i < N_sequenze; i++) {   // legge e memorizza ogni sequenza
	   	    fgets(buf, dimbuf, fs);
	   	    sscanf(buf, "%s", sequenze[i]);
	   	    words[i].parole_trovate = 0;  }

    fclose(fs);

	ft=fopen("testo.txt", "r");
		if( ft==NULL) {
		   	    perror("Errore in apertura del file di testo da analizzare");
		   	    exit(EXIT_FAILURE); }

	while(fgets(buf, dimbuf, ft))
	    analizzastringa(buf, &indice_par, sequenze, N_sequenze, words);

    fclose(ft);

    stampasequenze (N_sequenze, sequenze, words);

    return EXIT_SUCCESS;
}

char* minuscolo(char string[])
{
	char *str_min = malloc(sizeof(char)*strlen(string) + 1);
	int i = 0;
	while (string[i] != '\0') {
    	if (isupper(string[i]))
		  str_min[i] = tolower(string[i]);
    	else
    		str_min[i] = string[i];
    	i++;  }

    str_min[i] = '\0';
 return str_min;
}

void analizzastringa(char *stringa, int *n, char seq[][max_chars_s], int n_seq, parole words[])
{
	char *token;
	int i;

	token = strtok(stringa, DELIM);
	while(token) {
		   *n = *n + 1;
           for (i = 0; i < n_seq; i++)
	          if (strstr(minuscolo(token), minuscolo(seq[i])) && words[i].parole_trovate < max_words)
	             {
	               words[i].posizioni[words[i].parole_trovate] = *n;
	               strcpy(words[i].parola[words[i].parole_trovate] , token);
	               words[i].parole_trovate++;
	             }
           token=strtok(NULL, DELIM);  }
}

void stampasequenze (int n_seq, char seq[][max_chars_s], parole words[])
{
	int i, j, n_rilevamenti = 0;

	  for (i = 0; i < n_seq; i++)
	    	if (words[i].parole_trovate > 0)
	    	{ 	printf("La sequenza %s e' contenuta in : ", seq[i]);
	    		for (j = 0; j < words[i].parole_trovate; j++ ) {
	    			n_rilevamenti++;
	    			printf("%s (posizione %d)", words[i].parola[j], words[i].posizioni[j]);
	    			j < words[i].parole_trovate - 1 ? printf(", ") : printf(".\n");	}
	    	}

		if(n_rilevamenti == 0) printf("Nessuna sequenza trovata");
}
