/*
#ifndef TPOOL_H
#define TPOOL_H

#include <stdbool.h>
#include <stddef.h>

struct tpool;
typedef struct tpool tpool_t;

typedef void (*thread_func_t)(void *arg);

tpool_t *tpool_create(size_t num);
void tpool_destroy(tpool_t *tm);

bool tpool_add_work(tpool_t *tm, thread_func_t func, void *arg);
void tpool_wait(tpool_t *tm);

#endif

*/

#ifndef TPOOL_H
#define TPOOL_H

#include <pthread.h>
#include <stdbool.h>

#include "fila.h"

typedef struct {
    pthread_t *threads;

    int quantidade_threads;

    bool parar;

    Fila *fila;
} ThreadPool;

ThreadPool *tpool_criar(
    int quantidade_threads,
    Fila *fila
);

void tpool_destruir(
    ThreadPool *pool
);

#endif