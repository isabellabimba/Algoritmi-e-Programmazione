//
// Created by Isabella Priano on 07/12/2019.
//

#ifndef LAB_092_INVARRAY_H
#define LAB_092_INVARRAY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inv.h"

#define MAX_LUNGH_STR 50
#define MAX_LUNGH_CODICE 7
#define FILE_INVENTARIO "inventario.txt"
#define L 20+1 //per comandi più generali

typedef struct tabInv_t* tabInv_p;
typedef struct inv_t* inv_p;

//equivalente di invArray_read
void leggiFileInventario(tabInv_p tabInv);
int trovaOggettoByNome(char nomeOggettoInput[], tabInv_p tabInv );
void deallocaInv(tabInv_p tabInv);
int getNInv(tabInv_p inventario);
void setNInv(tabInv_p inventario, int nInv);
inv_p getInvByIndice(tabInv_p inventario, int i);
tabInv_p initTabInv_p();
void initVettEquip(tabInv_p tabInv);

#endif //LAB_092_INVARRAY_H

