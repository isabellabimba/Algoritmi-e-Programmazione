//
// Created by Isabella Priano on 19/12/2019.
//

#ifndef LAB_111_DATA_H
#define LAB_111_DATA_H

typedef struct { int g, m, a, min; float ore;} Data;

int DATAequal(Data d1, Data d2);
int DATAgreater(Data d1, Data d2);
int DATAlower(Data d1, Data d2);

#endif //LAB_111_DATA_H
