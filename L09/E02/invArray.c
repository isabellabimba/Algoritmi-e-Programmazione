//
// Created by Isabella Priano on 07/12/2019.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inv.h"
#include "invArray.h"

struct tabInv_t{
    inv_p* vettInv;//Vettore
    int nInv;
    int maxInv;
} tabInv_t;

int getNInv(tabInv_p inventario){
    return inventario->nInv;
}

tabInv_p initTabInv_p(){
    return malloc(sizeof(struct tabInv_t));
   // return malloc(sizeof(tabInv_t));
}

void initVettEquip(tabInv_p  tabInv){
    tabInv->vettInv = (inv_p*)malloc(sizeof(inv_p*) * tabInv->nInv);
    for (int j = 0; j < tabInv->nInv; ++j)
        tabInv->vettInv[j] = initInv_p();
}

void setNInv(tabInv_p inventario, int nInv){
    inventario->nInv = nInv;
}

inv_p getInvByIndice(tabInv_p inventario, int i){
    return inventario->vettInv[i];
}

void leggiFileInventario(tabInv_p tabInv) {

    FILE* fp = fopen(FILE_INVENTARIO, "r");
    if(fp == NULL){
        perror("Errore apertura file:");
        exit(EXIT_FAILURE);
    }
    int nInv;
    fscanf(fp,"%d", &nInv);//lettura numero oggetti
    setNInv(tabInv,nInv);  //allocamento inventario

    initVettEquip(tabInv);
    char nome[MAX_LUNGH_STR], tipo[MAX_LUNGH_STR];
    int hp, mp, atk, def, mag, spr;
    for (int i = 0; i < tabInv->nInv; ++i) {
        fscanf(fp,"%s",nome);   fscanf(fp,"%s", tipo);  fscanf(fp,"%d", &hp);
        fscanf(fp,"%d", &mp);   fscanf(fp,"%d", &atk);  fscanf(fp,"%d", &def);
        fscanf(fp,"%d", &mag);  fscanf(fp,"%d", &spr);
        setOggetto(tabInv->vettInv[i], nome, tipo, hp, mp, atk, def, mag, spr);
    }
    fclose(fp);
}

int trovaOggettoByNome(char nomeOggettoInput[], tabInv_p tabInv ){
    for (int i = 0; i < tabInv->nInv; ++i) {
        if(!strcmp(getNomeOggetto(tabInv->vettInv[i]), nomeOggettoInput))
            return i;
    }return -1;
}

void deallocaInv(tabInv_p tabInv) {
    free(tabInv->vettInv);
    free(tabInv);
}


stat_p initStat(){
    return malloc(sizeof(stat_t));
}

void setHP(stat_p stat, int hp){
    stat->hp = hp;
}

void setMP(stat_p stat, int mp){
    stat->mp = mp;
}

void setATK(stat_p stat, int atk){
    stat->atk = atk;
}

void setDEF(stat_p stat, int def){
    stat->def = def;
}

void setMAG(stat_p stat, int mag){
    stat->mag = mag;
}

void setSPR(stat_p stat, int spr){
    stat->spr = spr;
}

int getHP(stat_p stat){
    return stat->hp;
}

int getMP(stat_p stat){
    return stat->mp;
}

int getATK(stat_p stat){
    return stat->atk;
}

int getDEF(stat_p stat){
    return stat->def;
}

int getMAG(stat_p stat){
    return stat->mag;
}

int getSPR(stat_p stat){
    return stat->spr;
}

void controlloStatisticheMinoriDiZero(stat_p stat) {
    if(stat->hp < 1)    stat->hp  = 1;
    if(stat->mp  < 1)   stat->mp  = 1;
    if(stat->atk < 1)   stat->atk = 1;
    if(stat->def < 1)   stat->def = 1;
    if(stat->mag < 1)   stat->mag = 1;
    if(stat->spr < 1)   stat->spr = 1;
}

void stampaStatistiche(stat_p stat) {
    printf("%d ", stat->hp);    printf("%d ", stat->mp);   printf("%d ", stat->atk);
    printf("%d ", stat->def);   printf("%d ", stat->mag);    printf("%d ", stat->spr);
    printf("\n");
}
