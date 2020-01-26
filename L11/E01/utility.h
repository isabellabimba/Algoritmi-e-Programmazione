//
// Created by Isabella Priano on 19/12/2019.
//

#ifndef LAB_111_UTILITY_H
#define LAB_111_UTILITY_H

#include "collezione_titoli.h"
#define N 20+1

typedef enum {
    acquisisci, titolo, data, date, massimo, partizionamento, esci, errore
} comandi_t;

void funzione_inserisci(CollezioneTitoli collezioni);
comandi_t leggiComando();
void elaborazioneComando(comandi_t c, int *flag, CollezioneTitoli collezioni);

#endif //LAB_111_UTILITY_H
