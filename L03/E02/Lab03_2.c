/*
 ============================================================================
 Name        : Lab03_2.c
 Author      : Isabella Priano s258356
 Version     : 27/10/19
 Description : Laboratorio 3 esercizio 2 APA
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#define rb -6  // GCC opera in precisione estesa su 16 - 6 bytes (80 bit)
// trovate informazioni su: https://en.m.wikipedia.org/wiki/Long_double
// https://en.m.wikipedia.org/wiki/Extended_precision#x86_extended_precision_format
// https://en.wikipedia.org/wiki/Extended_precision
// VERSIONE PRG. OPERANTE SU 128 bit per long double https://onlinegdb.com/rk0o2u1cB

typedef enum {FALSE, TRUE} boolean;

boolean isbigEndian (void);
void dec_bin(int n, int vett[], int offset);
void stampaCodifica (void *p, int size, int bigEndian);

int main(void)
{
    float        af;
    double       ad;
    long double ald;

    int bigEndian;

    bigEndian = isbigEndian();

    printf("\nIntroduci un numeo reale : ");
    scanf("%Lf", &ald);

    af = (float)  ald;
    ad = (double) ald;

       stampaCodifica((void *)&af, sizeof(af) ,bigEndian);  printf("\n");
       stampaCodifica((void *)&ad, sizeof(ad) ,bigEndian);  printf("\n");
       stampaCodifica((void *)&ald,sizeof(ald) + rb,bigEndian);

    return 0;
}

boolean isbigEndian (void)
{
	int x = 1;
	return (*(char *)&x ? FALSE : TRUE);
}

void stampaCodifica (void *p, int size, int bigEndian){
	int byte;
	unsigned char *pm = (unsigned char *)p;
	int *cbin = calloc(8 * size, sizeof(int)); // alloca mem. e inizializza a 0

	 if(cbin == NULL) {
	   printf("Memoria esaurita\n");
	   exit (1);
	 }

	for (byte = 0; byte < size; byte++)
	  bigEndian ? dec_bin(pm[byte], cbin, byte) :
			      dec_bin(pm[size - 1 - byte], cbin, byte);

    printf("\nS ESP MANT\n");
	for (int i = 0; i < size * 8; i++){
	  printf("%d",cbin[i]);
	  if (i == 0) printf(" ");
	  if ((i == 8  && size == 4) ||
		  (i == 11 && size == 8) ||
		  (i == 15 && size == 16 + rb)) printf(" ");
	}
}

void dec_bin(int n, int vett[], int byte) {
    int i = 1;
    while (n > 0) {
    	    vett[(byte + 1) * 8 - i] = n % 2;
            n = n / 2;
            i++;   }
}
