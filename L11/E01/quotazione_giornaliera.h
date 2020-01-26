//
// Created by 723139 on 19/12/2019.
//

#ifndef LAB_111_QUOTAZIONE_GIORNALIERA_H
#define LAB_111_QUOTAZIONE_GIORNALIERA_H

#include "data.h"

typedef struct {
    Data d;
    float q;
    int n;
    float min, max;
} Quotazione;

Quotazione QUOTAZIONEsetNull();
Quotazione QUOTAZIONEinit(float v, int n, Data d);
int QUOTAZIONEconfronto(Quotazione q1, Quotazione q2); //yee
Quotazione QUOTAZIONEelabora(Quotazione q, float v, int n);

#endif //LAB_111_QUOTAZIONE_GIORNALIERA_H
