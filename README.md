# HotelBookingSystem

This hotel booking system allows for the creation of guests reservations by asking the name of the person responsible for the reservation, their document, the amount of people that are staying, and how many days their stay will last. An archive loads a list of available rooms and the person making the reservation can choose which room they would like to book.

A linked list is then created with the booking information, which is written into a text file for future consultations.

## Topics

- [List of files](#list-of-files)
- [How to run the project](#how-to-run-the-project)
- [Main menu](#main-menu)
- [Realizar reserva](#main-menu)
- [Excluir reserva](#excluir-reserva)
- [Listar reservas](#listar-reservas)
- [Buscar reserva](#buscar-reserva)
- [Editar reserva](#editar-reserva)
- [Consultar quartos disponíveis](#consultar-quartos-disponíveis)
- [Consultar quantidade de hospedes](#consultar-quantidade-de-hospedes)
- [Sair](#sair)

## List of files

- dados
  - ListaReservas.txt
  - Quartos.txt
  - salvos.txt
- Hospede
  - hospede.c
  - hospede.h
- output
  - main.exe
- Quartos
  - quarto.c
  - quarto.h
- main.c
- README.md

## How to run the project

To run this project, get inside the `out`directory and write the `./main` command in the terminal.

## Main menu

- Realizar reserva: creates a new reservation;
- Excluir reserva: deletes a reservation;
- Listar reservas: returns a list of current reservations;
- Buscar reserva: searches for a reservation;
- Editar reserva: edits the information within the reservation;
- Consultar quartos disponíveis: returns a list of available rooms for reservation;
- Consultar quantidade de hospedes: returns the number of current guests in the hotel;
- Sair: leave the program.

## Realizar reserva

This function creates a new reservation. This creates a new node in the linked list, sorted by alphabetical order.

c
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
    printf("%s", nova_reserva->quarto->disponibilidade);
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


## Excluir reserva

This function deletes a node from the linked list based on the user's input of which reservation he wants to remove. The removal is based on the number of the room.

c
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


## Listar reservas

This function returns a list of all current reservations in the hotel, with relevant info such as the name of the person responsible for the reservation, the person's document, the amount of people in the room, the number of the room, and the length of their stay in the hotel.

c
void imprime_reserva(Hospede *h)
{
    Hospede *hAux;
    for (hAux = h; hAux != NULL; hAux = hAux->prox)
    {
        printf("Nome do responsavel: %s\nDias hospedados: %d\nDocumento: %f\nNumero do quarto: %d\n\n", hAux->nome, hAux->estadia, hAux->documento, hAux->quarto->numero);

        // printf("Nome do responsavel: %s | Estadia: %d dias | Documento: %.0f\nQuarto: %d\nQuantidade de pessoas: %d\n\n", hAux->nome, hAux->estadia, hAux->documento, hAux->quarto->numero, hAux->quantidade);
    }
    free(hAux);
}


## Buscar reserva

This function allows the user to search for a reservation if given the number of the room he wants to find. The function returns the information of that only room.

c
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


## Editar reserva:

In progress.

## Consultar quartos disponíveis:

This function returns a list of all current available rooms for reservation.

c
void exibir_quartos_disponiveis(Quarto **q)
{
  int i;
  printf("\t----- LISTA DE QUARTOS DISPONIVEIS PARA RESERVA -----\n");
  for (i = 0; i < MAX_QUARTOS; i++)
  {
    if (strcmp(q[i]->disponibilidade, "DISPONIVEL") == 0)
    {
      printf("\tN do quarto: %d\n\tDisponibilidade: %s\n\tPreco: %.0f\n\tLocalizacao: %s\n", q[i]->numero, q[i]->disponibilidade, q[i]->preco, q[i]->localizacao);
      printf("\t---------------------\n");
    }
  }
}


## Consultar quantidade de hospedes

This function returns the amount of guests currently in the hotel.

c
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


## Sair

This option leaves the program.