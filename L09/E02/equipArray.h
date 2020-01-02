//
// Created by Isabella Priano on 07/12/2019.
//

#ifndef LAB_092_EQUIPARRAY_H
#define LAB_092_EQUIPARRAY_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "invArray.h"

#define MAX_LUNGH_STR 50
#define MAX_LUNGH_CODICE 7

typedef struct tabEquip_t* tabEquip_p;
typedef struct inv_t* inv_p;

int getEquipInUso(tabEquip_p equip);
inv_p getEquipByIndice(tabEquip_p  equip, int i);
void setEquipInUso(tabEquip_p equip, int inUso);
void setEquipByIndice(tabEquip_p  equip, inv_p oggetto ,int i);
tabEquip_p initTabEquip();
void initVettEq(tabEquip_p equip, int nInv);
inv_p* getVettEquip(tabEquip_p tabEquip);

#endif //LAB_092_EQUIPARRAY_H

