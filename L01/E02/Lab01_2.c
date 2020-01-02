/*
 ============================================================================
 Name        : Lab01_2.c
 Author      : Isabella Priano s258356
 Version     : 13/10/19
 Description : Laboratorio 1 esercizio 2 APA
 OnlineGDB   : https://www.onlinegdb.com/r1Y4udxFS
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N      30
#define dimbuf 200

typedef struct daticodifica
{
  char ricodifica[dimbuf];
  char originale[dimbuf];
} sostituzioni;

char* troncanstr(char *stringa, int n);
char* concatena(const char *s_in1, const char *s_in2, const char *s_in3);
char* cerca_e_sostituisci(char *s_target, char *s_ric, char *s_sost);

int main () {

   int S, i;
   FILE *fd, *fs, *fr;
   char buf[dimbuf];
   sostituzioni dati[N];
   char *str_codificata;

   fd=fopen("dizionario.txt", "r");
   fs=fopen("sorgente.txt", "r");
   fr=fopen("ricodificato.txt","w");

   	  if( fd==NULL || fs==NULL || fr == NULL) {
   	    perror("Errore in apertura di almeno un file");
   	    exit(EXIT_FAILURE);
   	  }

   	  fgets(buf, dimbuf, fd);    // carica dizionario
   	  S = atoi(buf);
   	  if (S == 0) {
   		printf("Impossibile codificare: dizionario vuoto");
   	    exit(EXIT_FAILURE);
   	  }
   	  for(i = 0; i < S; i++) {
   	    fgets(buf, dimbuf, fd);
   	    sscanf(buf, "%s%s", dati[i].ricodifica, dati[i].originale);
   	  }

   	fclose (fd);

   	while(fgets(buf, dimbuf, fs)) {
   	       str_codificata = buf;    // si inizializza str_codificata con la riga letta dal file sorgente.txt
           for (i = 0; i < S; i++)  // si aggiorna str_codificata attraverso cerca_e_sostituisci applicata su tutte le S coppie del dizionario
        	    str_codificata = cerca_e_sostituisci(str_codificata, dati[i].originale, dati[i].ricodifica);

           fputs(str_codificata, fr);
           free(str_codificata);
    }

   fclose(fs);
   fclose(fr);

   return 0;
}

char* troncanstr(char *stringa, int n)
{
   char *sub_str = malloc(sizeof(char)*n + 1);
   if (sub_str == NULL) {
           printf("Memoria esaurita\n");
           exit(EXIT_FAILURE);
       }

   strncpy(sub_str, stringa, n);
   sub_str[n] = '\0';
   return sub_str;
}

char* concatena(const char *s_in1, const char *s_in2, const char *s_in3)
{
    char *s_out = malloc(strlen(s_in1) + strlen(s_in2) + strlen(s_in3) + 1); // +1 per il tappo
    if (s_out == NULL) {
             printf("Memoria esaurita\n");
             exit(EXIT_FAILURE);
         }

    strcpy(s_out, s_in1);
    strcat(s_out, s_in2);
    strcat(s_out, s_in3);

    return s_out;
}

char* cerca_e_sostituisci(char *s_target, char *s_ric, char *s_sost)
{
	char *s_trovata, *s_iniz;

	   s_trovata = strstr(s_target, s_ric); /* individua il puntatore alla sottostringa di s_target che inizia con s_ric
	                                           N.B. se non viene trovata s_ric in s_target si ha s_trovata = NULL */

       if (s_trovata)  // s_ric e' stata rinvenuta in s_target
	     {
    	    /* si setta s_iniz alla sottostringa estratta da s_target con il contenuto di s_target che precede
    	       la posizione in cui si trova il primo carattere di s_ric */
    	       s_iniz = troncanstr(s_target, strlen(s_target) - strlen(s_trovata));

    	    // dalla prima parte di s_trovata si rimuove s_ric
    	    memmove(s_trovata, s_trovata + strlen(s_ric), strlen(s_trovata) - strlen(s_ric) + 1);

    	    /* si richiama la funzione 'concatena' che ritorna la stringa ottenuta concatenando:
    	       - s_iniz = parte iniziale di s_target fino al punto in cui e' stata tovata s_ric
    	       - s_sost = la stringa da sostituire a s_ric
    	       - la stringa restituita dalla funzione cerca_e_sostituisci richiamata
    	         ricorsivamente su s_trovata da cui e' stata rimossa s_ric tramite preced. uso di memmove */
	        return concatena(s_iniz, s_sost, cerca_e_sostituisci(s_trovata, s_ric, s_sost));
	     }
       else
    	   return (s_target);
}
