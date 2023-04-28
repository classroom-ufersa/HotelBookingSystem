#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#include "Quartos/quarto.c"
#include "Hospede/hospede.c"

#define MAX_QUARTOS 50

int main()
{
    int numero;
    char disponibilidade[81], localizacao[81];
    float preco;

    Quarto *quartos[MAX_QUARTOS];

    FILE *q;
    q = fopen("../dados/Quartos.txt", "r");
    if (q == NULL)
    {
        printf("Nao foi possivel abrir o arquivo de quartos cadastrados.\n");
        exit(1);
    }    
    fscanf(q, "%d\t%[^\t]\t%f\t%[^\n]", &numero, disponibilidade, &preco, localizacao);
    printf("\n%d\n", numero);
    printf("%s\n", disponibilidade);
    printf("%f\n", preco);
    printf("%s\n", localizacao);

    strcpy(quartos[0]->disponibilidade, disponibilidade); 
    strcpy(quartos[0]->localizacao, localizacao);
    quartos[0]->numero = numero;
    quartos[0]->preco = preco; 
    
    /* while (!(feof(q)))
    { 
        fscanf(q, "%d\t%[^\t]\t%f\t%[^\t]", &numero, disponibilidade, &preco, localizacao);
        printf("%d %s %f %s", numero, disponibilidade, preco, localizacao);
        //quartos[index] = captura_quartos(numero, disponibilidade, preco, localizacao);
        //printf("N do quarto: %d\nDisponibilidade: %s\nPreco: %.0f\nLocalizacao: %s\n", quartos[index]->numero, quartos[index]->disponibilidade, quartos[index]->preco, quartos[index]->localizacao);
        index++;
    } */
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
            criar_Quarto();
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
            int h = 0;
            for (h = 0; h < 5; h++)
            {
                printf("N do quarto: %d\nDisponibilidade: %s\nPreco: %.0f\nLocalizacao: %s\n", quartos[h]->numero, quartos[h]->disponibilidade, quartos[h]->preco, quartos[h]->localizacao);
            }
            
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