#include <stdio.h>
#define GEMME 4

//typedef struct{
//    int z, s, r, t;//zaffiro, smeraldo, rubino, topazio
//    int vz, vs, vr, vt;
//    int maxR;
//}pietre;

void creaCollana(int *z, int *s, int *r, int *t, int *vz, int *vs, int *vr, int *vt, int *maxR);
//int disp_rip1(int pos, int *val, int *sol, int n, int k, int count);
int disp_rip2(int pos,int *val,int *sol,int *solMax,int *valMax,int *lunghSolMax, int maxR, int n, int k, int contG[], int valG[], int count);
char *collana_finita(int n);
int controllo(int contGioielli[], int sol[],int pos, int maxRipetizioni);
int soldi_collana(int pos, int *sol, int valGioielli[]);
void poche_istruzioni();

typedef enum{   id_zaffiri, id_smeraldi, id_rubini, id_topazi   }n;

int main() {
    poche_istruzioni();
    return 0;
}

void poche_istruzioni(){
    int n_z, n_s, n_r, n_t;
    int val_z, val_s, val_r, val_t;
    int maxR;
    creaCollana(&n_z, &n_s, &n_r, &n_t, &val_z, &val_s, &val_r, &val_t, &maxR);
    int k =  n_z + n_s + n_r + n_t;

    int val[] = {id_zaffiri, id_smeraldi, id_rubini, id_topazi};
    int sol[k], solMax[k];
    int valMax = 0, lunghSolMax = 0;;
    int contG[] = {n_z,n_s,n_r,n_t};
    int valG[] = {val_z,val_s,val_r,val_t};

    disp_rip2(0, val, sol, solMax, &valMax, &lunghSolMax, maxR, GEMME, k, contG, valG, 0);
    printf("\nSoluzione max: ");
    for (int i = 0; i < lunghSolMax; ++i)   printf("%s ", collana_finita(solMax[i]));
    printf("\n");
    printf("Soluzione ottima di valore %d usando %d gemma/e\n", valMax, lunghSolMax);

}

void creaCollana(int *z, int *s, int *r, int *t, int *vz, int *vs, int *vr, int *vt, int *maxR){
    printf("Inserisci n e valore zaffiri: ");    scanf("%d%d", z, vz);
    printf("Inserisci n e valore rubini: ");     scanf("%d%d", r, vr);
    printf("Inserisci n e valore topazi: ");     scanf("%d%d", t, vt);
    printf("Inserisci n e valore smeraldi: ");   scanf("%d%d", s, vs);
    printf("Inserisci n max ripetizioni: ");     scanf("%d", maxR);
}

//int disp_rip1(int pos, int *val, int *sol, int n, int k, int count){
//    if(pos >= k){
//        for(i=0; i<k; i++)
//            printf("%d", sol[i]);
//        printf("\n");
//        return count+1;
//    }
//    for(int i=0; i<n; i++){
//        sol[pos] = val[I];
//        count = disp_rip1(pos+1, val, sol, n, k, count);
//    }
//    return count;
//}

int disp_rip2(int pos,int *val,int *sol, int *solMax,int *valMax, int *lunghSolMax, int maxR, int n, int k, int contG[], int valG[], int count) {
    int valC;
    if (pos >= k)   return count + 1;
    for (int i = 0; i < n; i++) {
        sol[pos] = val[i];
        if (controllo(contG, sol, pos, maxR)){ //controllo se la soluione è valida (uso quindi pruning)
            valC = soldi_collana(pos,sol,valG);//se la soluzione è valida controllo se è la soluzione best
            if(valC >= *valMax){ //se è soluzione con valore max scelgo quindi la solbest
                for (int j = 0; j <= pos; ++j)  solMax[j] = sol[j];
                *valMax = valC;
                *lunghSolMax = pos + 1;
            }//ricorsione
            count = disp_rip2(pos + 1, val, sol, solMax, valMax, lunghSolMax, maxR, n, k, contG,valG, count);
        }
    }   return count;
}

int soldi_collana(int pos, int *sol, int valG[]){
    int soldi;
    soldi = 0;
    for (int i = 0; i <= pos; ++i)  soldi += valG[sol[i]];
    return soldi;
}

int controllo(int contG[], int sol[],int pos,int maxR) {
    int i, j, f;
    f = 0; //flag per contare

    for (i = 0; i < GEMME; ++i) { //controllo numero delle gemme
        f = 0;
        for (j = 0; j <= pos; ++j) {
            if (sol[j] == i)    f++;
        }
        if (f > contG[i])    return 0;
    }

    for (i = 0; i < pos; ++i) //controllo dove si trovano
    {   if (sol[i] == id_zaffiri && !(sol[i + 1] == id_zaffiri || sol[i + 1] == id_rubini))     return 0;
        if (sol[i] == id_smeraldi && !(sol[i + 1] == id_smeraldi || sol[i + 1] == id_topazi))   return 0;
        if (sol[i] == id_rubini && !(sol[i + 1] == id_smeraldi || sol[i + 1] == id_topazi))     return 0;
        if (sol[i] == id_topazi && !(sol[i + 1] == id_zaffiri || sol[i + 1] == id_rubini))      return 0;   }

    f = 1;
    for (i = 1; i <= pos ; ++i) { //controllo quanti ce ne sono
        if(sol[i] == sol[i-1])  f++;
        else    f = 1;
        if(f > maxR)  return 0; }

    int contZ = 0, contS = 0;//controllo z e s
    for (i = 0; i <= pos ; ++i) {
        if(sol[i] == id_zaffiri)    contZ++;
        if(sol[i] == id_smeraldi)   contS++;    }
    if(contZ > contS)  return 0;
    return 1;
}

char *collana_finita(int n){
    switch(n){
        default:            return "errore";    break;
        case id_zaffiri:    return "z -";       break;
        case id_smeraldi:   return "s -";       break;
        case id_topazi:     return "t -";       break;
        case id_rubini:     return "r -";       break;  }
}