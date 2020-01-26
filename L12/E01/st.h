//
// Created by Isabella Priano on 09/01/2020.
//

#ifndef LAB_121_ST_H
#define LAB_121_ST_H

typedef struct st_t* ST;

ST STinit(int n);
void STinsert(ST st, char *name);
int STgetindex(ST st, char *name);
char *STselect(ST st, int i);

#endif //LAB_121_ST_H
