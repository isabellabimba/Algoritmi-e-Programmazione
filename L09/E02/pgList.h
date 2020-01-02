//
// Created by Isabella Priano on 07/12/2019.
//

#ifndef LAB_092_PGLIST_H
#define LAB_092_PGLIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pg.h"

#define MAX_LUNGH_STR 50
#define MAX_LUNGH_CODICE 7

typedef struct tabPg_t* tabPg_p;
typedef struct tabInv_t* tabInv_p;
typedef struct pg_t* pg_p;
typedef struct nodo* link;

void leggiFilePG(tabPg_p tabPg);
void newNodePersonaggio(tabPg_p tabPg, pg_p personaggio);
void aggiungiPG(tabPg_p tabPg );
void stampaListaPersonaggi(tabPg_p tabPg);
link trovaPgByCodice(tabPg_p tabPg);
void eliminaPG(tabPg_p tabPg);
void aggiungiOggettoAPersonaggio(tabPg_p tabPg,tabInv_p tabInv);
void rimuoviOggettoAPersonaggio(tabPg_p tabPg);
void calcolaStatistichePersonaggio(tabPg_p tabPg);
void deallocaPG(tabPg_p tabPg);
tabPg_p initTabPg_p();
void funzione_ricerca_p(tabPg_p tabPg);
pg_p *cercaPG(tabPg_p pgList, char *cod);
void pg_print(pg_p pgp);

#endif //LAB_092_PGLIST_H

