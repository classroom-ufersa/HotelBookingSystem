#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hospede.h"
#include "../Quartos/quarto.c"

struct hospede
{
    char nome[81];
    int estadia;
    int quantidade;
    float documento;
    Quarto *quarto;
    struct hospede *prox;
};

Hospede *inicializa_reserva(void)
{
    return NULL;
}

//Esta criando apenas um no na lista 
Hospede *cria_reserva(Hospede *h, Quarto *q, char nome[81], int estadia, int quantidade, float documento)
{

    Hospede * nova_reserva;
    Hospede * ant = NULL;
    Hospede * aux = h;

    while(aux!=NULL && strcmp(aux->nome, nome) < 0){
		ant = aux;
		aux = aux->prox;
	}

    nova_reserva = (Hospede *)malloc(sizeof(Hospede));
    nova_reserva->quarto = (Quarto*) malloc(sizeof(Quarto));
    
    strcpy(nova_reserva->nome, nome);
    nova_reserva->quarto = q;
    printf("%s", nova_reserva->quarto->disponibilidade);
    strcpy(nova_reserva->quarto->disponibilidade, "OCUPADO");
    nova_reserva->estadia = estadia;
    nova_reserva->quantidade = quantidade;
    nova_reserva->documento = documento;

    if(ant == NULL){
        nova_reserva->prox = h;
        h = nova_reserva;
    }
    else{
        nova_reserva->prox = ant->prox;
        ant->prox = nova_reserva;
    }
    return h;
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
        printf("Nome do responsavel: %s\nDias hospedados: %d\nDocumento: %f\nNumero do quarto: %d\n\n", hAux->nome, hAux->estadia, hAux->documento, hAux->quarto->numero);

        //printf("Nome do responsavel: %s | Estadia: %d dias | Documento: %.0f\nQuarto: %d\nQuantidade de pessoas: %d\n\n", hAux->nome, hAux->estadia, hAux->documento, hAux->quarto->numero, hAux->quantidade);
    }
    free(hAux);
}

void consulta_quantitativo(Hospede *h)
{
    Hospede *hAux;
    int quantidade = 0;
    for (hAux = h; hAux != NULL; hAux = hAux->prox)
    {
        quantidade += hAux->quantidade;
    }
    printf("Ha %d pessoas atualmente hospedadas no hotel.\n", quantidade);
    free(hAux);
}

Hospede *busca_reserva(int numero, Hospede *h)
{
    Hospede *hAux;
    for (hAux = h; hAux != NULL; hAux = hAux->prox)
    {
        if (hAux->quarto->numero == numero)
        {
            return hAux;
            //printf("Nome do responsavel: %s | Estadia: %d dias | Documento: %.0f\nQuarto: %d\nQuantidade de pessoas: %d\n\n", hAux->nome, hAux->estadia, hAux->documento, hAux->quarto->numero, hAux->quantidade);
        }
    }
    //free(hAux);
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

void escreve_lista(Hospede *h)
{
    Hospede *hAux;
    FILE *arq;
    arq = fopen("../dados/ListaReservas.txt", "w");
    if (arq == NULL)
    {
        printf("Nao foi possivel abrir o arquivo de quartos cadastrados.\n");
        exit(1);
    }

    for (hAux = h; hAux != NULL; hAux = hAux->prox)
    {
        fprintf(arq, "%s\n%d\n%.0f\n%d\n", hAux->nome, hAux->estadia, hAux->documento, hAux->quarto->numero);
    }

    fclose(arq);
}

Hospede * ler_lista(Hospede *h, Quarto **q)
{
    int index;
    Quarto *quarto;
    Hospede *hAux;
    Hospede *head = h;
    Hospede *tail = h;
    FILE *arq;
    arq = fopen("../dados/ListaReservas.txt", "r");
    if (arq == NULL)
    {
        printf("Nao foi possivel abrir o arquivo de quartos cadastrados.\n");
        exit(1);
    }
    
    while(!(feof(arq)))
    {
        hAux = (Hospede*) malloc(sizeof(Hospede));
        quarto = (Quarto*) malloc(sizeof(Quarto));
        hAux->quarto = quarto;
        fscanf(arq, "%s\n%d\n%f\n%d\n", hAux->nome, &hAux->estadia, &hAux->documento, &index);
        hAux->quarto = q[index-1];
        hAux->prox = NULL;

        if(head == NULL){
            head = hAux;
            tail = hAux;
        }
        else{
            tail->prox = hAux;
            tail = hAux;
        }
    }
    fclose(arq);
    return head;
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
