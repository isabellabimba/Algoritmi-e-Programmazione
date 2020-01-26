//
// Created by Isabella Priano on 19/12/2019.
//

#ifndef LAB_111_COLLEZIONE_TITOLI_H
#define LAB_111_COLLEZIONE_TITOLI_H

#include <stdio.h>
typedef struct collezionetitoli *CollezioneTitoli;
CollezioneTitoli COLLEZIONE_Tinit();
void COLLEZIONE_TinsertQuotazioni(CollezioneTitoli c, FILE *f);
void COLLEZIONETsearchTitolo(CollezioneTitoli c);
void COLLEZIONETsearchQuotazione(CollezioneTitoli c);
void COLLEZIONETsearchQuotazioneDate(CollezioneTitoli c);
void COLLEZIONETsearchMinMax(CollezioneTitoli c);
void COLLEZIONETBilancia(CollezioneTitoli c);

#endif //LAB_111_COLLEZIONE_TITOLI_H
