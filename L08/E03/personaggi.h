//
// Created by Isabella Priano on 04/12/2019.
//

#ifndef LAB_083_PERSONAGGI_H
#define LAB_083_PERSONAGGI_H

#define MAX_LUNGH_STR 50
#define MAX_LUNGH_CODICE 7
#include "inventario.h"

typedef struct{
    int inUso;
    inv_t** vettEq;//Vettore di puntatori a inv_t
}tabEquip_t;

typedef struct{
    char codice[MAX_LUNGH_CODICE];
    char nome[MAX_LUNGH_STR];
    char classe[MAX_LUNGH_STR];
    tabEquip_t equip;
    stat_t stat;
}pg_t;

typedef struct nodo{
    pg_t pg;
    struct nodo* next;
}nodoPg_t, *link;

typedef struct {
    link headPg;
    link tailPg;
    int nPg;
}tabPg_t;

void carica_file_PG(tabPg_t* tabPg, int nInv);
void fa_vedere(pg_t personaggio); //stampa i personaggi
void nuovo_personaggio(tabPg_t *tabPg, pg_t personaggio);
void aggiungi_PG(tabPg_t *tabPg, int nInv);
void stampa_lista_personaggi(tabPg_t* tabPg);
link trova_Pg_codice(tabPg_t *tabPg);
void elimina_PG(tabPg_t *tabPg);
void aggiungi_oggetto_personaggio(tabPg_t *tabPg, tabInv_t *tabInv);
void rimuovi_oggetto_personaggio(tabPg_t *tabPg);
void calcola_statistiche_personaggio(tabPg_t *tabPg);
void stampa_statistiche(stat_t stat);
void controllo_statistiche_piccole(stat_t *stat);
void togli_PG(tabPg_t *tabPg);
void funzione_ricerca_p(tabPg_t *tabPg);
link ricerca(tabPg_t *tabPg);

#endif //LAB_083_PERSONAGGI_H
