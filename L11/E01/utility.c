//
// Created by Isabella Priano on 19/12/2019.
//
#include <stdlib.h>
#include <stdio.h>
#include "utility.h"

void funzione_inserisci(CollezioneTitoli collezioni){
    char nome[N];
    printf("\nInserire nome file: ");
    scanf("%s", nome);

    FILE *fp; //apertura file
    if((fp = fopen(nome, "r")) == NULL) {
        perror("Errore apertura file!\n");
        exit(EXIT_FAILURE);
    }
    COLLEZIONE_TinsertQuotazioni(collezioni, fp);
}

comandi_t leggiComando(){
    char *comandi[errore] = {
            "acquisizione", "cerca titolo", "quotazione data",
            "quotazioni in intervallo date", "quotazioni massime e minime",
            "bilanciamento albero", "esci"  };

    int cmd;
    for (int i = 0; i < errore; ++i)
        printf("\n%d. %s", i+1, comandi[i]);
    printf("\nInserisci comando[1 - %d]: ", errore);
    scanf("%d", &cmd);
    cmd--;
    comandi_t c = acquisisci;
    while (c < errore && c != cmd)
        c++;
    return c;
}

void elaborazioneComando(comandi_t c, int *flag, CollezioneTitoli collezioni){
    switch (c) {
        case acquisisci:        funzione_inserisci(collezioni);                 break;
        case titolo:            COLLEZIONETsearchTitolo(collezioni);            break;
        case data:              COLLEZIONETsearchQuotazione(collezioni);        break;
        case date:              COLLEZIONETsearchQuotazioneDate(collezioni);    break;
        case massimo:           COLLEZIONETsearchMinMax(collezioni);            break;
        case partizionamento:   COLLEZIONETBilancia(collezioni);                break;
        case esci:              *flag = 0;                                      break;
        case errore:            default:    printf("Errore comando");           break;
    }
}
