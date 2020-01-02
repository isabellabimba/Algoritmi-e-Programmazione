//
// Created by Isabella Priano on 07/12/2019.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pg.h"
#include "equipArray.h"

pg_p initPersonaggio(){
    pg_p pg = malloc(sizeof(pg_t));
    pg->stat = initStat();
    return pg;
}

void setPersonaggio(pg_p* pg,char* codice, char* nome, char* classe, int hp, int mp,int atk,int def,int mag,int spr){
    *pg = initPersonaggio();
    strcpy((*pg)->codice,codice);    strcpy((*pg)->nome,nome);    strcpy((*pg)->classe,classe);
    setHP((*pg)->stat, hp);          setMP((*pg)->stat, mp);      setATK((*pg)->stat, atk);
    setDEF((*pg)->stat, def);        setMAG((*pg)->stat, mag);    setSPR((*pg)->stat, spr);
}

void stampaPersonaggio(pg_p personaggio){
    printf("%s ", personaggio->codice);     printf("%s ", personaggio->nome);
    printf("%s ", personaggio->classe);    stampaStatistiche(personaggio->stat);
}

stat_p getPgStat(pg_p pg){
    return pg->stat;
}

tabEquip_p getEquipPG(pg_p pg){
    return pg->equip;
}

void setEquipPG(pg_p* pg, tabEquip_p equip){
    (*pg)->equip = equip;
}

char* getCodicePG(pg_p pg){
    return pg->codice;
}
