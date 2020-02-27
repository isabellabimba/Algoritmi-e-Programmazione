//
// Created by Isabella Priano on 22/02/2020.
//
#include <stdio.h>
#include <stdlib.h>
#include "bst.h"
#include "menu.h"

BST combina_aux(int data[], int n, int k, int out_v[], int out_pos, int sk, int bool, BST root, struct piatti ElencPt[]) {
	static BST nr;
	int i;
	nr = root;
	if (bool == 0){
        for (i=0; i <= n-k; i++) {
            out_v[out_pos]=data[i];

             if(k > 1) combina_aux(&data[i + 1], n - 1 - i, k - 1, out_v, out_pos + 1, sk, bool, nr, ElencPt);
    else {
      // menu pronto
      Piattini Menu;
      float PrzMenu = 0;
      Menu = malloc(sizeof(Piattini));
      Menu->vett_piatti = malloc(sk * sizeof(int));
      for(int j=0; j<sk; j++){
      Menu->vett_piatti[j] = out_v[j];
      PrzMenu += ElencPt[out_v[j]].prezzo;
      }
      Menu->prezzo_tot = PrzMenu;
      nr = insert(nr, Menu, sk);

    }
  } } else {
	  for (i=0; i <= n-k; i++)
	    {
	      out_v[out_pos]=data[i];

	      if(k > 1)
	      	combina_aux(&data[i + 1], n - 1 - i, k - 1, out_v, out_pos + 1, sk, bool, nr, ElencPt);
	      else
	      {
	        // menu pronto : definiamo i possibili "bis"
	      	int *vbis;
	      	vbis = malloc((sk + 1) * sizeof(int));
	      	for (int s = 0; s < sk; s++)
	      	   copiavett(out_v, vbis, sk, s);
	      	Piattini Menu;
	      	float PrzMenu = 0;
	      	Menu = malloc(sizeof(Piattini));
	      	Menu->vett_piatti = malloc((sk+1) * sizeof(int));
	      	 for(int j=0; j<sk+1; j++){
	      	      Menu->vett_piatti[j] = vbis[j];
	      	      PrzMenu += ElencPt[vbis[j]].prezzo;}
	      	      Menu->prezzo_tot = PrzMenu;
	      	      nr = insert(nr, Menu, sk);
	      }
	    }
   }
 return nr;
}


void copiavett(int *vs, int *vd, int dims, int s){
    for(int i=0; i<dims; i++){
        if(i <=s ) vd[i] = vs[i];
        if(i >= s) vd[i+1] = vs[i];
    }
}

BST createNode(Piattini value){
    BST newNode = malloc(sizeof(struct bst));
    newNode->V = value;
    newNode->sx = NULL;
    newNode->dx = NULL;
    return newNode;
}

BST insert(BST root, Piattini data, int n){
    if(root == NULL) return createNode(data);
    if(MENUcompare(data, root->V, n))   // data < root->data
        root->sx = insert(root->sx, data, n);
    else if(MENUcompare(root->V, data, n))  //data > root->data
        root->dx = insert(root->dx, data, n);
    return root;
}

void inorder(BST root, int n, struct piatti ElencPt[]){
    if(root == NULL) return;
    inorder(root->sx, n, ElencPt);
     for (int i=0; i<n; i++){
    	int piatto = root->V->vett_piatti[i];
    	printf("%s ", ElencPt[piatto].nome);
    	printf("%s ", ElencPt[piatto].tipo1);
    	printf("%s ", ElencPt[piatto].tipo2);
    	printf("%.2f\n", ElencPt[piatto].prezzo);
     }
     printf("prezzo menu = %.2f\n", root->V->prezzo_tot);
     printf("-------------------\n");
    inorder(root->dx,n, ElencPt);
}

int MENUcompare(Piattini M1, Piattini M2, int n){
    if(M1->prezzo_tot != M2->prezzo_tot) return(M1->prezzo_tot < M2->prezzo_tot);
    else{
        for(int i=0; i<n; i++)
            if(M1->vett_piatti[i] != M2->vett_piatti[i]) return(M1->vett_piatti[i] < M2->vett_piatti[i]);
    } return 2; //menu identici (caso non realizzabile ma gestito comunque dalla funzione)
}
