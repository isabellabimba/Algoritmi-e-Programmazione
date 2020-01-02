//
// Created by Isabella Priano on 07/12/2019.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inv.h"

/*struct inv_t{
    char nome[MAX_LUNGH_STR];
    char tipo[MAX_LUNGH_STR];
    stat_p stat;
} inv_t;*/

void stampaOggetto(inv_p inventario){
    printf("%s ", inventario->nome);
    printf("%s ", inventario->tipo);
    printf("\n");
}

char* getNomeOggetto(inv_p inv){
    return inv->nome;
}

void setOggetto(inv_p inv, char* nome, char* tipo, int hp, int mp,int atk,int def,int mag,int spr){
    strcpy(inv->nome,nome); strcpy(inv->tipo,tipo); setHP(inv->stat, hp);
    setMP(inv->stat, mp);   setATK(inv->stat, atk); setDEF(inv->stat, def);
    setMAG(inv->stat, mag); setSPR(inv->stat, spr);
}

inv_p initInv_p(){
    inv_p inv = malloc(sizeof(inv_t));
    inv->stat = initStat();
    return inv;
}

stat_p getStatOggetto(inv_p inv){
    return inv->stat;
}
