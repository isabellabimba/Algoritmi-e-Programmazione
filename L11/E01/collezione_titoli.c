//
// Created by Isabella Priano on 19/12/2019.
//
#include <stdlib.h>
#include <string.h>
//#include <stdio.h>

#include "utility.h"
#include "collezione_titoli.h"
#include "classe_titoli.h"

typedef struct nodo* link;

struct collezionetitoli {
    int n;
    link h;
};

struct nodo {
    ClasseTitolo p;
    link next;
};

CollezioneTitoli COLLEZIONE_Tinit(){
    CollezioneTitoli c = malloc(sizeof(CollezioneTitoli));
    c->n = 0;
    c->h = NULL;
    return c;
}

static link NEW(char *str, link h){
    link x = malloc(sizeof(link));
    x->next = h;
    x->p = TITOLOinit(str);
    return x;
}

static link COLLEZIONE_Tinsert(CollezioneTitoli c, char *nome){ //inserisco nuovo titolo in lista
    link x, p;
    c->n++;
    if (c->h == NULL || TITOLOlower(c->h->p, nome)) {
        c->h = NEW(nome, c->h);
        return c->h;
    }
    for (x = c->h, p = x->next; p != NULL && (TITOLOgreater(x->p, nome) || TITOLOequal(x->p, nome)); x = p, p = p->next);
    x->next = NEW(nome, p);
    return x->next;
}

static link searchAndInsert(CollezioneTitoli  c, char *nome){ //ritorno titolo cercato nel caso non fosse presento lo inserisco
    link x;
    for (x = c->h; x != NULL && (TITOLOgreater(x->p, nome) || TITOLOequal(x->p, nome)); x = x->next)
        if (TITOLOequal(x->p, nome))    return x;
    return COLLEZIONE_Tinsert(c, nome);
}

static link search(link h){ //returno titolo cercato
    char nome[N];
    printf("Inserire nome titolo: ");   scanf("%s", nome);
    link x;
    for (x = h; x != NULL && (TITOLOgreater(x->p, nome)); x = x->next);
    if (TITOLOequal(x->p, nome))    return x; //se il titolo non è uguale allora il titolo non è presente in lista
    return NULL;
}

void COLLEZIONE_TinsertQuotazioni(CollezioneTitoli c, FILE *f){ //inserisco quotazione in un titolo
    char nome[N];
    int n;
    link x;
    while(fscanf(f, "%s %d", nome, &n) > 0) {
        x = searchAndInsert(c, nome);
        TITOLOaddQuotazione(x->p, f, n);
    }
}

void COLLEZIONETsearchTitolo(CollezioneTitoli c){ //cerco titolo
    link x = search(c->h);
    if (x != NULL)     printf("E' presente\n");// printf("%s\n", TITOLOgetnome(x->p));
    else                printf("Nessun titolo presente con quel nome\n");
}

void COLLEZIONETsearchQuotazione(CollezioneTitoli c){ //cerco quotazione titolo in una certa data
    link x = search(c->h);
    if (x != NULL)      TITOLOsearchQuotazione(x->p);
    else                printf("Nessun titolo presente con quel nome\n");
}

void COLLEZIONETsearchQuotazioneDate(CollezioneTitoli c){ //cerco quotazione in un certo intervallo di date
    link x = search(c->h);
    if (x != NULL)      TITOLOsearchQuotazioni(x->p);
    else                printf("Nessun titolo presente con quel nome\n");
}

void COLLEZIONETsearchMinMax(CollezioneTitoli c){ //cerco quotazioni min e max di un titolo
    link x = search(c->h);
    if (x != NULL)      TITOLOsearchMinMax(x->p);
    else                printf("Nessun titolo presente con quel nome\n");
}

void COLLEZIONETBilancia(CollezioneTitoli c){ //cerco quotazioni min e max di un titolo
    link x = search(c->h);
    if (x != NULL)      TITOLOpartizione(x->p);
    else                printf("Nessun titolo presente con quel nome\n");
}