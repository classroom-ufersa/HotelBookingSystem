#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#include "Quartos/quarto.h"

#define MAX_QUARTOS 50

int main()
{
    int numero, index = 0;
    char disponibilidade[81], localizacao[81];
    float preco;

    Quarto *quartos[MAX_QUARTOS];

    FILE *q;
    q = fopen("../dados/Quartos.txt", "r");
    if (q == NULL)
    {
        printf("Nao foi possivel criar o aluno!\n");
        exit(1);
    }
    while (!(feof(q)))
    {
        fscanf(q, "%d\t%[^\t]\t%f\t%[^\t]", &numero, disponibilidade, &preco, localizacao);
        quartos[index] = captura_quartos(numero, disponibilidade, preco, localizacao);
        index++;
    }
    fclose(q);

    printf("Bem vindo ao servico de hotelaria de Lucas Emanuel e Murilo Fontes\n");
    int op;
    do
    {
        printf("\tOpcoes disponiveis no programa:\n\n\t1 - Realizar reserva\n\t2 - Exluir reserva\n\t3 - Listar Reservas\n\t4 - Buscar reserva\n\t5 - Editar reserva\n\t6 - Consultar quartos disponiveis\n\t7 - Consultar quantitativo de hospedes\n\t8 - Sair\n\n\tQual opcao deseja fazer: ");
        scanf("%d", &op);
        switch (op)
        {
        case 1:
            printf("\n\tRealizando reserva...\n");
            break;
        case 2:
            printf("\n\tExcluindo reserva...\n");
            break;
        case 3:
            printf("\n\tListando reservas...\n");
            break;
        case 4:
            printf("\n\tBuscando reservas...\n");
            break;
        case 5:
            printf("\n\tEditando reserva...\n");
            break;
        case 6:
            printf("\n\tConsultando quartos disponiveis...\n");
            printf("Quartos disponiveis:\n");
            exibir_quartos(quartos);
            break;
        case 7:
            printf("\n\tConsultando quantidade de hospedes...\n");
            break;
        case 8:
            printf("\n\tSaindo...\n");
            break;
        }
    } while (op != 8);
}