//
// Created by Isabella Priano on 07/12/2019.
//

#ifndef LAB_092_INV_H
#define LAB_092_INV_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LUNGH_STR 50
#define MAX_LUNGH_CODICE 7

struct stat_t{
    int hp;
    int mp;
    int atk;
    int def;
    int mag;
    int spr;
} stat_t;

typedef struct stat_t* stat_p;
struct inv_t{
    char nome[MAX_LUNGH_STR];
    char tipo[MAX_LUNGH_STR];
    stat_p stat;
} inv_t;

typedef struct inv_t* inv_p;

char* getNomeOggetto(inv_p inv);
stat_p getStatOggetto(inv_p inv);

//equivalenti di inv_read e inv_print
void setOggetto(inv_p inv, char* nome, char* tipo, int hp, int mp,int atk,int def,int mag,int spr);
void stampaOggetto(inv_p inventario);
inv_p initInv_p();

//funzioni che servono per le statistiche
stat_p initStat();
void setHP(stat_p stat, int hp);
void setMP(stat_p stat, int mp);
void setATK(stat_p stat, int atk);
void setDEF(stat_p stat, int def);
void setMAG(stat_p stat, int mag);
void setSPR(stat_p stat, int spr);
int getHP(stat_p stat);
int getMP(stat_p stat);
int getATK(stat_p stat);
int getDEF(stat_p stat);
int getMAG(stat_p stat);
int getSPR(stat_p stat);

//equivalenti di stat_read e stat_print
void stampaStatistiche(stat_p stat);
void controlloStatisticheMinoriDiZero(stat_p stat);


#endif //LAB_092_INV_H