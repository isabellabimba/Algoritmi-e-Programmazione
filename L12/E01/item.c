//
// Created by Isabella Priano on 09/01/2020.
//
#include "item.h"

Item ITEMsetnull(){
    Item t;
    t.preso = t.v = t.wt = -1;
    return t;
}

Item ITEMcreate(int v, int wt){
    Item t;
    t.preso = 1;
    t.wt = wt;
    t.v = v;
    return t;
}

