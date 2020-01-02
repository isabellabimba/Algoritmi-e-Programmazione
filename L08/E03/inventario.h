//
// Created by Isabella Priano on 04/12/2019.
//

#ifndef LAB_083_INVENTARIO_H
#define LAB_083_INVENTARIO_H

#define MAX_LUNGH_STR 50
#define L 20+1 //per comandi più generali

typedef struct{
    int hp;
    int mp;
    int atk;
    int def;
    int mag;
    int spr;
}stat_t;

typedef struct{
    char nome[MAX_LUNGH_STR];
    char tipo[MAX_LUNGH_STR];
    stat_t stat;
}inv_t;

typedef struct{
    inv_t* vettInv;//Vettore
    int nInv;
    int maxInv;
}tabInv_t;

void leggiFileInventario(tabInv_t *tabInv);
int trova_oggetto_nome(char nomeOggettoInput[], tabInv_t *tabInv );
void stampa_inventario(inv_t inventario);
void togli_inv(tabInv_t *tabInv);
void ricerca_oggetto(tabInv_t *tabInv);
void stampa_oggetti(inv_t *o, int n);

#endif //LAB_083
