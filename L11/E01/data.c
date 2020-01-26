//
// Created by Isabella Priano on 19/12/2019.
//

#include "data.h"

static int confrontoData(Data d1, Data d2){
    return (d1.min*60+d1.ore+d1.g+d1.m*30+d1.a*365)-(d2.min*60+d2.ore+d2.g+d2.m*30+d2.a*365);
}

int DATAequal(Data d1, Data d2){
    if (confrontoData(d1, d2) == 0) return 1;
    return 0;
}

int DATAgreater(Data d1, Data d2){
    if (confrontoData(d1, d2) < 0)  return 1;
    return 0;
}

int DATAlower(Data d1, Data d2){
    if (confrontoData(d1, d2) > 0)  return 1;
    return 0;
}