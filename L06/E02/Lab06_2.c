/*
 ============================================================================
 Name        : Lab06_2.c
 Author      : Priano Isabella S258356
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define L_CODICE   6
#define L_MAX     51
#define N_SCELTE   8
#define MAX_L_NF 261   // massima lungh. in caratteri del nome del file di output
#define FILE_IN  "anagrafiche.txt"  // file anagrafiche per debug
#define DBG 1                       // se 1 carica FILE_IN di default

typedef enum { FALSE, TRUE } bool;

typedef struct
{
  int a;
  int m;
  int g;
} data_t;

typedef struct
{ char   codice [L_CODICE];
  char   nome   [L_MAX];
  char   cognome[L_MAX];
  char   via    [L_MAX];
  char   citta  [L_MAX];
  data_t data;
  int    cap;
} Item;

typedef struct Nodo       /* elemento della lista */
{ Item dati;
  struct Nodo *next;
} Nodo;

typedef Nodo *ListType;   /* si definisce il tipo ListType
                             come un puntatore al tipo Nodo
                             si potranno quindi definire
                             variabili di tipo "lista" come
                             ListType (lista1, lista2 ...); */

 void showMenu  (char *scelte[], int *selezione);
 void initList  (ListType *lista);
 void printEntry(Item v, FILE *fp);
 void printList (ListType lista, char* file);
 void insertInOrderList  (ListType *lista, Item newItem);
 void readFileAnagrafiche(char *nomefile, ListType *lista, int *Num_anagrafica);
 int  comparaData  (data_t d1, data_t d2);
 int  isInDate     (data_t d_in, data_t d, data_t d_fin);
 bool isListEmpty  (ListType lista);
 Item searchForCode(ListType lista, char *codice);
 Item newItem      (int* Num_anagrafica);
 Item deleteForCode(ListType *lista, char* cod);
 Item deleteForDate(ListType *lista, data_t d_in, data_t d_fin);

 int main(void) {
  ListType lista;
  Item anagrafica;
  int selezione, uscita = FALSE, n_anagrafiche = 0, anag_rimosse;
  char c, nomeFile[MAX_L_NF], codice[L_CODICE];
  data_t di, df;

  char *scelte[] = {
       "Inserimento nuova anagrafica da tastiera",
       "Acquisizione dati per anagrafiche da file",
       "Ricerca anagrafica per codice",
       "Cancellazione anagrafica per codice",
       "Cancellazione anagrafica per intervallo date",
       "Stampa anagrafiche a video",
       "Stampa anagrafiche (con codici) su file",
	   "Uscita"   };

  initList(&lista);

  while (!uscita)
    {
    showMenu(scelte, &selezione);
    switch (selezione)
    {
    case 0: // Inserimento da tastiera di una nuova anagrafica in lista ordinata
       	   insertInOrderList(&lista, newItem(&n_anagrafiche));
       	   break;
    case 1: // Acquisizione da file di nuove anagrafiche in lista ordinata
      #if DBG
    	   readFileAnagrafiche(FILE_IN, &lista, &n_anagrafiche);
      #else
    	   printf ("\nIntroduci il nome del file: ");
    	   scanf("%s", nomeFile);
    	   readFileAnagrafiche(nomeFile, &lista, &n_anagrafiche);
      #endif
           break;
    case 2: // Ricerca anagrafica per codice
    	   printf ("\nIntroduci un codice da cercare : ");
    	   scanf("%s", codice);
    	   anagrafica = searchForCode(lista, codice);
    	   if (strlen(anagrafica.codice)){
    		   printf("Trovata anagrafica :\n");
    		   printEntry(anagrafica, stdout);}
    	   else
    	     printf("ATTENZIONE : codice non trovato!\n");
           break;
    case 3: // Cancella una speficica anagrafica individuata per codice (se esiste)
    	   printf ("\nIntroduci il codice dell'anagrafica da eliminare : ");
    	   scanf("%s", codice);
    	   anagrafica = deleteForCode(&lista, codice);
    	   if (strlen(anagrafica.codice)) {
    		  printf("Rimozione anagrafica :\n");
    		  printEntry(anagrafica, stdout);}
    	   else
    		  printf("ATTENZIONE : codice non trovato\n");
           break;
    case 4: // Cancella una o piu' anagrafiche per intervallo date
    	   printf ("\nIntroduci la data di inizio cancellazione anagrafiche : ");
    	   scanf("%d%c%d%c%d", &di.g, &c, &di.m, &c, &di.a);
    	   printf ("Introduci la data di fine cancellazione anagrafiche   : ");
    	   scanf("%d%c%d%c%d", &df.g, &c, &df.m, &c, &df.a);
    	   if (comparaData(df, di) >= 0){   // se le date inserite sono coerenti
    		   anag_rimosse = 0;
    	       printf("Report cancellazione: \n");
    	     do {
    	           anagrafica = deleteForDate(&lista, di, df);
    	           if (strlen(anagrafica.codice)){         // se viene restituito un codice...
    	               printEntry(anagrafica, stdout);
    	               anag_rimosse++;}
    	        } while (strlen(anagrafica.codice));
    	     if (anag_rimosse)                             // se e' stata rimossa almeno un'anagrafica...
    	    	printf("NUM. ANAGRAFICHE CANCNCELLATE = %d\n", anag_rimosse);
    	     else
    	    	printf("NESSUNA ANAGRAFICA TROVATA CON I CRITERI DI RICERCA INSERITI\n");
    	   }
    	   else
    		   printf("Errore nell'inserimento delle date\n");
           break;
    case 5: // Stampa anagrafiche a video
           printf ("\nStampa lista anagrafiche:\n");
           printList (lista, NULL);
           break;
    case 6: // Stampa anagrafiche su file
           printf ("\nIntroduci il nome del file: ");
           scanf("%s",nomeFile);
           printList (lista, nomeFile);
           break;
    case 7: // Uscita dal programma
           printf ("Esecuzione programma terminata\n");
           uscita = TRUE;
           break;
    default:
           printf ("Opzione non riconosciuta.\n");
           break;
    }
   }
 	return EXIT_SUCCESS;
 }

/* stampa a video del menu delle funzionalita' disponibili */
void showMenu(char *scelte[], int *selezione) {
   int i=0;
   printf("\nMENU ----------------------------\n");
   for(i=0; i < N_SCELTE; i++) printf("%2d > %s\n",i,scelte[i]);
   printf("Scelta n. ");
   scanf(" %d",selezione);
 }

 /* La funzione initList inzializza una lista alla lista vuota */
 void initList (ListType *lista)
 {
   *lista = NULL;
 }

 /* La funzione insertInOrderList inserisce un nuovo Item nella lista
    e lo colloca in ordine secondo un criterio basato sulla data di nascita */
 void insertInOrderList(ListType *lista, Item newItem) {
   ListType s, r;

 		/* la lista non contiene elementi */
   if(*lista == NULL) {
     *lista=malloc(sizeof(struct Nodo));
     (*lista)->dati = newItem;
     (*lista)->next = NULL;
     return;
   }
 		/* l'elemento va inserito in prima posizione */
   if(comparaData((*lista)->dati.data, newItem.data) <= 0) {
     s=*lista;
     *lista=malloc(sizeof(struct Nodo));
     (*lista)->dati = newItem;
     (*lista)->next = s;
     return;
   }
 	    /* la lista ha piu' di un elemento */
   s=*lista;
   while(s->next != NULL) {

     if(comparaData(s->next->dati.data, newItem.data) <= 0) {
       r=s->next;
       s->next=malloc(sizeof(struct Nodo));
       s->next->dati = newItem;
       s->next->next = r;
       return;
     }

     s=s->next;
   }
 			/* se arrivo qui, l'elemento va inserito in fondo */
   s->next = malloc(sizeof(struct Nodo));
   s->next->dati = newItem;
   s->next->next = NULL;

   return;
 }

/* funzione che stabilisce se la lista e' vuota - restituisce un boolean */
bool isListEmpty (ListType lista)
 {
   if (lista == NULL)
	   return TRUE;
   else
	   return FALSE;
 }

/* funzione che stampa un'anagrafica a video (stdout) o su file */
 void printEntry(Item v, FILE *fp) {

   char s_g[3], s_m[3],s_cap[6];
   sprintf(s_g,"%02d", v.data.g);	// inserisce lo zero nei giorni di una cifra
   sprintf(s_m,"%02d", v.data.m);   // inserisce lo zero nei mesi di una cifra
   sprintf(s_cap,"%05d", v.cap);   // inserisce gli zero nei cap con meno di 5 cifra
   fprintf(fp, "%s %s %s %s/%s/%d %s %s %s\n", v.codice, v.nome, v.cognome,
		                                       s_g, s_m, v.data.a,
											   v.via, v.citta, s_cap);
 }

 /* funzione che stampa la lista di anagrafiche a video (stdout) o su file */
 void printList(ListType lista, char* file) {
   FILE *fp;

   if(file == NULL)
     fp = stdout;
   else
     fp = fopen(file,"w");

   while (!isListEmpty(lista))
   	    {
   	      printEntry(lista->dati, fp);
   	      lista = lista->next;
   	    }
   if(file != NULL){
     fclose(fp);
     printf("\nStampa completata su %s", file);}
   else
     printf("--- FINE STAMPA\n");
 }

 /* funzione che compara due date */
 int comparaData(data_t d1, data_t d2) { // comparaData >0 se d1 > d2
   if (d1.a != d2.a)
     return (d1.a-d2.a);
   else if (d1.m != d2.m)
     return (d1.m-d2.m);
   else if (d1.g != d2.g)
     return (d1.g-d2.g);
   else return 0;
 }

 /* funzione che stabilisce se la data d e' compresa tra d_in e d_fin */
int isInDate (data_t d_in, data_t d, data_t d_fin)
{
	return (comparaData(d, d_in) >=0 && comparaData(d, d_fin) <= 0);
}

/* funzione che acquisisce da tastiera una nuova anagrafica */
Item newItem (int* Num_anagrafica)
 {
   Item new;
   char c;
   *Num_anagrafica += 1;
   sprintf(new.codice,"A%04d", *Num_anagrafica);
   printf("\nCodice attribuito : %s\n", new.codice);
   printf("Nome                 : ");
   scanf("%s", new.nome);
   printf("Cognome              : ");
   scanf("%s", new.cognome);
   printf("Nascita (gg/mm/aaaa) : ");
   scanf("%d%c%d%c%d", &new.data.g, &c, &new.data.m, &c, &new.data.a);
   printf("Residenza - via      : ");
   scanf("%s", new.via);
   printf("Residenza - citta'   : ");
   scanf("%s", new.citta);
   printf("Residenza - cap      : ");
   scanf("%d", &new.cap);
   return new;
 }

/* funzione che acquisisce da file i dati per aggiungere anagrafiche in lista */
void readFileAnagrafiche(char *nomefile, ListType *lista, int *Num_anagrafica) {
	 Item new;
	 char c, buf[5 * L_MAX];
	 int caricamenti = 0;

   FILE *in = fopen(nomefile, "r");
   if (in == NULL)
     exit(-1);

   while(fgets(buf, 5 * L_MAX, in)){
	   *Num_anagrafica += 1;
	   sprintf(new.codice,"A%04d", *Num_anagrafica);
       sscanf(buf, "%s%s%d%c%d%c%d%s%s%d", new.nome, new.cognome,
    		                               &new.data.g, &c, &new.data.m, &c, &new.data.a,
									       new.via, new.citta, &new.cap);
       insertInOrderList(lista, new);
       caricamenti++; }
   printf("Numero anagrafiche caricate = %d\n", caricamenti);
   fclose(in);
 }

/* funzione di ricerca anagrafica in lista per codice - restituisce l'Item se trovato
 * oppure un Item privo di contenuti in caso contrario                                */
Item searchForCode(ListType lista, char* codice)
{ Item Trovato ={};
  if (lista == NULL)
	return Trovato;
  else
   { if (strcmp(codice, lista->dati.codice) == 0){
	   return lista->dati;}
     else
       return(searchForCode(lista->next, codice)); }
}

/* funzione di cancellazione anagrafica in lista per codice - restituisce l'Item cancellato
 * se rinvenuto oppure un Item privo di contenuti in caso contrario                         */
Item deleteForCode(ListType *lista, char* cod) {
   Nodo *temp, *puntCorrente, *puntPrecedente;
   Item Eliminato = {};
   if(isListEmpty(*lista)) return Eliminato;
   if(strcmp((*lista)->dati.codice, cod) == 0) {  // codice trovato in capo alla lista
	     temp = *lista;
         *lista = (*lista)->next;
         Eliminato = temp->dati;
         free(temp); }
   else {
         puntPrecedente=NULL;
         for(puntCorrente = *lista; puntCorrente != NULL && strcmp(puntCorrente->dati.codice, cod) != 0;
             puntCorrente = puntCorrente->next)
        {
         puntPrecedente = puntCorrente;
        }
         if(puntCorrente!=NULL && strcmp(puntCorrente->dati.codice, cod) == 0) {
          temp = puntCorrente;
          puntPrecedente->next = puntCorrente->next;
          Eliminato = temp->dati;
          free(temp); }
        }
   return Eliminato;
}

/* funzione di cancellazione anagrafica in lista per date - restituisce l'Item cancellato
 * se rinvenuto oppure un Item privo di contenuti in caso contrario                         */
Item deleteForDate(ListType *lista, data_t d_in, data_t d_fin) {
   Nodo *temp, *puntCorrente, *puntPrecedente;
   Item Eliminato = {};
   if(isListEmpty(*lista)) return Eliminato;
   if(isInDate(d_in, (*lista)->dati.data, d_fin)) {
	     temp = *lista;
         *lista = (*lista)->next;
         Eliminato = temp->dati;
         free(temp); }
   else {
         puntPrecedente = NULL;
         for(puntCorrente = *lista; puntCorrente != NULL && !(isInDate(d_in, (*lista)->dati.data, d_fin));
    	     puntCorrente = puntCorrente->next)
        {
          puntPrecedente = puntCorrente;
        }
        if(puntCorrente != NULL && isInDate(d_in, (*lista)->dati.data, d_fin)) {
          temp = puntCorrente;
          puntPrecedente->next = puntCorrente->next;
          Eliminato = temp->dati;
          free(temp); }
        }
   return Eliminato;
}
