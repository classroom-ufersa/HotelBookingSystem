#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hospede.h"
#include "../Quartos/quarto.h"

struct hospede
{
    char nome[81];
    int estadia;
    float documento;
    Quarto *quarto;
    struct hospede *prox;
};

Hospede * inicializa_reserva(void){
    return NULL;
}

Hospede * cria_reserva(char nome[81], int estadia, float documento, int numero, Hospede *h){
    Hospede *nova_reserva;
    nova_reserva = (Hospede*) malloc (sizeof(Hospede));
    strcpy(nova_reserva->nome, nome);
    strcpy(nova_reserva->quarto->disponibilidade, "Indisponivel");
    nova_reserva->estadia = estadia;
    nova_reserva->documento = documento;
    nova_reserva->quarto->numero = numero;
    nova_reserva->prox = h;
    return nova_reserva;
}

int destruir_reserva(Hospede *h){
    return (h == NULL);
}

void imprime_reserva(Hospede *h){
    Hospede *hAux;
    for(hAux = h; hAux != NULL; hAux = hAux->prox){
        printf("Nome: %s | Estadia: %d dias | Documento: %.0f\nQuarto: %d\n\n", hAux->nome, hAux->estadia, hAux->documento, hAux->quarto->numero);
    }
}

Hospede * busca_reserva(int numero, Hospede * h){
    Hospede *hAux;
    for(hAux = h; hAux != NULL; hAux = hAux->prox){
        if(hAux->quarto->numero == numero){
            return hAux;
        }
    }
    return NULL;
}

Hospede * exclui_reserva(Hospede * h, int numero){
    Hospede * ant = NULL;
    Hospede * hAux = h;

    while(hAux->quarto->numero != numero){
        if(hAux == NULL){
            return h;
        }
        ant = hAux;
        hAux = hAux->prox;
    }

    if(ant == NULL){
        h = hAux->prox;
    }
    else{
        ant->prox = hAux->prox;
    }
    free(hAux);
    return h;
}

void libera_reserva(Hospede * h){
    Hospede * hAux = h;
    Hospede * hAuxLibera;
    while(hAux != NULL){
        hAuxLibera = hAux->prox;
        free(hAux);
        hAux = hAuxLibera;
    }
}