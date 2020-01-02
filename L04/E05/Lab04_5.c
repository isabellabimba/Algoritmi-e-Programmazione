/*
 ============================================================================
 Name        : LAB04_5.c
 Author      : Priano Isabella S258356
 ============================================================================
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEN 26
#define DBG 0

#define MAXR     1000
#define STR      31
#define N_SCELTE 9
#define FILE_IN  "log.txt"
#define TIPI_ORD 4

typedef enum chiaveOrdinamento_e {NESSUNO, DATA, CODICE, PARTENZA, ARRIVO} chiaveOrdinamento;

typedef struct {
  int a;
  int m;
  int g;
} data_t;

typedef struct {
  int h;
  int m;
  int s;
} ora_t;

typedef struct {
  char codice[STR];
  char partenza[STR];
  char destinazione[STR];
  char data_str[STR];
  char orap_str[STR];
  char orad_str[STR];
  int ritardo;
  data_t data;
  ora_t p, d;
} voce_t;


enum { falso, vero };
typedef int bool;

int  leggiVoci(voce_t *el);
int  comparaData(data_t d1, data_t d2);
int  confrontaVoci(voce_t v1, voce_t v2, chiaveOrdinamento k);
void stampaElenco(voce_t el[], int nr);
void stampaRif(char *nomeFile, voce_t **rec, int nr);
void stampaSuFile(voce_t **r1, voce_t **r2, voce_t **r3, voce_t **r4, char *nomeFile, int nr);
void stampaMenu(char *scelte[], int *selezione);
void stampaEntry(voce_t v, FILE *fp);
void ordinaRifElenco(voce_t **rec, chiaveOrdinamento k, int n);
void ricercaPartenzaDicotomica(voce_t **rec, char *partenza, int nCharConfronto, int nr);
bool ricercaCodiceDicotomica(voce_t **rec, int nr, char *codiceRicerca, int *indice);

int main(int argc, char** argv) {

  char *scelte[] = {
    "Uscita",
    "Stampa  a   video (dati oiginali)",
    "  ord.  per data",
    "  ord.  per codice",
    "  ord.  per stazione di partenza",
    "  ord.  per stazione di arrivo",
    "  ord.  su  file (con scelta tipo ord.)",
    "Ricerca per codice (parziale)",
    "        per stazione di partenza"
  };

  voce_t elenco[MAXR];
  voce_t *elencoRifData[MAXR], *elencoRifCod[MAXR], *elencoRifPart[MAXR], *elencoRifArr[MAXR];
  int nr;    // numero registrazioni nel file di log

  char codiceRicerca[LEN], partenzaRicerca[LEN];
  int selezione, nCharConfronto;
  bool fineProgramma;
  char nomeFile[25];
  int indice = -1, trovato = 0;

  nr = leggiVoci(elenco);

for (int i = 0; i < nr; i++){ // caricamento vettori puntatori a elementi di "elenco"
	elencoRifData[i] = elencoRifPart[i] = elencoRifCod[i] = elencoRifArr[i] = &elenco[i]; }


#if DBG
  stampaElenco(elenco, nr);
#endif
  fineProgramma = falso;

  ordinaRifElenco(elencoRifData, DATA, nr);
  ordinaRifElenco(elencoRifCod, CODICE, nr);
  ordinaRifElenco(elencoRifPart, PARTENZA, nr);
  ordinaRifElenco(elencoRifArr, ARRIVO, nr);

  do {
    stampaMenu(scelte, &selezione);
    switch(selezione) {

    case 0: {
      fineProgramma = vero;
    }
    break;
    case 1: {
            	stampaElenco(elenco, nr);
            }
            break;

    case 2: {
      printf("Elenco ordinato per data\n");
      stampaRif(NULL, elencoRifData, nr);
    }
    break;

    case 3: {
      printf("Elenco ordinato per codice\n");
      stampaRif(NULL, elencoRifCod, nr);
    }
    break;

    case 4: {
      printf("Elenco ordinato per partenza\n");
      stampaRif(NULL, elencoRifPart, nr);
    }
    break;

    case 5: {
      printf("Elenco ordinato per arrivo\n");
      stampaRif(NULL, elencoRifArr, nr);
    }
    break;

    case 6: {
          printf("Inserire nome file\n");
          scanf("%s",nomeFile);
          stampaSuFile(elencoRifData, elencoRifCod, elencoRifPart, elencoRifArr, nomeFile, nr);
        }
        break;

    case 7: {
      printf("Inserire codice: ");
      scanf("%s", codiceRicerca);
      indice = -1;
      trovato = falso ;
      trovato = ricercaCodiceDicotomica(elencoRifCod, nr, codiceRicerca, &indice);
      if (trovato) stampaEntry(*elencoRifCod[indice], stdout);
    }
    break;

    case 8: {
      printf("Inserire stazione di partenza: ");
      scanf("%s", partenzaRicerca);
      nCharConfronto = strlen(partenzaRicerca);
      ricercaPartenzaDicotomica(elencoRifPart, partenzaRicerca, nCharConfronto, nr);
    }
    break;

    default: {
      printf("Scelta non valida\n");
    }
    break;
    }
  } while(!fineProgramma);

  printf("\nEsecuzione programma terminata");
  return 0;
}

int comparaData(data_t d1, data_t d2) {
  if (d1.a != d2.a)
    return (d1.a-d2.a);
  else if (d1.m != d2.m)
    return (d1.m-d2.m);
  else if (d1.g != d2.g)
    return (d1.g-d2.g);
  else return 0;
}

int comparaOra(ora_t o1, ora_t o2) {
  if (o1.h != o2.h)
    return (o1.h-o2.h);
  else if (o1.m != o2.m)
    return (o1.m-o2.m);
  else if (o1.s != o2.s)
    return (o1.s-o2.s);
  else return 0;
}

void stampaMenu(char *scelte[], int *selezione) {
  int i=0;
  printf("\nMENU'\n");
  for(i=0; i<N_SCELTE; i++) printf("%2d > %s\n",i,scelte[i]);
  scanf(" %d",selezione);
}

int leggiVoci(voce_t *el) {
  int i, n = 0;
  FILE *fp = fopen(FILE_IN, "r");
  if (fp == NULL)
    exit(-1);

  fscanf(fp, "%d", &n);
  for (i=0; i < n; i++) {
    fscanf(fp, "%s %s %s %s %s %s %d\n", el[i].codice, el[i].partenza, el[i].destinazione, el[i].data_str, el[i].orap_str, el[i].orad_str, &el[i].ritardo);
    sscanf (el[i].data_str,"%d/%d/%d", &el[i].data.a,&el[i].data.m,&el[i].data.g);
    sscanf (el[i].orap_str,"%d:%d:%d", &el[i].p.h,&el[i].p.m,&el[i].p.s);
    sscanf (el[i].orad_str,"%d:%d:%d", &el[i].d.h,&el[i].d.m,&el[i].d.s);
  }
  fclose(fp);
  return n;
}

void ordinaRifElenco(voce_t **rec, chiaveOrdinamento k, int n) {
  int i, j, imin;
  voce_t *temp;

  for(i = 0; i < n - 1; i++) {
	    imin = i;
	    for(j = i + 1; j < n; j++)
	    	if (confrontaVoci(*rec[j], *rec[imin], k) < 0)
	    		imin = j;
	    temp = rec[i];
	    rec[i] = rec[imin];
	    rec[imin] = temp;
	    }
  }

int confrontaVoci(voce_t v1, voce_t v2, chiaveOrdinamento k) {
  switch(k) {
    case DATA: {
      int cmp = comparaData(v1.data, v2.data);
      if (cmp == 0) return comparaOra(v1.p, v2.p);
      return cmp;
    }
    break;
    case CODICE: {
      return strcmp(v1.codice, v2.codice);
    }
    break;
    case PARTENZA: {
      return strcmp(v1.partenza, v2.partenza);
    }
    break;
    case ARRIVO: {
      return strcmp(v1.destinazione, v2.destinazione);
    }
    break;
    default: {
    } break;
  }
  return 0;
}

void stampaElenco(voce_t el[], int nr)
{   int i;
	for(i=0; i < nr; i++) stampaEntry(el[i], stdout);
}

void stampaEntry(voce_t v, FILE *fp) {
  fprintf(fp, "%s %s %s %s %s %s %d\n", v.codice, v.partenza, v.destinazione, v.data_str, v.orap_str, v.orad_str, v.ritardo);
}

void stampaRif(char *nomeFile, voce_t **rec, int nr) {
  int i;
  FILE *fp;
  if(nomeFile == NULL)
    fp = stdout;
  else
    fp = fopen(nomeFile,"w");

  for(i=0; i < nr; i++) stampaEntry(*rec[i], fp);

  if(nomeFile!=NULL)
    fclose(fp);
}


bool ricercaCodiceDicotomica(voce_t **rec, int nr, char *codiceRicerca, int *indice) {
  int iniziale = 0, finale = nr - 1, medio, cmp;

  if(finale < 0)
    return falso;

  while(iniziale <= finale) {
    medio = (iniziale + finale) / 2;
    cmp = strcmp(rec[medio]->codice, codiceRicerca);
    if(cmp == 0) {
      *indice = medio;
      return vero;
    }
    if(cmp < 0)
      iniziale = medio + 1;
    else
      finale = medio - 1;
  }
  return falso;
}


void ricercaPartenzaDicotomica(voce_t **rec, char *partenza, int nCharConfronto, int nr) {
  int iniziale = 0, finale = nr - 1, medio, i, j, cmp;
  bool trovato = falso;

  while(iniziale <= finale && !trovato) {
    medio = (iniziale + finale) / 2;
    cmp = strncmp(rec[medio]->partenza, partenza, nCharConfronto);
    if(cmp == 0) {
      trovato = vero;
    } else {
      if(cmp < 0)
        iniziale = medio + 1;
      else
        finale = medio - 1;
    }
  }

  if(trovato) {
    i = medio;
    j = medio -1;
    while(i < nr && strncmp(rec[i]->partenza, partenza, nCharConfronto) == 0) {
    	stampaEntry(*rec[i], stdout);
      i++;
    }
    while(j>=0 && strncmp(rec[j]->partenza, partenza, nCharConfronto) == 0) {
      stampaEntry(*rec[i], stdout);
      j--;
    }
  } else
    printf("Voce non trovata");
}

void stampaSuFile(voce_t **r1, voce_t **r2, voce_t **r3, voce_t **r4, char *nomeFile, int nr) {
  int k;
  printf("\nStampa su file %s con ordinamento", nomeFile);
  printf("\n 1 - per data");
  printf("\n 2 - per codice");
  printf("\n 3 - per stazione di partenza");
  printf("\n 4 - per stazione di arrivo");
  printf("\n 0 - per uscire");
  printf("\n Scelta > ");
  scanf("%d", &k);
  switch(k) {
    case DATA: {
      stampaRif(nomeFile, r1, nr);

      }
      break;
    case CODICE: {
      stampaRif(nomeFile, r2, nr);
      }
      break;
    case PARTENZA: {
      stampaRif(nomeFile, r3, nr);
      }
      break;
    case ARRIVO: {
      stampaRif(nomeFile, r4, nr);
      }
      break;
    default: {
      }
      break;
  }
}
