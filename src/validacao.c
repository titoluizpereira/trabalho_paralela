#include "validacao.h"
#include <stdlib.h>
#include <stdio.h>

int validar_pedido(Pedido* pedido, double taxa_falha) {

    double chance = (double) rand() / RAND_MAX;

    if (chance < taxa_falha) {

        printf("Pedido %d reprovado na validacao.\n", pedido->id);

        return 0;
    }

    printf("Pedido %d aprovado na validacao.\n", pedido->id);

    return 1;
}

void* executar_validacao(void* arg) {

    ValidadorPedido* validador = (ValidadorPedido*) arg;

    while (1) {

        Pedido pedido = fila_remover(validador->fila_entrada);

        if (validar_pedido(&pedido, validador->taxa_falha)) {

            pedido.status = PEDIDO_VALIDADO;

            fila_inserir(validador->fila_saida, pedido);

        } else {

            pedido.status = ERRO_VALIDADE;
        }
    }

    return NULL;
}