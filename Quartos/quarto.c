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


/* Função merda do krai */
Quarto * captura_quartos(int n, char disp[81], float preco, char local[81])
{
  Quarto *temp = (Quarto *)malloc(sizeof(Quarto));
  temp->numero = n;
  strcpy(temp->disponibilidade, disp);
  temp->preco = preco;
  strcpy(temp->localizacao, local);
  return temp;
}

void exibir_quartos(Quarto **q)
{
  int i;
  for (i = 0; i < MAX_QUARTOS; i++)
  {
    printf("N do quarto: %d\nDisponibilidade: %s\nPreco: %.0f\nLocalizacao: %s\n", q[i]->numero, q[i]->disponibilidade, q[i]->preco, q[i]->localizacao);
  }
}

void criar_Quarto()
{
    int numero;
    char disponibilidade[81];
    float preco;
    char localizacao[81];

    FILE *f = fopen("../dados/Quartos.txt", "a");
    if (f == NULL)
    {
        printf("Nao foi possivel abrir o arquivo!\n");
        exit(1);
    }

    printf("Digite o numero do quarto: ");
    scanf("%d", &numero);
    printf("Digite a disponibilidade do quarto: ");
    scanf(" %[^\n]s", disponibilidade);
    printf("Digite o preco do quarto: ");
    scanf("%f", &preco);
    printf("Digite a localizacao do quarto: ");
    scanf(" %[^\n]s", localizacao);

    fprintf(f, "%d\t%s\t%f\t%s\n", numero, disponibilidade, preco, localizacao);
    fclose(f);
}