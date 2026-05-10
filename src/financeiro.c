#include "financeiro.h"
#include <stdlib.h>
#include <stdio.h>

int validar_financeiro(Pedido* pedido, double taxa_falha) {

    double chance = (double) rand() / RAND_MAX;

    if (chance < taxa_falha) {

        printf("Pedido %d recusado no financeiro.\n", pedido->id);

        return 0;
    }

    printf("Pedido %d aprovado no financeiro.\n", pedido->id);

    return 1;
}

void* executar_financeiro(void* arg) {

    ValidadorFinanceiro* financeiro = (ValidadorFinanceiro*) arg;

    while (1) {

        Pedido pedido = fila_remover(financeiro->fila_entrada);

        if (validar_financeiro(&pedido, financeiro->taxa_falha)) {

            pedido.status = PEDIDO_FINANCEIRO_APROVADO;

            fila_inserir(financeiro->fila_saida, pedido);

        } else {

            pedido.status = ERRO_FINANCEIRO;
        }
    }

    return NULL;
}