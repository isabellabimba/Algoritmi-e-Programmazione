//
// Created by Isabella Priano on 07/12/2019.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pgList.h"
#include "inv.h"
#include "pg.h"
#include "equipArray.h"
#include "invArray.h"

#define MAX_OGGETTI_INVENTARIO 8

typedef struct nodo* link;

struct nodo {
    pg_p pg;
    link next;
} nodo_s;

struct tabPg_t {
    link headPg;
    link tailPg;
    int nPg;
} tabPg_t;

tabPg_p initTabPg_p(){
    return malloc(sizeof(tabPg_t));
}

void deallocaPG(tabPg_p tabPg) {
    link t, p;
    if (tabPg->headPg == NULL)
        return;
    for (t = tabPg->headPg->next, p = tabPg->headPg; t != NULL; p = t, t = t->next) {
        free(getVettEquip(getEquipPG(p->pg)));
        free(p);
    }   free(tabPg);
}

void calcolaStatistichePersonaggio(tabPg_p tabPg) {
    link Pg = trovaPgByCodice(tabPg);
    if(Pg == NULL){
        printf("PG non trovato\n");
        return;
    }
    stat_p stat_tmp = getPgStat(Pg->pg);
    for (int i = 0; i < getEquipInUso(getEquipPG(Pg->pg)); ++i) { //scorro gli oggetti nell'int del pg e calc stat
        setHP(stat_tmp, getHP(getPgStat(Pg->pg)) + getHP(getStatOggetto(getEquipByIndice(getEquipPG(Pg->pg),i))));
        setMP(stat_tmp, getMP(getPgStat(Pg->pg)) + getMP(getStatOggetto(getEquipByIndice(getEquipPG(Pg->pg),i))));
        setATK(stat_tmp, getATK(getPgStat(Pg->pg)) + getATK(getStatOggetto(getEquipByIndice(getEquipPG(Pg->pg),i))));
        setDEF(stat_tmp, getDEF(getPgStat(Pg->pg)) + getDEF(getStatOggetto(getEquipByIndice(getEquipPG(Pg->pg),i))));
        setMAG(stat_tmp, getMAG(getPgStat(Pg->pg)) + getMAG(getStatOggetto(getEquipByIndice(getEquipPG(Pg->pg),i))));
        setSPR(stat_tmp, getSPR(getPgStat(Pg->pg)) + getSPR(getStatOggetto(getEquipByIndice(getEquipPG(Pg->pg),i))));
    }
    controlloStatisticheMinoriDiZero(stat_tmp); //se le stat sono min di 1 le metto a 0
    stampaStatistiche(stat_tmp);
}

void rimuoviOggettoAPersonaggio(tabPg_p tabPg) {
    char nomeOggettoInput[MAX_LUNGH_STR];
    link Pg = trovaPgByCodice(tabPg);
    if(Pg == NULL){
        printf("PG non trovato\n");
        return;
    }

    printf("INVENTARIO DEL PERSONAGGIO: \n");
    int i;
    for (i = 0; i < getEquipInUso(getEquipPG(Pg->pg)); ++i) {
        //stampaOggetto(*Pg->pg.equip.vettEq[i]);//DA QUI
        stampaOggetto(getEquipByIndice(getEquipPG(Pg->pg),i));//DA QUI
    }
    printf("Inserire nome oggetto da rimuovere: ");
    scanf("%s", nomeOggettoInput);
    int equipInUso = getEquipInUso(getEquipPG(Pg->pg));

    for (i = 0; i < equipInUso; i++) {
        if(!strcmp(getNomeOggetto(getEquipByIndice(getEquipPG(Pg->pg),i)),nomeOggettoInput )){ //cerco l'oggetto
            for (int j = i; j < equipInUso - 1; ++j) { //se lo trovo, traslo tutto il vettore di uno all'indietro
                //Pg->pg.equip.vettEq[j] = Pg->pg.equip.vettEq[j +1];
                setEquipByIndice(getEquipPG(Pg->pg),getEquipByIndice(getEquipPG(Pg->pg),j+1),j);
            }
            setEquipInUso(getEquipPG(Pg->pg),equipInUso - 1); //diminuisco numero di oggetti
            printf("Oggetto rimosso\n");
            return;
        }
    }   printf("Oggetto non trovato\n");
}

void aggiungiOggettoAPersonaggio(tabPg_p tabPg, tabInv_p tabInv) {
    char nomeOggettoInput[MAX_LUNGH_STR];
    for (int i = 0; i < getNInv(tabInv); ++i) { //stampo tutti gli oggetti per aiutare l'utente
        //stampaOggetto(tabInv->vettInv[i]);
        stampaOggetto(getInvByIndice(tabInv,i));
    }
    printf("Inserire nome oggetto da aggiungere a un personaggio: ");
    scanf("%s", nomeOggettoInput);
    int indiceOggetto = trovaOggettoByNome(nomeOggettoInput, tabInv);
    if(indiceOggetto == -1){
        printf("Oggetto non trovato\n");
        return;
    }
    link Pg = trovaPgByCodice(tabPg);
    if(Pg == NULL){
        printf("PG non trovato\n");
        return;
    }
    if(getEquipInUso(getEquipPG(Pg->pg)) == MAX_OGGETTI_INVENTARIO){
        printf("Il personaggio ha lo zaino pieno!");
        return;
    }
    //aggiungo inv scelto al vettore di inventari del pg
    setEquipByIndice(getEquipPG(Pg->pg), getInvByIndice(tabInv,indiceOggetto), getEquipInUso(getEquipPG(Pg->pg)));
    setEquipInUso(getEquipPG(Pg->pg),getEquipInUso(getEquipPG(Pg->pg)) + 1);
    printf("Oggetto %s aggiunto a personaggio %s \n", nomeOggettoInput, getCodicePG(Pg->pg));
}

link trovaPgByCodice(tabPg_p tabPg){
    char codicePGInput[MAX_LUNGH_CODICE];
    printf("\nInserire codice PG : ");
    scanf("%s", codicePGInput);

    if(tabPg->headPg == NULL)
        return NULL;
    link t;
    for (t = tabPg->headPg; t != NULL;t = t->next) { //ciclo per trovare pg con codice in input
        if (!strcmp(getCodicePG(t->pg), codicePGInput)) {
            return t;
        }
    }return NULL;
}

void eliminaPG(tabPg_p tabPg) {
    char codiceInput[MAX_LUNGH_CODICE];
    printf("Inserire codice di personaggio che vuoi eliminare: ");
    scanf("%s", codiceInput);
    link t, prec; //ciclo per trovare pg con il codice in input
    for (t = tabPg->headPg, prec = NULL; t != NULL; prec = t, t = t->next) {
        if (!strcmp(getCodicePG(t->pg), codiceInput)) {
            prec->next = t->next; //cancello nodo
            free(t);
            printf("Personaggio eliminato\n");
            return;
        }
    }   printf("Personaggio non trovato\n");
}

void aggiungiPG(tabPg_p tabPg){
    char codice[MAX_LUNGH_CODICE], nome[MAX_LUNGH_STR],classe[MAX_LUNGH_STR];
    int hp, mp, atk, def, mag, spr;
    printf("Inserire codice:\t");       scanf("%s", codice);
    printf("Inserire nome:  \t");       scanf("%s", nome);
    printf("Inserire classe:\t");       scanf("%s", classe);
    printf("Inserire hp:    \t");       scanf("%d", &hp);
    printf("Inserire mp:    \t");       scanf("%d", &mp);
    printf("Inserire atk:   \t");       scanf("%d", &atk);
    printf("Inserire def:   \t");       scanf("%d", &def);
    printf("Inserire mag:   \t");       scanf("%d", &mag);
    printf("Inserire spr:   \t");       scanf("%d", &spr);

    pg_p personaggio = initPersonaggio();
    setPersonaggio(&personaggio,codice,nome,classe,hp,mp,atk,def,mag,spr);
    setEquipPG(&personaggio,initTabEquip());
    setEquipInUso(getEquipPG(personaggio),0);
    initVettEq(getEquipPG(personaggio),MAX_OGGETTI_INVENTARIO);
    //personaggio.equip.vettEq = (inv_t **) malloc(sizeof(inv_t *) * nInv);
    newNodePersonaggio(tabPg, personaggio);
    tabPg->tailPg->next = NULL;
    printf("Personaggio aggiunto!\n");
}

void leggiFilePG(tabPg_p tabPg) {

    tabPg->headPg = NULL;   tabPg->tailPg = NULL;   tabPg->nPg = 0;
    FILE *fp = fopen("pg.txt", "r");

    if (fp == NULL) {
        perror("Errore apertura file:");
        exit(EXIT_FAILURE);
    }
    pg_p personaggio_tmp = NULL;
    char codice[MAX_LUNGH_CODICE];
    char nome[MAX_LUNGH_STR];
    char classe[MAX_LUNGH_STR];
    int hp, mp, atk, def, mag, spr;

    while (fscanf(fp, "%s%s%s%d%d%d%d%d%d", codice, nome, classe, &hp, &mp, &atk, &def, &mag, &spr) != EOF) {
        setPersonaggio(&personaggio_tmp,codice,nome,classe,hp,mp,atk,def,mag,spr);
        setEquipPG(&personaggio_tmp,initTabEquip());
 //       tabEquip_p eq = getEquipPG(personaggio_tmp);
        setEquipInUso(getEquipPG(personaggio_tmp),0);
        initVettEq(getEquipPG(personaggio_tmp),MAX_OGGETTI_INVENTARIO);
        newNodePersonaggio(tabPg, personaggio_tmp);
    }
    tabPg->tailPg->next = NULL;//Faccio puntare ultimo inserito a NULL
    stampaListaPersonaggi(tabPg);
    //printf("%s\n\n\n",tabPg->headPg->pg.classe);
    fclose(fp);
}

void stampaListaPersonaggi(tabPg_p tabPg){
    link t;
    for(t = tabPg->headPg; t != NULL;t = t->next)   stampaPersonaggio(t->pg);
}

void funzione_ricerca_p(tabPg_p tabPg){
    char codice[50];
    printf("Codice PG:");
    scanf("%s", codice);
    pg_p *pgp;
    pgp = cercaPG(tabPg, codice);
    if(pgp != NULL) pg_print(*pgp);
}

pg_p *cercaPG(tabPg_p pgList, char *cod){
    link pp = NULL;
    if(pgList == NULL) return NULL;
    for(pp = pgList->headPg; pp != NULL; pp = pp->next){
        if(strcmp(pp -> pg->codice, cod) == 0) return (&pp->pg);
    }  return NULL;
}

void pg_print(pg_p pgp){
    if(pgp != NULL)
    printf("%s => %s [%s]\n", pgp->codice, pgp->nome, pgp->classe);
}

void newNodePersonaggio(tabPg_p tabPg, pg_p personaggio) {
    if(tabPg->headPg == NULL){ //inserisco primo elemento
        tabPg->headPg = (link)malloc(sizeof(nodo_s));
        tabPg->headPg->pg = personaggio;
        return;
    }
    if(tabPg->tailPg == NULL){ //inserisco secondo elemento
        tabPg->tailPg = (link)malloc(sizeof(nodo_s));
        tabPg->tailPg->pg = personaggio;
        tabPg->headPg->next = tabPg->tailPg;
        return;
    }
    tabPg->tailPg->next = (link)malloc(sizeof(nodo_s)); //creo nuovo elemento e aggiorno coda
    tabPg->tailPg->next->pg = personaggio;
    tabPg->tailPg = tabPg->tailPg->next;
};

