//
// Created by Isabella Priano on 16/12/2019.
//

#include <stdio.h>
#include <stdlib.h>
#include "istruzioni.h"
#include "diagonali.h"

// valore moltiplicatore
const float MOLTIPLICATORE = 1.5;

void apri_file(FILE **fp, char *nome){
    *fp = NULL;
    *fp = fopen(nome, "r");
    if (*fp == NULL) {
        perror("Errore lettura file!");
        printf("Magari non hai scritto il .txt di fianco al .exe\n");
        exit(EXIT_FAILURE);
    }
}

void swap(Item_t *d, int i, int j){
    Item_t app;
    app = d[i];     d[i] = d[j];    d[j] = app;
}

void sort(Item_t *d, int n){
    for (int i = 0; i < n -1; ++i)
        for (int j = i+1; j < n; ++j)
            if (d[i].valore < d[j].valore)
                swap(d, i, j);
}

void stampa(Item_t *p, diagonale_t *d, int n, int DD, int DP){
    float punti = 0;
    for (int i = n-1; i >= 0; i--) {
        punti += d[i].valore_tot;
        if (i == n - 1 && d[i].bonus)
            punti *= MOLTIPLICATORE;
    }
    printf("DD = %2d DP = %2d\nTOT = %5.3f\n", DD, DP, punti);
    for (int i = 0; i < n; i++) {
        printf("DIAG #%d > %5.3f (%d)", i+1, d[i].valore_tot, d[i].difficolta_tot);
        if (i == n-1 && d[i].bonus)
            printf("* %2.2f (BONUS)", MOLTIPLICATORE);
        printf("\n");
        for (int j = 0; j < d[i].n; j++)
            printf("%s ", p[d[i].elem[j]].nome);
        printf("\n");
    }
}

void errore(int j, int cnt, int n, int ss){
    if (ss >= n) {
        printf("Impossibile creare la combinazionde delle diagonali\n");
        exit(-1);
    }
    if (j == 2 && ss >= cnt) {
        printf("Impossibile creare la combinazione di diagonali con una sequenza!\n");
        exit(-2);
    }
}

int condition(int diff, int i, int DP, int diff_min, int f2, int min_in, int min_a, int frontale, Item_t p, int  pos){
    if (diff > DP)                                                          return 0;
    if (i == 2 && (DP-diff >= (min_a+min_in)))                              return 1;
    if (i == 1) {
        if (pos == 0 && DP-diff >= diff_min+frontale)                       return 1;
        if (pos > 0 && (f2 || ITEMindietro(p))&& DP-diff >= diff_min)       return 1;   }
    if (i == 0 && DP-diff >= 0)                                             return 1;
    return 0;
}

int sequenza(Item_t p1, Item_t p2, int j, int *f) {  //soddisfo questa necessità nella terza riga
    if (*f || j != 2)           return 1;
    if (p2.ingresso == p1.uscita && (ITEMavanti(p2) || ITEMindietro(p2))) {
        *f = 1;                 return 1;   }
    return 0;
}

int indice(int i, int *av, int *in, int *ac, int j){
    if (j == 2)     return ac[i];
    if (j == 1)     return av[i];
    if (j == 0)     return in[i];
}

int start_condition(int i_frontali, int i_spalle, Item_t p, int DD, int diff_frontale, int min, int j){
    if (!ITEMprimo(p))                                      return 0;
    if (j == 0)                                             return 1;
    if (j == 1 && DD-p.difficolta >= diff_frontale+min)     return 1;
    if (j == 2 ) {
        if (p.uscita == spalle)
            if (DD - p.difficolta >= i_spalle)              return 1;
        if (p.uscita == frontale)
            if (DD - p.difficolta >= i_frontali)            return 1;   }
    return 0;
}

int prova_indietro (int f, int j, Item_t p){
    if (f || j != 0)                return 1;
    if (p.tipologia == indietro)    return 1;
    return 0;
}

int prova_avanti (int f, int j, Item_t p){
    if (f || j != 1)              return 1;
    if (p.tipologia == avanti)    return 1;
    return 0;
}

void wrapper_powerset(Item_wrappper p, int n){
    sort(p.item, p.n);  //ordinamento elem per difficoltà dal + alto al + basso
    int pos, dif_riga, t, flag, ss;
    int tot = 0;
    int f1, f2, f3, f4;
    f1 = f2 = f3 = f4 = 0;
    int f;
    diagonale_t *d = DIAGONALIcrea(n); //crea diagonali finali e di appoggio

    for (int i = p.n-1; i >= 0; i--) {  //elemento a < difficolà che può andare da solo
        if (ITEMisfrontale(p.item[i]) && ITEMprimo(p.item[i])) {
            t = i;
            break;  }
    } //poi definisco e inizializzo tutto a zero
    int avanti[p.n], cnt_a = 0;
    int indietro[p.n], cnt_i = 0;
    int acrobatici[p.n], cnt = 0;
    int u_spalle[p.n], i_cnt_s = 0;
    int u_frontali[p.n], i_cnt_f = 0;
    int i_fronatle;

    for (int i = 0; i < p.n; i++) {
        if (ITEMavanti(p.item[i])) {
            avanti[cnt_a] = i;      cnt_a++;
            acrobatici[cnt] = i;    cnt++;
        }
        if (ITEMindietro(p.item[i])) {
            indietro[cnt_i] = i;    cnt_i++;
            acrobatici[cnt] = i;    cnt++;
        }
        if (ITEMavanti(p.item[i]) || ITEMindietro(p.item[i])) {
            if (p.item[i].uscita == frontale)   u_frontali[i_cnt_f++] = i;
            if (p.item[i].uscita == spalle)     u_spalle[i_cnt_s++] = i;
            if (p.item[i].ingresso == frontale) i_fronatle = i;
        }
    }
    for (int j = n - 1; j >= 0; f = 1, f3 = 0, j--) { //guarda tutte le diagonali
        d[j].n = 1;     pos = 1;
        if ((f1 && j == 1)  || (f2 && j == 0)) { //se ho soddisfatto uno degli obbiettivi
            f3 = 1;     f = 0;
        }
        int i;
        ss = i = 0;
        for(flag = 1; flag; ) { //fino a trovare elem che inizia front e che può essere primo
            if (j == n - 1) //prima volta avvio elem sicuramente acrobatici
                while (i < cnt && (!ITEMisfrontale(p.item[acrobatici[i]]) || !ITEMprimo(p.item[acrobatici[i]])))    i++;
            else if (!f3 && !f1 && j == 1) //seconda riga metto sicuramente elem in avanti
                while (i < cnt_a && (!ITEMisfrontale(p.item[avanti[i]]) || !ITEMprimo(p.item[avanti[i]])))          i++;
            else if (!f3 && !f2 && j == 0) //prima riga metto sicuramente elem indietro
                while (i < cnt_i && (!ITEMisfrontale(p.item[indietro[i]]) || !ITEMprimo(p.item[indietro[i]])))      i++;
            if (f3 && f) { //controllo se non ho nessuna necessità
                i = 0;      f = 0;  }
            while (i < p.n && f3 && (!ITEMisfrontale(p.item[i]) || !ITEMprimo(p.item[i]))) i++;
            errore(j, cnt, p.n, i);  //controllo errori
            if (f3)     ss = i; //ritorno indice corrente
            else{
                if ((j == 1 && i >= cnt_a) || (j == 0 && i >= cnt_i))   f3 = 1;
                else    ss = indice(i, avanti, indietro, acrobatici, j);    }

            // controlliamo se posso concludere
            if (condition(p.item[ss].difficolta + tot, j, p.DP, p.item[t].difficolta,  f2, p.item[indietro[cnt_i-1]].difficolta, p.item[avanti[cnt_a-1]].difficolta, 0, p.item[ss], 0)
                && p.item[ss].difficolta < p.DD && !ITEMisfinale(p.item[ss]) &&
                start_condition(p.item[u_frontali[i_cnt_f-1]].difficolta, p.item[u_spalle[i_cnt_s-1]].difficolta, p.item[ss], p.DD, p.item[i_fronatle].difficolta, p.item[t].difficolta, j)) {
                d[j].elem[0] = ss;
                d[j].difficolta_tot = p.item[ss].difficolta;
                d[j].valore_tot = p.item[ss].valore;
                tot += p.item[ss].difficolta;
                dif_riga = p.item[ss].difficolta;
                if (j == n - 1 && p.item[ss].difficolta >= DIFFICOLTA)      d[j].bonus = 1;
                flag = 0;
            }   i++;
        }
        if (ITEMavanti(p.item[d[j].elem[0]]))       f1 = 1;
        if (ITEMindietro(p.item[d[j].elem[0]]))     f2 = 1;
        for(flag = 1, i = 0; flag;) {
            /* se la diagonale ha una difficoltà minore di DP o se è la prima o se altre condizioni
             * o se gli elementi nella diag sono minori di 5 */
            while((p.item[i].difficolta + dif_riga) <= p.DD
                  && condition(p.item[i].difficolta + tot, j, p.DP, p.item[t].difficolta, f2, p.item[indietro[cnt_i-1]].difficolta,  p.item[avanti[cnt_a-1]].difficolta, f1, p.item[i], pos)
                  && sequenza(p.item[d[j].elem[d[j].n-1]], p.item[i], j, &f4)
                  && prova_avanti(f1, j, p.item[i]) && prova_indietro(f2, j, p.item[i])) {

                d[j].elem[pos] = i;
                d[j].n++;
                d[j].difficolta_tot += p.item[i].difficolta;
                d[j].valore_tot += p.item[i].valore;
                tot += p.item[i].difficolta;
                dif_riga += p.item[i].difficolta;
                if (j == n - 1 && p.item[i].difficolta >= DIFFICOLTA)   d[j].bonus = 1;
                pos++;
                if (ITEMavanti(p.item[d[j].elem[pos-1]]))           f1 = 1;
                if (ITEMindietro(p.item[d[j].elem[pos-1]]))         f2 = 1;
                if (ITEMisfinale(p.item[i]))                           flag = 0;
            }   i++;
            // riesco dal completare una diagonale se:
            if (( p.DP - d[j].difficolta_tot < p.item[p.n-1].difficolta) ||
                (p.DD - d[j].difficolta_tot < p.item[p.n-1].difficolta) || i == p.n || pos == D)
                flag = 0;
        }
    }
    if (!f1) {
        printf("Impossibile creare una diagonale percè non possiamo inserire elemento acrobatico indietro!\n");
        exit(-3);   }
    if (!f2) {
        printf("Impossibile creare una diagonale percè non possiamo inserire elemento acrobatico in avanti!\n");
        exit(-4);   }
    stampa(p.item, d, n, p.DD, p.DP);
    DIAGONALIdistruggi(d);
}
