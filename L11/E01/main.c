#include "utility.h"
#include "collezione_titoli.h"

int main() {
    int flag = 1;
    comandi_t c;
    CollezioneTitoli collezione = COLLEZIONE_Tinit();
    while (flag) {
        c = leggiComando();
        elaborazioneComando(c, &flag, collezione);
    }   return 0;
}