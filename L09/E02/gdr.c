#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pg.h"
#include "pgList.h"
#include "invArray.h"

typedef enum{
    c_aggiungiPG, c_eliminaPG, c_aggiungiOggetto, c_rimuoviOggetto, c_calcolaStatistiche, c_cercaPersonaggio, c_fine
} comando;

comando selezionaComando();
void selezionaDati(comando c, tabInv_p tabInv, tabPg_p tabPg);

int main() {
    tabInv_p tabInv;
    tabInv = initTabInv_p(); //riservo mamoria per l'inventario
    leggiFileInventario(tabInv); //carico inventario

    tabPg_p tabPg;
    tabPg = initTabPg_p(); //riservo memoria per i personaggi
    leggiFilePG(tabPg); //carico personaggi

    comando c = c_aggiungiPG;
    while(c != c_fine){
        c = selezionaComando();
        selezionaDati(c, tabInv, tabPg);
    }
    return 0;
}

comando selezionaComando(){
    char tabella[6][50]={"AggiungiPG","EliminaPG","AggiungiOggetto","RimuoviOggetto","CalcolaStatistiche","CercaPersonaggio"};
    char *comandoScelto;
    comandoScelto = calloc(50, sizeof(char));

    printf("Scegli comando: ( AggiungiPG | EliminaPG | AggiungiOggetto | RimuoviOggetto | CalcolaStatistiche | CercaPersonaggio | Fine) : ");
    scanf("%s", comandoScelto);
    comando c = c_aggiungiPG;
    while(c < c_fine && strcmp(comandoScelto,tabella[c]) != 0)
        c++;
    return c;
}

void selezionaDati(comando c, tabInv_p tabInv, tabPg_p tabPg) {
    switch(c){
        case c_aggiungiPG:          aggiungiPG(tabPg);                                  break;
        case c_eliminaPG:           eliminaPG(tabPg);   stampaListaPersonaggi(tabPg);   break;
        case c_aggiungiOggetto:     aggiungiOggettoAPersonaggio(tabPg, tabInv);         break;
        case c_rimuoviOggetto:      rimuoviOggettoAPersonaggio(tabPg);                  break;
        case c_calcolaStatistiche:  calcolaStatistichePersonaggio(tabPg);               break;
        case c_cercaPersonaggio:    funzione_ricerca_p(tabPg);                          break;
  //      case c_cercaOggetto:        ricerca_oggetto(tabInv);                            break;
        case c_fine:                deallocaPG(tabPg);  deallocaInv(tabInv);            break;
    }
}
