//
// Created by Isabella Priano on 04/12/2019.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inventario.h"
#include "personaggi.h"

void stampa_inventario(inv_t inventario){

    printf("%s ", inventario.nome);
    printf("%s ", inventario.tipo);
    stampa_statistiche(inventario.stat);
}

void leggiFileInventario(tabInv_t *tabInv) {

    FILE* fp = fopen("inventario.txt", "r");

    if(fp == NULL){
        perror("Errore apertura file: ");
        exit(EXIT_FAILURE);
    }

    fscanf(fp,"%d", &(tabInv->nInv)); //lettura numero oggetti e allocamento inventario
    tabInv->vettInv = (inv_t*)malloc(sizeof(inv_t) * tabInv->nInv);

    for (int i = 0; i < tabInv->nInv; ++i) {
        fscanf(fp,"%s", tabInv->vettInv[i].nome);
        fscanf(fp,"%s", tabInv->vettInv[i].tipo);
        fscanf(fp,"%d", &tabInv->vettInv[i].stat.hp);
        fscanf(fp,"%d", &tabInv->vettInv[i].stat.mp);
        fscanf(fp,"%d", &tabInv->vettInv[i].stat.atk);
        fscanf(fp,"%d", &tabInv->vettInv[i].stat.def);
        fscanf(fp,"%d", &tabInv->vettInv[i].stat.mag);
        fscanf(fp,"%d", &tabInv->vettInv[i].stat.spr);
    } fclose(fp);
}


int trova_oggetto_nome(char nomeOggettoInput[], tabInv_t *tabInv ){
    for (int i = 0; i < tabInv->nInv; ++i) {
        if(!strcmp(tabInv->vettInv[i].nome, nomeOggettoInput))
            return i;
    }
    return -1;
}

void togli_inv(tabInv_t *tabInv) {
    free(tabInv->vettInv);
    free(tabInv);
}

void ricerca_oggetto(tabInv_t *tabInv){
    char nome[L]; int i;

    printf("Inserisci nome: ");
    scanf("%s", nome);
    for (i = 0; i < tabInv->nInv; ++i) {    if (strcmp(nome, tabInv->vettInv[i].nome) == 0)     break; /* uscita non strutturata */}
    if (i > tabInv->nInv)   printf("Oggetto non trovato\n");
    else                    stampa_oggetti(&tabInv->vettInv[i], 1);
}

void stampa_oggetti(inv_t *o, int n){
    for (int i = 0; i < n; ++i)
        printf("%d) %s %s %d %d %d %d %d %d\n", i+1, o[i].nome, o[i].tipo, o[i].stat.hp, o[i].stat.mp,
               o[i].stat.atk, o[i].stat.def, o[i].stat.mag, o[i].stat.spr);
}