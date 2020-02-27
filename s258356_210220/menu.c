//
// Created by Isabella Priano on 22/02/2020.
//

#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "bst.h"



/*struct menu{
    int *vett_piatti;  //cambiato dal compito per errata lettura
    float prezzo_tot;
};*/

void crea_menu(){
     FILE *fp;
     int MAX = 0;    //il P richiesto dal testo
     int utente = 0; //numero piatti che vuole mangiare l'utente

    fp = fopen(nomefile, "r");
    if (fp == NULL) {
        perror("Errore apertura file\n");
        exit(EXIT_FAILURE);
    }

    fscanf(fp, "%d", &MAX);  //prendo il primo numero del file per fare poi iterazione
    struct piatti *ElencoPiatti;
    ElencoPiatti = malloc(MAX * sizeof(struct piatti));
    for(int i=0; i<MAX; i++)
        fscanf(fp, "%s %s %s %f", ElencoPiatti[i].nome, ElencoPiatti[i].tipo1, ElencoPiatti[i].tipo2, &ElencoPiatti[i].prezzo);
    fclose(fp);

    printf("Inserire il numero di piatti: \n");     scanf("%d", &utente);

    crea_piccoli_menu(utente, MAX, ElencoPiatti);
}

void crea_piccoli_menu(int k, int n, struct piatti ElencPt[]){
    int *v, *out;   //vettore indici da combinare, vettore indici combinati
    v = malloc(n * sizeof(*v));
    out = malloc(n * sizeof(*out));
    for(int i=0; i<n; i++)  v[i] = i;

    BST root = NULL;
    root = combina_aux(v, n, k  , out, 0, k  , 0, root, ElencPt);
    root = combina_aux(v, n, k-1, out, 0, k-1, 1, root, ElencPt);

    inorder(root, k, ElencPt);

}


