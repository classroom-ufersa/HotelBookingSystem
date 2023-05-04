#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#include "Hospede/hospede.c"

#define MAX_QUARTOS 50

int main()
{
    int numero = 0, estadia = 0, quantidade = 0, index = 0, i;
    char disponibilidade[81], localizacao[81], nome[81];
    float preco = 0, documento = 0;

    Hospede *lista_hospedes;
    Hospede *resultado_busca;

    Quarto *quartos[MAX_QUARTOS];
    FILE *q;
    q = fopen("../dados/Quartos.txt", "r");
    if (q == NULL)
    {
        printf("Nao foi possivel abrir o arquivo de quartos cadastrados.\n");
        exit(1);
    }

    FILE *arq;
    arq = fopen("../dados/ListaReservas.txt", "r");
    if (arq == NULL)
    {
        printf("Nao foi possivel abrir o arquivo de quartos cadastrados.\n");
        exit(1);
    }

    // Ler os quartos do arquivo
    while (!(feof(q)))
    {
        fscanf(q, "%d\t%[^\t]\t%f\t%[^\n]", &numero, disponibilidade, &preco, localizacao);
        quartos[index] = captura_quartos(numero, disponibilidade, preco, localizacao);
        index++;
    }
    fclose(q);

    printf("Bem vindo ao servico de hotelaria de Lucas Emanuel e Murilo Fontes\n");
    int op;
    //mesmo o arquivo estando vazio, ele entra no if. Porque?
    if (!(feof(arq)))
    {
        lista_hospedes = ler_lista(lista_hospedes, quartos);
        printf("arquivo lido com sucesso\n");
    }
    else
    {
        lista_hospedes = inicializa_reserva();
        printf("arquivo vazio\n");
    }
    fclose(arq);
    do
    {
        printf("\tOpcoes disponiveis no programa:\n\n\t1 - Realizar reserva\n\t2 - Exluir reserva\n\t3 - Listar Reservas\n\t4 - Buscar reserva\n\t5 - Editar reserva\n\t6 - Consultar quartos disponiveis\n\t7 - Consultar quantitativo de hospedes\n\t8 - Sair\n\n\tQual opcao deseja fazer: ");
        scanf("%d", &op);
        switch (op)
        {
        case 1:
            exibir_quartos_disponiveis(quartos);
            printf("\tQual o numero do quarto em que deseja se hospedar? ");
            scanf("%d", &numero);
            // como fazer melhor?
            i = verifica_quarto(quartos, numero);
            if (i == 1)
            {
                break;
            }
            printf("\n\tRealizando reserva...\n");
            printf("\tDigite o nome do responsavel: ");
            scanf(" %[^\n]", nome);
            strcpy(nome, transforma_nome(nome));
            printf("\tDigite seu numero de RG ou CPF: ");
            scanf("%f", &documento);
            printf("\tReserva para quantas pessoas? ");
            scanf("%d", &quantidade);
            strcpy(quartos[numero - 1]->disponibilidade, "OCUPADO");
            printf("\tReservando o quarto %d.\n\tPor quantos dias deseja se hospedar? ", numero);
            scanf("%d", &estadia);
            lista_hospedes = cria_reserva(lista_hospedes, quartos[numero - 1], nome, estadia, quantidade, documento);
            printf("\tReserva para o quarto %d criada com sucesso!\n", numero);
            escreve_quarto(quartos);
            escreve_lista(lista_hospedes);
            printf("%s", nome);
            break;

        case 2:
            printf("\n\tExcluindo reserva...\n");
            printf("Digite o numero do quarto para excluir sua reserva:\n");
            scanf("%d", &numero);
            lista_hospedes = exclui_reserva(lista_hospedes, numero);
            printf("Reserva do quarto %d excluida com sucesso! Volte sempre.\n", numero);
            break;

        case 3:
            if (lista_hospedes == NULL)
            {
                printf("\t\nNao ha reservas cadastradas!\n\n");
                break;
            }
            printf("\n\tListando reservas...\n");
            imprime_reserva(lista_hospedes);
            break;

        case 4:
            printf("\n\tBuscando reservas...\n");
            printf("Digite o numero do quarto que deseja exibir as informacoes da reserva associada a ele:\n");
            scanf("%d", &numero);

            resultado_busca = busca_reserva(numero, lista_hospedes);
            if (resultado_busca == NULL)
            {
                printf("\tReserva nao encontrada.\n");
                break;
            }
            printf("%s", resultado_busca->nome);
            break;

        case 5:
            printf("\n\tEditando reserva...\n");
            lista_hospedes = editar_reserva(lista_hospedes, quartos);
            break;

        case 6:
            printf("\n\tConsultando quartos disponiveis...\n");
            exibir_quartos_disponiveis(quartos);
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