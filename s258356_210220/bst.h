//
// Created by Isabella Priano on 22/02/2020.
//

#ifndef ESAME99_BST_H
#define ESAME99_BST_H

#include "menu.h"

typedef struct bst *BST;
struct bst{
    Piattini V;
    BST dx, sx;
};

BST combina_aux(int data[], int n, int k, int out_v[], int out_pos, int sk, int bool, BST root, struct piatti ElencPt[]);
void copiavett(int *vs, int *vd, int dims, int s);
BST createNode(Piattini value);
BST insert(BST root, Piattini data, int n);
void inorder(BST root, int n, struct piatti ElencPt[]);
int MENUcompare(Piattini M1, Piattini M2, int n);

#endif //ESAME99_BST_H
