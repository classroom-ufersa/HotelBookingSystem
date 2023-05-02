#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hospede.h"
#include "../Quartos/quarto.c"

struct hospede
{
    char nome[81];
    int estadia;
    float documento;
    Quarto *quarto;
    struct hospede *prox;
};

Hospede *inicializa_reserva(void)
{
    return NULL;
}

// precisa corrigir. está inserindo ao contrario
Hospede *cria_reserva(Hospede *h, Quarto *q, char nome[81], int estadia, float documento)
{

    Hospede *nova_reserva;
    nova_reserva = (Hospede *)malloc(sizeof(Hospede));
    strcpy(nova_reserva->nome, nome);
    nova_reserva->quarto = q;
    strcpy(nova_reserva->quarto->disponibilidade, "Indisponivel");
    nova_reserva->estadia = estadia;
    nova_reserva->documento = documento;
    nova_reserva->prox = h;
    return nova_reserva;
}

int destruir_reserva(Hospede *h)
{
    return (h == NULL);
}

void imprime_reserva(Hospede *h)
{
    Hospede *hAux;
    for (hAux = h; hAux != NULL; hAux = hAux->prox)
    {
        printf("Nome: %s | Estadia: %d dias | Documento: %.0f\nQuarto: %d\n\n", hAux->nome, hAux->estadia, hAux->documento, hAux->quarto->numero);
    }
    free(hAux);
}

Hospede *busca_reserva(int numero, Hospede *h)
{
    Hospede *hAux;
    for (hAux = h; hAux != NULL; hAux = hAux->prox)
    {
        if (hAux->quarto->numero == numero)
        {
            printf("Nome: %s | Estadia: %d dias | Documento: %.0f\nQuarto: %d\n\n", hAux->nome, hAux->estadia, hAux->documento, hAux->quarto->numero);
        }
    }
    free(hAux);
    return NULL;
}

Hospede *exclui_reserva(Hospede *h, int numero)
{
    Hospede *ant = NULL;
    Hospede *hAux = h;

    while (hAux->quarto->numero != numero)
    {
        if (hAux == NULL)
        {
            return h;
        }
        ant = hAux;
        hAux = hAux->prox;
    }

    if (ant == NULL)
    {
        h = hAux->prox;
    }
    else
    {
        ant->prox = hAux->prox;
    }
    free(hAux);
    return h;
}

void libera_reserva(Hospede *h)
{
    Hospede *hAux = h;
    Hospede *hAuxLibera;
    while (hAux != NULL)
    {
        hAuxLibera = hAux->prox;
        free(hAux);
        hAux = hAuxLibera;
    }
}