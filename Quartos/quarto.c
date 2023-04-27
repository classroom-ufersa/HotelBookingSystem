#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_QUARTOS 50

typedef struct quarto
{
  int numero;
  char disponibilidade[81];
  float preco;
  char localizacao[81];
} Quarto;

Quarto *captura_quartos(int n, char disp[81], float preco, char local[81])
{
  Quarto *temp = (Quarto *)malloc(sizeof(Quarto));
  temp->numero = n;
  strcpy(disp, temp->disponibilidade);
  temp->preco = preco;
  strcpy(local, temp->localizacao);
  return temp;
}

void exibir_quartos(Quarto *q[])
{
  int i;
  for (i = 0; i < MAX_QUARTOS; i++)
  {
    printf("N do quarto: %d\n", q[i]->numero);
  }
}