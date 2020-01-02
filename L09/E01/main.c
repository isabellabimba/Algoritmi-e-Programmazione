#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int s;
    int f;
}att;

void prendi(att **vet, int *n);
void top_sol(att *vet, int n);
void print_poco(att *vet, int i, int *ind);
void print_tutto(att *vet, int n, int *w, int *ind);
void sort(att *vet, int n);
void poche_istruzioni();

int main() {
    poche_istruzioni();
    return 0;
}
void poche_istruzioni(){
    att *vet;
    int n;
    prendi(&vet, &n);
    sort(vet, n);
    top_sol(vet, n);
    free(vet);
}

void prendi(att **vet, int *n){     //funzione per caricare il vettore di struct da file
    FILE *fp = fopen("file.txt", "r");;
    if(fp==NULL)    {   perror("Errore file\n");    exit(EXIT_FAILURE);     }
    fscanf(fp, "%d", n);
    (*vet)=(att *)malloc((*n)*sizeof(att));
    for(int i=0; i<(*n); i++)   fscanf(fp, "%d %d", &(*vet)[i].s, &(*vet)[i].f);
    fclose(fp);
}

void sort(att *vet, int n){             //ordinamento delle attività in maniera crescente rispetto al tempo di inizio
    att tmp;
    for(int i=0; i<n; i++){
        for(int j=0; j<n-1-i; j++){
            if(vet[j].s>vet[j+1].s)
            {   tmp=vet[j];     vet[j]=vet[j+1];    vet[j+1]=tmp;   }
            else if(vet[j].s==vet[j+1].s)
                { if(vet[j].f>vet[j+1].f){    tmp=vet[j]; vet[j]=vet[j+1];    vet[j+1]=tmp;   }   }
        }
    }
}

void print_poco(att *vet, int i, int *ind){         //stampa ricosrsiva della soluzione
    if(i==-1)   return;
    print_poco(vet, ind[i], ind);
    printf("(%d,%d) ", vet[i].s, vet[i].f);
}

void print_tutto(att *vet, int n, int *w, int *ind){
    int max_w=0, max_i=-1;
    for(int i=0; i<n; i++)  //selezione dell'attività che termina la soluzione
        { if(w[i]>=max_w) {   max_i=i;    max_w=w[i]; }   }
    printf("Sequenza di attivita' con somma delle durate massime: ");
    print_poco(vet, max_i, ind);        //stampa della soluzione
}

void top_sol(att *vet, int n){
    int *ind, *w, w_tmp;
    ind = (int *)malloc(n*sizeof(int));
    w = (int *)malloc(n*sizeof(int));
    if(ind==NULL || w==NULL)
    {   printf("Errore.\n");    exit(-1);   }

    ind[0]=-1; w[0]=vet[0].f-vet[0].s;
    for(int i=1; i<n; i++){
        ind[i]=-1; w[i]=vet[i].f-vet[i].s;
        w_tmp=w[i];
        for(int j=0; j<i; j++){                                 //controllo di ogni prefisso per ogni attività selezionata dal ciclo esterno
            if((vet[j].s<=vet[i].f && vet[j].f<=vet[i].s) && w[i]<w_tmp+w[j]){   //controlla della compatibilità di due attività
                ind[i]=j;   w[i]=w_tmp+w[j];
            }
        }
    }
    print_tutto(vet, n, w, ind);      //stampa della soluzione
    free(ind);
    free(w);
}
