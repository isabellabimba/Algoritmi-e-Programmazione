//
// Created by Isabella Priano on 14/12/2019.
//

#ifndef LAB_104_TABELLA_H
#define LAB_104_TABELLA_H

typedef struct tabella *Tab;

Tab tabella_init(int n);
int ins_tab(Tab t, char *name, int *num);
char *ind_to_string(Tab t, int ind);
int string_to_ind(Tab t, char *name);
void sort_vertici(int *v, Tab t, int n);
void print_tabella(Tab t);

#endif //LAB_104_TABELLA_H
