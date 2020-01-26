#include <stdio.h>
#include <time.h>
#include "istruzioni.h"
#include "diagonali.h"

#define DIFFICOLTA 8

int main(int argc, char *argv[]){
    clock_t begin = clock();
    FILE *fp;
    apri_file(&fp, argv[1]);
    Item_wrappper p = ITEMcarica(fp);
    wrapper_powerset(p, B);
    ITEMdealloca(p);

    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("\nTIME EXECUTION: %g", time_spent);
    printf("\n");
    return 0;
}