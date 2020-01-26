//
// Created by Isabella Priano on 16/12/2019.
//

#ifndef LAB_103_ISTRUZIONI_H
#define LAB_103_ISTRUZIONI_H

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "diagonali.h"
#define DIFFICOLTA 8

void apri_file(FILE **fp, char *nome);
void swap(Item_t *d, int i, int j);
void sort(Item_t *d, int n);
void stampa(Item_t *p, diagonale_t *d, int n, int DD, int DP);
void errore(int j, int cnt, int n, int ss);
int condition(int diff, int i, int DP, int diff_min, int f2, int min_in, int min_a, int frontale, Item_t p, int  pos);
int sequenza(Item_t p1, Item_t p2, int j, int *f);
int indice(int i, int *av, int *in, int *ac, int j);
int start_condition(int i_frontali, int i_spalle, Item_t p, int DD, int diff_frontale, int min, int j);
int prova_indietro (int f, int j, Item_t p);
int prova_avanti (int f, int j, Item_t p);
void wrapper_powerset(Item_wrappper p, int n);

#endif //LAB_103_ISTRUZIONI_H
