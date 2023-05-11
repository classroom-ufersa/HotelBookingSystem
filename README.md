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

```c
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
```

## Excluir reserva

This function deletes a node from the linked list based on the user's input of which reservation he wants to remove. The removal is based on the number of the room.

```c
Hospede *exclui_reserva(Hospede *h, Quarto ** q, int numero)
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
        strcpy(h->quarto->disponibilidade, "DISPONIVEL");
        h = hAux->prox;
        escreve_lista(h);
        escreve_quarto(q);
    }
    else
    {
        strcpy(ant->prox->quarto->disponibilidade, "DISPONIVEL");
        ant->prox = hAux->prox;
        escreve_lista(h);
        escreve_quarto(q);
    }
    free(hAux);
    return h;
}
```

## Listar reservas

This function returns a list of all current reservations in the hotel, with relevant info such as the name of the person responsible for the reservation, the person's document, the amount of people in the room, the number of the room, and the length of their stay in the hotel.

```c
void imprime_reserva(Hospede *h)
{
    Hospede *hAux;
    for (hAux = h; hAux != NULL; hAux = hAux->prox)
    {
        printf("\tNome do responsavel: %s\n\tTotal de pessoas no quarto: %d\n\tDias hospedados: %d\n\tDocumento: %.0f\n\tNumero do quarto: %d\n\n", hAux->nome, hAux->quantidade, hAux->estadia, hAux->documento, hAux->quarto->numero);
    }
    free(hAux);
}
```

## Buscar reserva

This function allows the user to search for a reservation if given the number of the room he wants to find. The function returns the information of that only room.

```c
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

```

## Editar reserva:

This function allows changes to the attributes of the list.

```c
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
    op = LeInteiro();

    switch (op)
    {
    case 1:
        aux = busca_reserva(numero, h);
        estadia = aux->estadia;
        documento = aux->documento;
        quantidade = aux->quantidade;
        h = exclui_reserva(h, q, numero);
        printf("\n\tTudo certo, agora digite o novo nome do responsavel: ");
        scanf(" %[^\n]", nome);
        strcpy(nome, transforma_nome(nome));
        h = cria_reserva(h, q[numero - 1], nome, estadia, quantidade, documento);
        escreve_lista(h);
        system("cls");
        printf("\tNome do responsavel editado com sucesso!\n\n");
        return h;
        break;
    case 2:
        aux = busca_reserva(numero, h);
        strcpy(nome, aux->nome);
        documento = aux->documento;
        quantidade = aux->quantidade;
        h = exclui_reserva(h, q, numero);
        printf("\n\tTudo certo, agora digite a nova duracao da estadia: ");
        scanf("%d", &estadia);
        h = cria_reserva(h, q[numero - 1], nome, estadia, quantidade, documento);
        escreve_lista(h);
        system("cls");
        printf("\tDuracao da estadia editado com sucesso!\n\n");
        return h;
        break;
    case 3:
        aux = busca_reserva(numero, h);
        strcpy(nome, aux->nome);
        estadia = aux->estadia;
        quantidade = aux->quantidade;
        h = exclui_reserva(h, q, numero);
        printf("\n\tTudo certo, agora digite o novo numero do documento: ");
        scanf("%f", &documento);
        h = cria_reserva(h, q[numero - 1], nome, estadia, quantidade, documento);
        escreve_lista(h);
        system("cls");
        printf("\tNumero do documento editado com sucesso!\n\n");
        return h;
        break;
    case 4:
        aux = busca_reserva(numero, h);
        strcpy(nome, aux->nome);
        estadia = aux->estadia;
        quantidade = aux->quantidade;
        documento = aux->documento;
        strcpy(aux->quarto->disponibilidade, "DISPONIVEL");
        h = exclui_reserva(h, q, numero);
        exibir_quartos_disponiveis(q);
        printf("\n\tTudo certo, agora digite o  numero do novo quarto que deseja se hospedar: ");
        scanf("%d", &numero);
        h = cria_reserva(h, q[numero - 1], nome, estadia, quantidade, documento);
        escreve_lista(h);
        escreve_quarto(q);
        system("cls");
        printf("\tQuarto editado com sucesso!\n\n");
        return h;
        break;
    default:
        system("cls");
        printf("\n\tOpcao invalida, voltando para o menu\n\n");
        return h;
        break;
    }
}
```

## Consultar quartos disponíveis:

This function returns a list of all current available rooms for reservation.

```c
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
```

## Consultar quantidade de hospedes

This function returns the amount of guests currently in the hotel.

```c
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
```

## Sair

This option leaves the program.
