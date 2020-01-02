#include <stdio.h>
#include <stdlib.h>

typedef enum{ orizzontale, verticale  }rotazione_t;
typedef enum{ FALSE, TRUE }boolean;
typedef char colori_t;

typedef struct _sub_tile {
    int val;
    colori_t colore;
}sub_tile_t;

typedef struct _tile {
    rotazione_t rot;
    sub_tile_t 	tile[2];
    boolean usata;
}tile_t;

typedef struct _board {
    int id;
    boolean	vuoto;
}board_t;

void leggi1(board_t ***tiles_m, tile_t *pool_tasselli, int *R, int *C);
void leggi2(tile_t **tiles_pool, int*n);
void disp_sempl(int pos, tile_t *sacco_tasselli, board_t **board, int *max_punteggio, board_t **best_sol, int n_tasselli, int R, int C);
void best_sol(board_t **tiles_m, tile_t *tiles_pool);
void display_sol(board_t **best_sol, int R, int C);
int valuta_punteggio(board_t **board, tile_t *pool, int R, int C);
void rotazione(tile_t* tile,int k);

int main(int argc, char **argv) {
    board_t **tiles_m;
    tile_t	*tiles_pool;
    best_sol(tiles_m,tiles_pool);
    printf("\n");
    return(0);
}

void best_sol(board_t** tiles_m,tile_t* tiles_pool){
    int max_punteggio = 0;
    int R, C;
    int n_tasselli;
    board_t** best_sol;

    leggi2(&tiles_pool,&n_tasselli);
    leggi1(&tiles_m,tiles_pool,&R,&C);
    best_sol = (board_t**) malloc(R * sizeof(tile_t*));
    for (int i = 0; i < R; i++) best_sol[i] = (board_t*) malloc(C * sizeof(tile_t));
    disp_sempl(0, tiles_pool, tiles_m, &max_punteggio, best_sol, n_tasselli, R, C);
    display_sol(best_sol, R, C);
    printf("\nPunteggio: %d",max_punteggio);
}

void display_sol(board_t** best_sol, int R, int C) {
    for (int i = 0; i < R; i++){
        printf("\n[ ");
        for (int j = 0; j < C; j++) printf("%d ",best_sol[i][j].id);
        printf("]");    }
}

void leggi2(tile_t **tiles_pool, int* n) {
    FILE *fp= fopen("tiles.txt","r");
    if (fp == NULL){
        perror("Errore durante l'apertura del file");
        exit(EXIT_FAILURE); }

    fscanf(fp,"%d",n);
    *tiles_pool = (tile_t*) malloc(*n*sizeof(tile_t));
    fgetc(fp);
    for (int i = 0; i < *n; i++) {
        fscanf(fp,"%c %d %c %d",	&((*tiles_pool)[i].tile[orizzontale].colore),
               &((*tiles_pool)[i].tile[orizzontale].val),
               &((*tiles_pool)[i].tile[verticale].colore),
               &((*tiles_pool)[i].tile[verticale].val));
        fgetc(fp);
        (*tiles_pool)[i].usata	= FALSE;    }
}

void leggi1(board_t*** tiles_m,tile_t* pool_tasselli, int* R, int* C) {
    FILE *fp = fopen("board.txt","r");
    if (fp == NULL){
        perror("Errore nell'apertura file");
        exit(EXIT_FAILURE); }
    fscanf(fp,"%d%d",R,C);
    *tiles_m = (board_t**) malloc( (*R) * sizeof(*tiles_m));
    for (int i = 0; i < (*R); i++) (*tiles_m)[i] = (board_t*) malloc((*C) * sizeof(board_t));
    for (int i = 0; i < (*R); i++) {
        for (int j = 0; j < (*C); j++) {
            fscanf(fp,"%d/",&((*tiles_m)[i][j].id));
            if ( (*tiles_m)[i][j].id != -1) {
                (*tiles_m)[i][j].vuoto = FALSE;
                fscanf(fp,"%d",&(pool_tasselli[ (*tiles_m)[i][j].id ].rot) );	//salvo nella posizione che ho appena letto se non era -1
                if ((pool_tasselli[ (*tiles_m)[i][j].id ].rot) == 1)
                    rotazione(pool_tasselli,(*tiles_m)[i][j].id);				//ruoto il tassello
                pool_tasselli[(*tiles_m)[i][j].id].usata = TRUE; }
            else { (*tiles_m)[i][j].vuoto = TRUE;
                   fscanf(fp,"%d",&((*tiles_m)[i][j].id));						//supero il valore numerico dopo
                 }
        }
    }
}

int valuta_punteggio(board_t** board,tile_t* pool,int R,int C) {
    int risultato = 0, curr_ris = 0;
    int i, j;
    boolean col_eq;
    colori_t colore_iniziale;

    for (i = 0; i < R; i++) { //calcolo il valore delle righe
        j = 0;
        colore_iniziale = pool[ board[i][j].id ].tile[orizzontale].colore;		//accesso mediante indice
        col_eq = TRUE;
        curr_ris = 0;
        for (j=0; j < C && col_eq; j++) {
            if (colore_iniziale == pool[ board[i][j].id ].tile[orizzontale].colore)
                curr_ris += pool[ board[i][j].id ].tile[orizzontale].val;
            else col_eq = FALSE;
        }
        if (col_eq)     risultato += curr_ris;
    }
    for (j = 0; j < C; j++) { //calcolo il valore delle colonne
        i = 0;
        colore_iniziale = pool[ board[i][j].id ].tile[verticale].colore;
        col_eq = TRUE;
        curr_ris = 0;
        for (i = 0; i < R && col_eq; i++) {
            if (colore_iniziale == pool[ board[i][j].id ].tile[verticale].colore)
                curr_ris 	+= pool[ board[i][j].id ].tile[verticale].val;
            else col_eq 	= FALSE; }
        if (col_eq) risultato += curr_ris;  }
    return risultato;
}

void disp_sempl(int pos,tile_t* sacco_tasselli,board_t** board,int* max_punteggio,board_t** best_sol, int n_tasselli, int R,int C) {
    int i, j;
    if (pos >= R*C) {
        int curr_punteggio = valuta_punteggio(board,sacco_tasselli,R,C);
        if (curr_punteggio == 115 ) printf("troppo");
        if ( curr_punteggio > (*max_punteggio) ){
            *max_punteggio = curr_punteggio;
            for (i = 0; i < R; i++) {
                for (j = 0; j < C; j++) best_sol[i][j]	= board[i][j]; }
        } return;
    }
    i = pos/R; j = pos%C;
    if (!board[i][j].vuoto){				//Se non vuoto => occupato => ricorro
        disp_sempl(pos+1,sacco_tasselli,board,max_punteggio,best_sol,n_tasselli, R,C);
        return; }
    for (int k=0; k<n_tasselli; k++) {
        if(sacco_tasselli[k].usata == FALSE){
            board[i][j].id = k;
            board[i][j].vuoto = FALSE;
            sacco_tasselli[k].usata = TRUE;
            disp_sempl(pos+1,sacco_tasselli,board,max_punteggio,best_sol,n_tasselli, R,C);
            rotazione(sacco_tasselli,k);       //prima la inserisco normalmente, poi la ruoto
            disp_sempl(pos+1,sacco_tasselli,board,max_punteggio,best_sol,n_tasselli, R,C);
            board[i][j].vuoto = TRUE;
            sacco_tasselli[k].usata = FALSE;    }
    }
}

void rotazione(tile_t* tile,int k) {
    sub_tile_t tmp;
    tmp = tile[k].tile[orizzontale];
    tile[k].tile[orizzontale] = tile[k].tile[verticale];
    tile[k].tile[verticale] = tmp;
}