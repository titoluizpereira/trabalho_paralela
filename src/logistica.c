#include "logistica.h"
#include <stdlib.h>
#include <stdio.h>

int validar_logistica(Pedido* pedido, double taxa_falha) {

    double chance = (double) rand() / RAND_MAX;

    if (chance < taxa_falha) {

        printf("Falha na entrega do pedido %d.\n", pedido->id);

        return 0;
    }

    printf("Pedido %d entregue com sucesso.\n", pedido->id);

    return 1;
}

void* executar_logistica(void* arg) {

    ValidadorLogistica* logistica = (ValidadorLogistica*) arg;

    while (1) {

        Pedido pedido = fila_remover(logistica->fila_entrada);

        if (validar_logistica(&pedido, logistica->taxa_falha)) {

            pedido.status = PEDIDO_REALIZADO;

        } else {

            pedido.status = ERRO_LOGISTICA;
        }
    }

    return NULL;
}