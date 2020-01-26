#include <stdio.h>
#include <stdlib.h>

#define N 4 //tipi gioielli

void metti_dati(int* n_z,int* n_s,int* n_r,int* n_t);
int gioiello(int n_z,int n_s,int n_r,int n_t,int ****matriceOccorrenze);      //fX
int fZ(int n_z,int n_s,int n_r,int n_t, int ****matriceOccorrenze, int cont); //zaffiri
int fS(int n_z,int n_s,int n_r,int n_t, int ****matriceOccorrenze, int cont); //smeraldi
int fR(int n_z,int n_s,int n_r,int n_t, int ****matriceOccorrenze, int cont); //rubini
int fT(int n_z,int n_s,int n_r,int n_t, int ****matriceOccorrenze, int cont); //topazi
int ****matrix_occ(int n_z, int n_s, int n_r, int n_t); //inizializzo matrice occorrenze
void libera_tutto(int**** matriceOccorrenze,int n_z, int n_s, int n_r, int n_t);

int main() {
    int ****m_grossa;
    int n_z, n_s, n_r, n_t;

    metti_dati(&n_z, &n_s, &n_r, &n_t);
    //condizioni disposizione
    //z - [z r]   s - [s t]   r - [s t]   t - [z r]
    m_grossa = matrix_occ(n_z, n_s, n_r, n_t);
    printf("Collana massima di lunghezza %d", gioiello(n_z, n_s, n_r, n_t, m_grossa));
    libera_tutto(m_grossa,n_z, n_s, n_r, n_t);
    return 0;
}

int ****matrix_occ(int n_z, int n_s, int n_r, int n_t) {
    int ****matriceOccorrenze = (int****)malloc((n_z + 1) * sizeof(int***));
    for (int i = 0; i < (n_z + 1); ++i) {
        matriceOccorrenze[i] = (int***)malloc((n_s + 1) * sizeof(int**));
        for (int j = 0; j < (n_s + 1); ++j) {
            matriceOccorrenze[i][j] = (int**)malloc((n_r + 1) * sizeof(int*));
            for (int t = 0; t < (n_r + 1); ++t) {
                matriceOccorrenze[i][j][t] = (int*)malloc((n_t + 1) * sizeof(int));
                for (int m = 0; m < (n_t + 1); ++m)
                    matriceOccorrenze[i][j][t][m] = -1;//riempio la matrice multidim di -1
            }
        }
    }   return matriceOccorrenze;
}

void libera_tutto(int**** matriceOccorrenze,int n_z, int n_s, int n_r, int n_t) {
    for (int i = 0; i < (n_z + 1); ++i) {
        for (int j = 0; j < (n_s + 1); ++j) {
            for (int t = 0; t < (n_r + 1); ++t)
                free(matriceOccorrenze[i][j][t]);
            free( matriceOccorrenze[i][j]);
        }free(matriceOccorrenze[i]);
    }free(matriceOccorrenze);
}

int gioiello(int n_z,int n_s,int n_r,int n_t,int**** matriceOccorrenze){ //fX
    int *lunghezzeSequenze = calloc(N, sizeof(int));
    if(n_z > 0)     lunghezzeSequenze[0] = fZ(n_z, n_s, n_r, n_t,matriceOccorrenze,0);
    if(n_r > 0)     lunghezzeSequenze[1]= fR(n_z, n_s, n_r, n_t,matriceOccorrenze,0);
    if(n_t > 0)     lunghezzeSequenze[2]= fT(n_z, n_s, n_r, n_t,matriceOccorrenze,0);
    if(n_s > 0)     lunghezzeSequenze[3] = fS(n_z, n_s, n_r, n_t,matriceOccorrenze,0);

    int maxLunghezza = lunghezzeSequenze[0];
    for (int i = 1; i < N; ++i)
    { if(lunghezzeSequenze[i] > maxLunghezza)   maxLunghezza = lunghezzeSequenze[i];}   return maxLunghezza;
}

int fZ(int n_z,int n_s,int n_r,int n_t, int**** matriceOccorrenze, int cont){

    if( matriceOccorrenze[n_z][n_s][n_r][n_t] != -1)   return  matriceOccorrenze[n_z][n_s][n_r][n_t];
    n_z--;

    int nZ = 0, nR = 0;
    if(n_z > 0)     nZ = fZ(n_z, n_s, n_r, n_t,matriceOccorrenze, cont+1);
    if(n_r > 0)     nR = fR(n_z, n_s, n_r, n_t,matriceOccorrenze, cont+1);

    int solParziale =  nZ > nR ? nZ : nR;
    matriceOccorrenze[n_z][n_s][n_r][n_t] = solParziale;

    return solParziale + 1;
}

int fS(int n_z,int n_s,int n_r,int n_t, int**** matriceOccorrenze, int cont){

    if( matriceOccorrenze[n_z][n_s][n_r][n_t] != -1)    return  matriceOccorrenze[n_z][n_s][n_r][n_t];
    n_s--;

    int nS = 0, nT = 0;
    if(n_s > 0)     nS = fS(n_z, n_s, n_r, n_t,matriceOccorrenze, cont+1);
    if(n_t > 0)     nT = fT(n_z, n_s, n_r, n_t,matriceOccorrenze, cont+1);

    int solParziale = nS > nT ? nS : nT;
    matriceOccorrenze[n_z][n_s][n_r][n_t]  = solParziale;

    return solParziale + 1;
}

int fR(int n_z,int n_s,int n_r,int n_t, int**** matriceOccorrenze, int cont){

    if( matriceOccorrenze[n_z][n_s][n_r][n_t] != -1)    return  matriceOccorrenze[n_z][n_s][n_r][n_t];
    n_r--;

    int nS = 0, nT = 0;
    if(n_s > 0)     nS = fS(n_z, n_s, n_r, n_t,matriceOccorrenze, cont+1);
    if(n_t > 0)     nT = fT(n_z, n_s, n_r, n_t,matriceOccorrenze, cont+1);

    int solParziale = nS > nT ? nS : nT;
    matriceOccorrenze[n_z][n_s][n_r][n_t]  = solParziale;

    return solParziale + 1;
}

int fT(int n_z,int n_s,int n_r,int n_t, int**** matriceOccorrenze, int cont){

    if( matriceOccorrenze[n_z][n_s][n_r][n_t] != -1)
        return  matriceOccorrenze[n_z][n_s][n_r][n_t];
    n_t--;

    int nZ = 0, nR = 0;
    if(n_z > 0)     nZ = fZ(n_z, n_s, n_r, n_t,matriceOccorrenze, cont+1);
    if(n_r > 0)     nR = fR(n_z, n_s, n_r, n_t,matriceOccorrenze, cont+1);

    int solParziale =  nZ > nR ? nZ : nR;
    matriceOccorrenze[n_z][n_s][n_r][n_t] = solParziale;
    return solParziale + 1;
}

void metti_dati(int* n_z,int* n_s,int* n_r,int* n_t){
    printf("Inserisci numero zaffiri: ");   scanf("%d", n_z);
    printf("Inserisci numero rubini: ");    scanf("%d", n_r);
    printf("Inserisci numero topazi: ");    scanf("%d", n_t);
    printf("Inserisci numero smeraldi: ");  scanf("%d", n_s);
}