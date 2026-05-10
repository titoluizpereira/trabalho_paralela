#ifndef FILA_H
#define FILA_H

#include <pthread.h>

#include "pedido.h"

#define TAMANHO_FILA 8

typedef struct {
    Pedido pedidos[TAMANHO_FILA];

    int fila_inicio;
    int fila_fim;
    int quantidade;

    pthread_mutex_t mutex;

    pthread_cond_t condicao_n_vazia;
    pthread_cond_t condicao_n_cheia;

} Fila;

void fila_inicializar(Fila *fila);

void fila_inserir(
    Fila *fila,
    Pedido pedido
);

Pedido fila_remover(Fila *fila);

int fila_esta_vazia(Fila *fila);

int fila_esta_cheia(Fila *fila);

void fila_destruir(Fila *fila);

#endif