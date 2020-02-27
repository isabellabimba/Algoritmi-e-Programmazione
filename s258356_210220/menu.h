//
// Created by Isabella Priano on 22/02/2020.
//

#ifndef ESAME99_MENU_H
#define ESAME99_MENU_H

#define N 100
#define nomefile "piatti.txt"

typedef struct menu *Piattini;
typedef struct piatti *EP;

struct piatti{
    char nome[N];
    char tipo1[N];
    char tipo2[N];
    float prezzo;
};

struct menu{
    int *vett_piatti;  //cambiato dal compito per errata lettura
    float prezzo_tot;
};

void crea_menu();
void crea_piccoli_menu(int k, int n, EP ElencoPt);
void somma_prezzo();

#endif //ESAME99_MENU_H
