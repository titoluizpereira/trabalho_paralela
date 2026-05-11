#include <stdio.h>

#include "sistema.h"

static void mostrar_menu() {
    printf("\n");
    printf("-- Sistema De Vendas --\n");
    printf("1 - Cadastrar cliente\n");
    printf("2 - Cadastrar item\n");
    printf("3 - Novo pedido\n");
    //printf("4 - Iniciar entregas\n");
    printf("5 - Mostrar Dados\n");
    printf("0 - Sair\n");
    printf("\n");

    printf("Escolha uma opcao: ");
}

int main() {
    Sistema sistema = iniciar();

    sistema.pool = tpool_criar(4, &sistema.fila_pedidos);

    int opcao;

    do {
        mostrar_menu();

        scanf("%d", &opcao);

        switch (opcao) {

            case 1:
                cadastrar_cliente(&sistema);
                break;

            case 2:
                cadastrar_item(&sistema);
                break;

            case 3:
                cadastrar_pedido(&sistema);
                break;

            case 5:
                printf("Data:");
                mostrar_dados(&sistema);
                break;
                
                case 0:
                printf("Encerrando sistema...\n");
                break;

            default:
                printf("Opcao invalida.\n");
                break;
        }

    } while (opcao != 0);

    if (sistema.pool != NULL) {
        tpool_destruir(sistema.pool);
    }

    return 0;
}