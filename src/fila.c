#include <stdio.h>

#include "fila.h"

void fila_inicializar(Fila *fila) {
    fila->fila_inicio = 0;
    fila->fila_fim = 0;
    fila->quantidade = 0;

    pthread_mutex_init(
        &fila->mutex,
        NULL
    );

    pthread_cond_init(
        &fila->condicao_n_vazia,
        NULL
    );

    pthread_cond_init(
        &fila->condicao_n_cheia,
        NULL
    );
}

int fila_esta_vazia(Fila *fila) {
    return fila->quantidade == 0;
}

int fila_esta_cheia(Fila *fila) {
    return fila->quantidade == TAMANHO_FILA;
}

void fila_inserir(Fila *fila,Pedido pedido) {
    pthread_mutex_lock(&fila->mutex);

    while (fila_esta_cheia(fila)) {
        pthread_cond_wait(
            &fila->condicao_n_cheia,
            &fila->mutex
        );
    }

    fila->pedidos[fila->fila_fim] = pedido;

    fila->fila_fim =
        (fila->fila_fim + 1) % TAMANHO_FILA;

    fila->quantidade++;

    pthread_cond_signal(
        &fila->condicao_n_vazia
    );

    pthread_mutex_unlock(&fila->mutex);
}

Pedido fila_remover(Fila *fila) {
    pthread_mutex_lock(&fila->mutex);

    while (fila_esta_vazia(fila)) {
        pthread_cond_wait(
            &fila->condicao_n_vazia,
            &fila->mutex
        );
    }

    Pedido pedido =
        fila->pedidos[fila->fila_inicio];

    fila->fila_inicio =
        (fila->fila_inicio + 1) % TAMANHO_FILA;

    fila->quantidade--;

    pthread_cond_signal(
        &fila->condicao_n_cheia
    );

    pthread_mutex_unlock(&fila->mutex);

    return pedido;
}

void fila_destruir(Fila *fila) {
    pthread_mutex_destroy(
        &fila->mutex
    );

    pthread_cond_destroy(
        &fila->condicao_n_vazia
    );

    pthread_cond_destroy(
        &fila->condicao_n_cheia
    );
}