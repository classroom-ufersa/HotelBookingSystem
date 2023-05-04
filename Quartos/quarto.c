#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "quarto.h"

#define MAX_QUARTOS 50

struct quarto
{
  int numero;
  char disponibilidade[81];
  float preco;
  char localizacao[81];
};

Quarto *captura_quartos(int n, char disp[81], float preco, char local[81])
{
  Quarto *temp = (Quarto *)malloc(sizeof(Quarto));
  temp->numero = n;
  strcpy(temp->disponibilidade, disp);
  temp->preco = preco;
  strcpy(temp->localizacao, local);
  return temp;
}

void escreve_quarto(Quarto **quartos)
{
  int index = 0;
  FILE *file_quartos;
  file_quartos = fopen("../dados/Quartos.txt", "w");
  if (file_quartos == NULL)
  {
    printf("Nao foi possivel abrir o arquivo de quartos cadastrados.\n");
    exit(1);
  }

  for (index = 0; index < MAX_QUARTOS; index++)
  {
    fprintf(file_quartos, "%d\t%s\t%f\t%s\n", quartos[index]->numero, quartos[index]->disponibilidade, quartos[index]->preco, quartos[index]->localizacao);
  }

  fclose(file_quartos);
}

void exibir_quartos(Quarto **q)
{
  int i;
  printf("\t----- LISTA DE QUARTOS DISPONIVEIS PARA RESERVA -----\n");
  for (i = 0; i < MAX_QUARTOS; i++)
  {
    printf("\tN do quarto: %d\n\tDisponibilidade: %s\n\tPreco: %.0f\n\tLocalizacao: %s\n", q[i]->numero, q[i]->disponibilidade, q[i]->preco, q[i]->localizacao);
    printf("\t---------------------\n");
  }
}

int verifica_quarto(Quarto **q, int numero)
{
  int i;
  for (i = 0; i < MAX_QUARTOS; i++)
  {
    if ((q[i]->numero == numero) && (strcmp(q[i]->disponibilidade, "OCUPADO") == 0))
    {
      printf("\n\tDesculpe, o quarto %d esta ocupado.\n\n", numero);
      return 1;
    }
  }
  return 0;
}