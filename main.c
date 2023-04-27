#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hospede.h"

#define MAX_QUARTOS 50

Quarto * quartos[MAX_QUARTOS];

int main(void)
{
    int i;
    for(i = 0; i <= MAX_QUARTOS; i++){
        quartos[i] = inicializa_quartos(i+1);
    }

    exibir_quartos(quartos);

    return 0;
}