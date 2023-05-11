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

Hospede *cria_reserva(Hospede *h, Quarto *q, char nome[81], int estadia, int quantidade, float documento)
{

    Hospede *nova_reserva;
    Hospede *ant = NULL;
    Hospede *aux = h;

    while (aux != NULL && strcmp(aux->nome, nome) < 0)
    {
        ant = aux;
        aux = aux->prox;
    }

    nova_reserva = (Hospede *)malloc(sizeof(Hospede));
    nova_reserva->quarto = (Quarto *)malloc(sizeof(Quarto));

    strcpy(nova_reserva->nome, nome);
    nova_reserva->quarto = q;
    strcpy(nova_reserva->quarto->disponibilidade, "OCUPADO");
    nova_reserva->estadia = estadia;
    nova_reserva->quantidade = quantidade;
    nova_reserva->documento = documento;

    if (ant == NULL)
    {
        nova_reserva->prox = h;
        h = nova_reserva;
    }
    else
    {
        nova_reserva->prox = ant->prox;
        ant->prox = nova_reserva;
    }
    return h;
}

void imprime_reserva(Hospede *h)
{
    Hospede *hAux;
    for (hAux = h; hAux != NULL; hAux = hAux->prox)
    {
        printf("\tNome do responsavel: %s\n\tTotal de pessoas no quarto: %d\n\tDias hospedados: %d\n\tDocumento: %.0f\n\tNumero do quarto: %d\n\n", hAux->nome, hAux->quantidade, hAux->estadia, hAux->documento, hAux->quarto->numero);
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
    printf("\n\tHa %d pessoas atualmente hospedadas no hotel.\n\n", quantidade);
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
        }
    }
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
        fprintf(arq, "%s\n%d\n%d\n%.0f\n%d\n", hAux->nome, hAux->quantidade, hAux->estadia, hAux->documento, hAux->quarto->numero);
    }

    fclose(arq);
}

Hospede *ler_lista(Hospede *h, Quarto **q)
{
    int index;
    Hospede *head = NULL;
    Hospede *tail = NULL;
    FILE *arq;

    arq = fopen("../dados/ListaReservas.txt", "r");
    if (arq == NULL)
    {
        printf("Nao foi possivel abrir o arquivo de quartos cadastrados.\n");
        exit(1);
    }

    fseek(arq, 0, SEEK_END);
    long size = ftell(arq);
    if (size == 0)
    {
        fclose(arq);
        return h;
    }
    fseek(arq, 0, SEEK_SET);

    while (!(feof(arq)))
    {
        Hospede *hAux = (Hospede *)malloc(sizeof(Hospede));
        if (hAux == NULL)
        {
            printf("\n\tErro na alocação de memoria!\n");
            exit(1);
        }
        Quarto *quarto = (Quarto *)malloc(sizeof(Quarto));
        if (quarto == NULL)
        {
            printf("\n\tErro na alocação de memoria!\n");
            exit(1);
        }

        fscanf(arq, "%s\n%d\n%d\n%f\n%d\n", hAux->nome, &hAux->quantidade, &hAux->estadia, &hAux->documento, &index);
        hAux->quarto = quarto;
        hAux->quarto = q[index - 1];
        hAux->prox = NULL;

        if (head == NULL)
        {
            head = hAux;
            tail = hAux;
        }
        else
        {
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

Hospede *editar_reserva(Hospede *h, Quarto **q)
{
    Hospede *aux = (Hospede *)malloc(sizeof(Hospede));
    char nome[81];
    int op, estadia, numero, quantidade;
    float documento;

    imprime_reserva(h);

    printf("\n\tDigite o numero do quarto do responsavel que deseja fazer a edicao: ");
    scanf("%d", &numero);

    printf("\n\tO que deseja editar?\n\t\t1 - Nome\n\t\t2 - Duracao da estadia\n\t\t3 - Documento\n\t\t4 - Quarto ");
    scanf("%d", &op);

    if (op == 1)
    {
        aux = busca_reserva(numero, h);
        estadia = aux->estadia;
        documento = aux->documento;
        quantidade = aux->quantidade;
        h = exclui_reserva(h, numero);
        printf("\n\tTudo certo, agora digite o novo nome do responsavel: ");
        scanf(" %[^\n]", nome);
        strcpy(nome, transforma_nome(nome));
        h = cria_reserva(h, q[numero - 1], nome, estadia, quantidade, documento);
        escreve_lista(h);
        return h;
    }

    else if (op == 2)
    {
        aux = busca_reserva(numero, h);
        strcpy(nome, aux->nome);
        documento = aux->documento;
        quantidade = aux->quantidade;
        h = exclui_reserva(h, numero);
        printf("\n\tTudo certo, agora digite a nova duracao da estadia: ");
        scanf("%d", &estadia);
        h = cria_reserva(h, q[numero - 1], nome, estadia, quantidade, documento);
        escreve_lista(h);
        return h;
    }

    else if (op == 3)
    {
        aux = busca_reserva(numero, h);
        strcpy(nome, aux->nome);
        estadia = aux->estadia;
        quantidade = aux->quantidade;
        h = exclui_reserva(h, numero);
        printf("\n\tTudo certo, agora digite o novo numero do documento: ");
        scanf("%f", &documento);
        h = cria_reserva(h, q[numero - 1], nome, estadia, quantidade, documento);
        escreve_lista(h);
        return h;
    }

    else if (op == 4)
    {
        aux = busca_reserva(numero, h);
        strcpy(nome, aux->nome);
        estadia = aux->estadia;
        quantidade = aux->quantidade;
        documento = aux->documento;
        strcpy(aux->quarto->disponibilidade, "DISPONIVEL");
        h = exclui_reserva(h, numero);
        exibir_quartos_disponiveis(q);
        printf("\n\tTudo certo, agora digite o  numero do novo quarto que deseja se hospedar: ");
        scanf("%d", &numero);
        h = cria_reserva(h, q[numero - 1], nome, estadia, quantidade, documento);
        escreve_lista(h);
        escreve_quarto(q);
        return h;
    }
}
