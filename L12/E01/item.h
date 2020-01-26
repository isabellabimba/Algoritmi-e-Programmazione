//
// Created by Isabella Priano on 09/01/2020.
//

#ifndef LAB_121_ITEM_H
#define LAB_121_ITEM_H

typedef struct {
    int v;
    int wt;
    int preso; //rimozione archi nella ricerca del DAG (tipo tmp)
} Item;

Item ITEMsetnull();
Item ITEMcreate(int v, int wt);

#endif //LAB_121_ITEM_H
