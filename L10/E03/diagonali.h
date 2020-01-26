//
// Created by Isabella Priano on 16/12/2019.
//

#ifndef LAB_103_DIAGONALI_H
#define LAB_103_DIAGONALI_H

#include "item.h"

typedef struct{
    int n;
    int difficolta_tot;
    float valore_tot;
    int elem[D];
    int bonus; //diagonale ocn bonus altrimnti senza bonus
}diagonale_t;

diagonale_t *DIAGONALIcrea(int n);
void DIAGONALIdistruggi(diagonale_t *d);

#endif //LAB_103_DIAGONALI_H
