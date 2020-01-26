//
// Created by Isabella Priano on 19/12/2019.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utility.h"
#include "classe_titoli.h"
#include "collezione_giornaliera.h"
#include "data.h"

struct classeTitolo {
    char nome[N];
    Collezione c;
};

ClasseTitolo TITOLOinit(char *nome){
    ClasseTitolo c = malloc(sizeof(ClasseTitolo));
    strcpy(c->nome, nome);
    c->c = COLLEZIONE_Qinit();
    return c;
}

char *TITOLOgetnome(ClasseTitolo c){
    return c->nome;
}

int TITOLOgreater(ClasseTitolo c, char *nome){
    if (strcmp(c->nome, nome) < 0)  return 1;
    return 0;
}

int TITOLOlower(ClasseTitolo c, char *nome){
    if (strcmp(c->nome, nome) > 0)  return 1;
    return 0;
}

int TITOLOequal(ClasseTitolo c, char *nome){
    if (strcmp(c->nome, nome) == 0) return 1;
    return 0;
}

void TITOLOaddQuotazione(ClasseTitolo c, FILE *fin, int max){ //aggiungo quotazioni nella collezione di quotazioni o aggiorno quotazioni già presenti
    Data d;
    //float v;
    //int n;
    for (int i = 0; i < max; ++i){
        fscanf(fin, "%d/%d/%d %*d:%*d %f %d\n", &d.a, &d.m, &d.g, &d.ore, &d.min);
        COLLEZIONE_Qinsert(c->c, d.ore, d.min, d);
    }
}

void TITOLOsearchQuotazione(ClasseTitolo c){ //ricerca a quotazione di un titolo in una certa data
    COLLEZIONE_QsearchData(c->c);
}

void TITOLOsearchMinMax(ClasseTitolo c){ //ricerca a quotazione max e min di un titolo
    COLLEZIONEsearchMinMax(c->c);
}

void TITOLOsearchQuotazioni(ClasseTitolo c){ //ricerca a quotazione di un titolo in un certo intervallo di date
    COLLEZIONE_QsearchIntervallDate(c->c);
}

void TITOLOpartizione(ClasseTitolo c){
    COLLEZIONEpartition(c->c);
}
