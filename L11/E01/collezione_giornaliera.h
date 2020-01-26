//
// Created by 723139 on 19/12/2019.
//

#ifndef LAB_111_COLLEZIONE_GIORNALIERA_H
#define LAB_111_COLLEZIONE_GIORNALIERA_H

#include "data.h"

typedef struct collezione *Collezione;

Collezione COLLEZIONE_Qinit();
void COLLEZIONE_Qinsert(Collezione bst, float valore, int numero, Data d);
void COLLEZIONE_QsearchData(Collezione bst);
void COLLEZIONE_QsearchIntervallDate(Collezione bst);
void COLLEZIONEsearchMinMax(Collezione bst);
void COLLEZIONEpartition(Collezione bst);

#endif //LAB_111_COLLEZIONE_GIORNALIERA_H
