#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hospede.h"

#define MAX_QUARTOS 50

struct quarto
{
    int numero;
    char disponibilidade[81];
    float preco;
    char localizacao[81];
};

struct hospede
{
    char nome[81];
    int estadia;
    float documento;
    Quarto *quarto;
    struct hospede *prox;
};

void exibir_quartos(Quarto *q[])
{
    int i;
    for (i = 0; i < MAX_QUARTOS; i++)
    {
        printf("N do quarto: %d\n", q[i]->numero);
    }
}

/* Hospede *inicializa_reserva(void)
{
    return NULL;
} */

/* Hospede *cria_reserva(char nome[81], int estadia, float documento, Hospede *h)
{
    Hospede *nova_reserva;
    nova_reserva = (Hospede *)malloc(sizeof(Hospede));
    strcpy(nova_reserva->nome, nome);
    strcpy(nova_reserva->quarto->disponibilidade, "Indisponivel");
    nova_reserva->estadia = estadia;
    nova_reserva->documento = documento;
    nova_reserva->prox = h;
    return nova_reserva;
}
 */
/* Quarto * imprime_quartos(Quarto *q){
    Quarto * p;
    for(p = q; p != NULL; p = p->prox){
        printf("Numero do quarto: %d | Preco: %.2f | Localizacao: %s | Disponibilidade: %s\n", p->numero, p->preco, p->localizacao, p->disponibilidade);
    }
}

void libera_quartos(Quarto* q){
    Quarto* p = q;
    while(p != NULL){
        Quarto* t = p->prox;
        free(p);
        p = t;
    }
} */