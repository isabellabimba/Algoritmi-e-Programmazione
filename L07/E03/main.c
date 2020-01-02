#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LUNGH_STR 50
#define MAX_LUNGH_CODICE 7
#define MAX_OGGETTI_INVENTARIO 8

typedef struct{
    int hp, mp, atk, def, mag, spr;
}stat_t;

typedef struct{
    char nome[MAX_LUNGH_STR];
    char tipo[MAX_LUNGH_STR];
    stat_t stat;
}inv_t;

typedef struct{
    inv_t* vettInv; //vettore
    int nInv;
    int maxInv;
}tabInv_t;

typedef struct{
    int inUso;
    inv_t** vettEq; //vettore di puntatori a inv_t
}tabEquip_t;

typedef struct{
    char codice[MAX_LUNGH_CODICE];
    char nome[MAX_LUNGH_STR];
    char classe[MAX_LUNGH_STR];
    tabEquip_t equip;
    stat_t stat;
}pg_t;

typedef struct nodo{
    pg_t pg;
    struct nodo* next;
}nodoPg_t, *link;

typedef struct {
    link headPg;
    link tailPg;
    int nPg;
}tabPg_t;

typedef enum{
    c_aggiungiPG, c_eliminaPG, c_aggiungiOggetto, c_rimuoviOggetto, c_calcolaStatistiche, c_fine
}comando;
//prototipi
void carica_file_PG(tabPg_t* tabPg, int nInv);
void fa_vedere(pg_t personaggio); //stampa i personaggi
void nuovo_personaggio(tabPg_t *tabPg, pg_t personaggio);
void carica_file_inventario(tabInv_t *tabInv);
comando seleziona_comando();
void aggiungi_PG(tabPg_t *tabPg);
void stampa_lista_personaggi(tabPg_t* tabPg);
void seleziona_dati(comando c, tabInv_t *tabInv, tabPg_t *tabPg);
int trova_oggetto_nome(char nomeOggettoInput[], tabInv_t *tabInv );
link trova_Pg_codice(tabPg_t *tabPg);
void elimina_PG(tabPg_t *tabPg);
void stampa_inventario(inv_t inventario);
void aggiungi_oggetto_personaggio(tabPg_t *tabPg, tabInv_t *tabInv);
void rimuovi_oggetto_personaggio(tabPg_t *tabPg);
void calcola_statistiche_personaggio(tabPg_t *tabPg);
void stampa_statistiche(stat_t stat);
void controllo_statistiche_piccole(stat_t *stat);
void togli_PG(tabPg_t *tabPg);
void togli_inv(tabInv_t *tabInv);
void poche_istruzioni();

int main() {
    poche_istruzioni();
    return 0;
}

void poche_istruzioni(){
    tabInv_t* tabInv;   //carico inventario
    tabInv = (tabInv_t*)malloc(sizeof(tabInv_t));
    carica_file_inventario(tabInv);
    tabPg_t *tabPg;     //carico personaggi
    tabPg = (tabPg_t*)malloc(sizeof(tabPg_t));
    carica_file_PG(tabPg, tabInv->nInv);

    comando c = c_aggiungiPG;
    while(c != c_fine){
        c = seleziona_comando();
        seleziona_dati(c, tabInv, tabPg);   }
}

void seleziona_dati(comando c, tabInv_t *tabInv, tabPg_t *tabPg) {
    switch(c)
    {   case c_aggiungiPG:  aggiungi_PG(tabPg);                                 break;
        case c_eliminaPG:   elimina_PG(tabPg);  stampa_lista_personaggi(tabPg); break;
        case c_aggiungiOggetto: aggiungi_oggetto_personaggio(tabPg, tabInv);    break;
        case c_rimuoviOggetto:  rimuovi_oggetto_personaggio(tabPg);             break;
        case c_calcolaStatistiche:  calcola_statistiche_personaggio(tabPg);     break;
        case c_fine:    togli_PG(tabPg);    togli_inv(tabInv);                  break;  }
}

void togli_inv(tabInv_t *tabInv) {
    free(tabInv->vettInv);  free(tabInv);
}

void togli_PG(tabPg_t *tabPg) {
    link t, p;
    if (tabPg->headPg == NULL)  return;
    for (t = tabPg->headPg->next, p = tabPg->headPg; t != NULL; p = t, t = t->next) {
        free(p->pg.equip.vettEq);   free(p);    }   free(tabPg);
}

void calcola_statistiche_personaggio(tabPg_t *tabPg) {
    link Pg = trova_Pg_codice(tabPg);
    if(Pg == NULL){ printf("PG non trovato\n"); return; }
    stat_t stat_tmp = Pg->pg.stat;
    for (int i = 0; i < Pg->pg.equip.inUso; ++i)  //scorro gli oggetti nell'inventario del personaggio e faccio le statistiche finali
    {   stat_tmp.hp += Pg->pg.equip.vettEq[i]->stat.hp;
        stat_tmp.mp += Pg->pg.equip.vettEq[i]->stat.mp;
        stat_tmp.atk += Pg->pg.equip.vettEq[i]->stat.atk;
        stat_tmp.def += Pg->pg.equip.vettEq[i]->stat.def;
        stat_tmp.mag += Pg->pg.equip.vettEq[i]->stat.mag;
        stat_tmp.spr += Pg->pg.equip.vettEq[i]->stat.spr;   }
    controllo_statistiche_piccole(&stat_tmp); //se le statistiche sono <0 azzero
    stampa_statistiche(stat_tmp);             //quindi le stampo
}

void controllo_statistiche_piccole(stat_t *stat) {
    if(stat->hp < 1)    stat->hp  = 1;
    if(stat->mp  < 1)   stat->mp  = 1;
    if(stat->atk < 1)   stat->atk = 1;
    if(stat->def < 1)   stat->def = 1;
    if(stat->mag < 1)   stat->mag = 1;
    if(stat->spr < 1)   stat->spr = 1;
}

void stampa_statistiche(stat_t stat) {
    printf("%d ", stat.hp);     printf("%d ", stat.atk);    printf("%d ", stat.def);
    printf("%d ", stat.mag);    printf("%d ", stat.mp);     printf("%d ", stat.spr);
    printf("\n");
}

void rimuovi_oggetto_personaggio(tabPg_t *tabPg) {
    char nomeOggettoInput[MAX_LUNGH_STR];

    link Pg = trova_Pg_codice(tabPg);
    if(Pg == NULL){ printf("PG non trovato\n");     return;}
    printf("Inventario del personaggio: \n");
    for (int i = 0; i < Pg->pg.equip.inUso; ++i)    stampa_inventario(*Pg->pg.equip.vettEq[i]);
    printf("Inserire nome oggetto da rimuovere: "); scanf("%s", nomeOggettoInput);

    int j; j=0;
    for (int i = 0; i < Pg->pg.equip.inUso; i++) {
        if(!strcmp(Pg->pg.equip.vettEq[i]->nome,nomeOggettoInput )) //Cerco l'oggetto
        {   //Se lo trovo, traslo tutto il vettore di uno all'indietro
            for (j = i; j < Pg->pg.equip.inUso - 1; ++j)    Pg->pg.equip.vettEq[j] = Pg->pg.equip.vettEq[j +1];
            Pg->pg.equip.inUso--; //Diminuisco numero di oggetti
            printf("Oggetto rimosso\n");    return; }
        } printf("Oggetto non trovato\n");
}

void aggiungi_oggetto_personaggio(tabPg_t *tabPg, tabInv_t *tabInv) {
    char nomeOggettoInput[MAX_LUNGH_STR];

    for (int i = 0; i < tabInv->nInv; ++i)  stampa_inventario(tabInv->vettInv[i]); //stampo tutto per aiutare i giocatori
    printf("Inserire nome oggetto da aggiungere a un personaggio: ");   scanf("%s", nomeOggettoInput);

    int indiceOggetto = trova_oggetto_nome(nomeOggettoInput, tabInv);
    if(indiceOggetto == -1){    printf("Oggetto non trovato\n");    return; }
    link Pg = trova_Pg_codice(tabPg);
    if(Pg == NULL){             printf("PG non trovato\n");         return; }
    if(Pg->pg.equip.inUso == MAX_OGGETTI_INVENTARIO){
        printf("Il personaggio ha il numero massimo di oggetti!");  return; }
    Pg->pg.equip.vettEq[Pg->pg.equip.inUso++] = &tabInv->vettInv[indiceOggetto]; //aggiungo inventario al vettore inv pg
    printf("Oggetto %s aggiunto a personaggio %s", nomeOggettoInput, Pg->pg.codice);
}

link trova_Pg_codice(tabPg_t *tabPg){
    char codicePGInput[MAX_LUNGH_CODICE];

    printf("Inserire codice PG:\n"); scanf("%s", codicePGInput);

    if(tabPg->headPg == NULL)   return NULL;
    link t;
    for (t = tabPg->headPg; t != NULL;t = t->next) //trovo il Pg con il codice cercato
    {   if (!strcmp(t->pg.codice, codicePGInput))   return t;   }   return NULL;
}

int trova_oggetto_nome(char nomeOggettoInput[], tabInv_t *tabInv ){
    for (int i = 0; i < tabInv->nInv; ++i) {
        if(!strcmp(tabInv->vettInv[i].nome, nomeOggettoInput))  return i;
    }   return -1;
}

void elimina_PG(tabPg_t *tabPg) {
    char codice_input[MAX_LUNGH_CODICE];
    printf("Inserire codice di personaggio che vuoi eliminare: ");
    scanf("%s", codice_input);

    link t, prec;
    for (t = tabPg->headPg, prec = NULL; t != NULL; prec = t, t = t->next) //trovo Pg inserito
    {   if (!strcmp(t->pg.codice, codice_input))
        {   prec->next = t->next; //cancello un nodo
            free(t);
            printf("Personaggio eliminato\n");
            return; }
    }   printf("Personaggio non trovato\n");
}

void aggiungi_PG(tabPg_t *tabPg){
    pg_t personaggio;
    printf("Inserire codice: ");    scanf("%s", personaggio.codice);
    printf("Inserire nome: ");      scanf("%s", personaggio.nome);
    printf("Inserire classe: ");    scanf("%s", personaggio.classe);
    printf("Inserire hp: ");        scanf("%d", &personaggio.stat.hp);
    printf("Inserire mp: ");        scanf("%d", &personaggio.stat.mp);
    printf("Inserire atk: ");       scanf("%d", &personaggio.stat.atk);
    printf("Inserire def: ");       scanf("%d", &personaggio.stat.def);
    printf("Inserire mag: ");       scanf("%d", &personaggio.stat.mag);
    printf("Inserire spr: ");       scanf("%d", &personaggio.stat.spr);

    personaggio.equip.inUso = 0;//Inizializzo equipaggiamenti in uso a zero
    personaggio.equip.vettEq = (inv_t **) malloc(sizeof(inv_t *) * MAX_OGGETTI_INVENTARIO);
    nuovo_personaggio(tabPg, personaggio);
    tabPg->tailPg->next = NULL;
    printf("Personaggio aggiunto con successo!\n");
    printf("READY TO PLAY! ;)\n");
}

comando seleziona_comando(){
    char tabella[5][50]={"aggiungi_PG","elimina_PG","aggiungi_oggetto","rimuovi_oggetto","calcola_statistiche"};
    char comando_scelto[50];

    printf("Scegli comando: ( aggiungi_PG | elimina_PG | aggiungi_oggetto | rimuovi_oggetto | calcola_statistiche | Fine) : ");
    scanf("%s", comando_scelto);
    comando c = c_aggiungiPG;
    while(c < c_fine && strcmp(comando_scelto,tabella[c]))  c++;
    return c;
}

void carica_file_inventario(tabInv_t *tabInv) {
    FILE* fp = fopen("inventario.txt", "r");
    if(fp == NULL){
        perror("Errore apertura file\n");
        exit(EXIT_FAILURE); }
    fscanf(fp,"%d", &(tabInv->nInv));   //prendo n oggetti e metto a posto l'inventario

    tabInv->vettInv = (inv_t*)malloc(sizeof(inv_t) * tabInv->nInv);
    for (int i = 0; i < tabInv->nInv; ++i)
    {   fscanf(fp,"%s", tabInv->vettInv[i].nome);
        fscanf(fp,"%s", tabInv->vettInv[i].tipo);
        fscanf(fp,"%d", &tabInv->vettInv[i].stat.hp);
        fscanf(fp,"%d", &tabInv->vettInv[i].stat.mp);
        fscanf(fp,"%d", &tabInv->vettInv[i].stat.atk);
        fscanf(fp,"%d", &tabInv->vettInv[i].stat.def);
        fscanf(fp,"%d", &tabInv->vettInv[i].stat.mag);
        fscanf(fp,"%d", &tabInv->vettInv[i].stat.spr);
    }   fclose(fp);
}

void carica_file_PG(tabPg_t* tabPg, int nInv) {
    tabPg->headPg = NULL;
    tabPg->tailPg = NULL;
    tabPg->nPg = 0;
    FILE *fp = fopen("pg.txt", "r");
    if (fp == NULL) {
        perror("Errore apertura file\n");
        exit(EXIT_FAILURE); }
    pg_t personaggio_tmp; //temporaneo

    while (fscanf(fp, "%s %s %s %d %d %d %d %d %d", personaggio_tmp.codice, personaggio_tmp.nome,
                  personaggio_tmp.classe, &personaggio_tmp.stat.hp, &personaggio_tmp.stat.mp, &personaggio_tmp.stat.atk,
                  &personaggio_tmp.stat.def, &personaggio_tmp.stat.mag, &personaggio_tmp.stat.spr) != EOF)
    {   personaggio_tmp.equip.inUso = 0;//Inizializzo equipaggiamenti in uso a zero
        personaggio_tmp.equip.vettEq = (inv_t **) malloc(sizeof(inv_t *) * nInv);
        nuovo_personaggio(tabPg, personaggio_tmp);
    }   tabPg->tailPg->next = NULL;//Faccio puntare ultimo inserito a NULL
    stampa_lista_personaggi(tabPg);
    fclose(fp);
}

void stampa_lista_personaggi(tabPg_t* tabPg){
    link t;
    for(t = tabPg->headPg; t != NULL;t = t->next){
        fa_vedere(t->pg); //stampa singolo personaggio per creare poi la "lista" dei personaggi
    }
}

void stampa_inventario(inv_t inventario){
    printf("%s ", inventario.nome);
    printf("%s ", inventario.tipo);
    stampa_statistiche(inventario.stat);
}

void fa_vedere(pg_t personaggio){
    printf("%s ", personaggio.codice);  printf("%s ", personaggio.nome);    printf("%s ", personaggio.classe);
    stampa_statistiche(personaggio.stat);
}

void nuovo_personaggio(tabPg_t *tabPg, pg_t personaggio) {
    if(tabPg->headPg == NULL){ //inserire il primo elemento
        tabPg->headPg = (link)malloc(sizeof(nodoPg_t));
        tabPg->headPg->pg = personaggio;
        return; }
    if(tabPg->tailPg == NULL) //inserisco secondo elemento
    {   tabPg->tailPg = (link)malloc(sizeof(nodoPg_t));
        tabPg->tailPg->pg = personaggio;
        tabPg->headPg->next = tabPg->tailPg;
        return; }
    //crea nuovo elemento e aggiorno la coda
    tabPg->tailPg->next = (link)malloc(sizeof(nodoPg_t));
    tabPg->tailPg->next->pg = personaggio;
    tabPg->tailPg = tabPg->tailPg->next;
}