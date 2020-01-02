#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "personaggi.h"
#include "inventario.h"

typedef enum{
    c_aggiungiPG, c_eliminaPG, c_aggiungiOggetto, c_rimuoviOggetto, c_calcolaStatistiche, c_cercaPersonaggio, c_cercaOggetto, c_fine
}comando;
comando scegli1();
void scegli2(comando c, tabInv_t *tabInv, tabPg_t *tabPg);

int main() {
    tabInv_t* tabInv;
    tabInv = (tabInv_t*)malloc(sizeof(tabInv_t));
    leggiFileInventario(tabInv); //carico inventario

    tabPg_t *tabPg;
    tabPg = (tabPg_t*)malloc(sizeof(tabPg_t));
    carica_file_PG(tabPg, tabInv->nInv); //carico personaggi

    comando c = c_aggiungiPG;
    while(c != c_fine){
        c = scegli1();
        scegli2(c, tabInv, tabPg);
    }
    return 0;
}

comando scegli1(){
    char tabella[7][50]={"AggiungiPG","EliminaPG","AggiungiOggetto","RimuoviOggetto","CalcolaStatistiche","CercaPersonaggio","CercaOggetto"};

    char comandoScelto[50];
    printf("Scegli comando: ( AggiungiPG | EliminaPG | AggiungiOggetto | RimuoviOggetto | CalcolaStatistiche | CercaPersonaggio | CercaOggetto | Fine) : ");
    scanf("%s", comandoScelto);
    comando c = c_aggiungiPG;
    while(c < c_fine && strcmp(comandoScelto,tabella[c]))   c++;
    return c;
}


void scegli2(comando c, tabInv_t *tabInv, tabPg_t *tabPg) {
    switch(c){
        case c_aggiungiPG:          aggiungi_PG(tabPg ,tabInv->nInv);                       break;
        case c_eliminaPG:           elimina_PG(tabPg);  stampa_lista_personaggi(tabPg);     break;
        case c_aggiungiOggetto:     aggiungi_oggetto_personaggio(tabPg, tabInv);            break;
        case c_rimuoviOggetto:      rimuovi_oggetto_personaggio(tabPg);                     break;
        case c_calcolaStatistiche:  calcola_statistiche_personaggio(tabPg);                 break;
        case c_cercaPersonaggio:    funzione_ricerca_p(tabPg);                              break;
        case c_cercaOggetto:        ricerca_oggetto(tabInv);                                break;
        case c_fine:                togli_PG( tabPg);   togli_inv(tabInv);                  break;  }
}