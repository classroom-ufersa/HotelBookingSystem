#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#include "Hospede/hospede.c"

#define MAX_QUARTOS 50

int main()
{
    int numero = 0, estadia = 0, quantidade = 0, vagas = MAX_QUARTOS, index = 0;
    char disponibilidade[81], localizacao[81], nome[81];
    float preco = 0, documento = 0;

    Hospede *lista_hospedes;

    Quarto *quartos[MAX_QUARTOS];
    FILE *q;
    q = fopen("../dados/Quartos.txt", "r");
    if (q == NULL)
    {
        printf("Nao foi possivel abrir o arquivo de quartos cadastrados.\n");
        exit(1);
    }

    // Ler os quartos do arquivo
    while (!(feof(q)))
    {
        fscanf(q, "%d\t%[^\t]\t%f\t%[^\n]", &numero, disponibilidade, &preco, localizacao);
        // printf("%d %s %f %s", numero, disponibilidade, preco, localizacao);
        quartos[index] = captura_quartos(numero, disponibilidade, preco, localizacao);
        // printf("N do quarto: %d\nDisponibilidade: %s\nPreco: %.0f\nLocalizacao: %s\n", quartos[index]->numero, quartos[index]->disponibilidade, quartos[index]->preco, quartos[index]->localizacao);
        index++;
    }
    fclose(q);

    printf("Bem vindo ao servico de hotelaria de Lucas Emanuel e Murilo Fontes\n");
    int op;
    lista_hospedes = inicializa_reserva();
    do
    {
        printf("\tOpcoes disponiveis no programa:\n\n\t1 - Realizar reserva\n\t2 - Exluir reserva\n\t3 - Listar Reservas\n\t4 - Buscar reserva\n\t5 - Editar reserva\n\t6 - Consultar quartos disponiveis\n\t7 - Consultar quantitativo de hospedes\n\t8 - Sair\n\n\tQual opcao deseja fazer: ");
        scanf("%d", &op);
        switch (op)
        {
        case 1:
            if (vagas > 0)
            {
                int i;
                printf("\n\tRealizando reserva...\n");
                printf("Digite o nome do responsavel:\n");
                scanf(" %[^\n]", nome);
                printf("Digite seu numero de RG ou CPF:\n");
                scanf("%f", &documento);
                exibir_quartos(quartos);
                printf("Qual o numero do quarto em que deseja se hospedar?\n");
                scanf("%d", &numero);

                // está faltando verificar se o quarto ja esta ocupado. teste abaixo

                /* for(i = 0; i < MAX_QUARTOS; i++)
                {
                    if((quartos[i] == numero) && (strcmp(quartos[i]->disponibilidade, "OCUPADO") == 0))
                    {
                        printf("Desculpe, o quarto %d esta ocupado.\n", numero);
                        break;
                    }
                } */

                printf("Reserva para quantas pessoas?\n");
                scanf("%d", &quantidade);
                strcpy(quartos[numero - 1]->disponibilidade, "INDISPONIVEL");
                printf("Reservando o quarto %d.\nPor quantos dias deseja se hospedar?\n", numero);
                scanf("%d", &estadia);
                lista_hospedes = cria_reserva(lista_hospedes, quartos[numero - 1], nome, estadia, quantidade, documento);
                printf("Reserva para o quarto %d criada com sucesso!\n", numero);
                break;

                // esta faltando uma funçao para atualizar o arquivo dizendo o numero do quarto que ficou ocupado
            }
            else
            {
                printf("Desculpe! Nao ha vagas disponiveis para reserva no momento.\n");
                break;
            }

        case 2:
            printf("\n\tExcluindo reserva...\n");
            printf("Digite o numero do quarto para excluir sua reserva:\n");
            scanf("%d", &numero);
            lista_hospedes = exclui_reserva(lista_hospedes, numero);
            printf("Reserva do quarto %d excluida com sucesso! Volte sempre.\n", numero);
            break;

        case 3:
            printf("\n\tListando reservas...\n");
            imprime_reserva(lista_hospedes);
            break;
        case 4:
            printf("\n\tBuscando reservas...\n");
            printf("Digite o numero do quarto que deseja exibir as informacoes da reserva associada a ele:\n");
            scanf("%d", &numero);
            lista_hospedes = busca_reserva(numero, lista_hospedes);
            break;

        case 5:
            printf("\n\tEditando reserva...\n");
            break;

        case 6:
            printf("\n\tConsultando quartos disponiveis...\n");
            exibir_quartos(quartos);

            break;
        case 7:
            printf("\n\tConsultando quantidade de hospedes...\n");
            consulta_quantitativo(lista_hospedes);
            break;

        case 8:
            printf("\n\tObrigado por utilizar nosso programa!\n");
            libera_reserva(lista_hospedes);
            break;
        }
    } while (op != 8);
}