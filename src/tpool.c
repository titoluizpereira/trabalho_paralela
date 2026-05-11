/*
#include "tpool.h"
#include <pthread.h>

struct tpool_work {
    thread_func_t      func;
    void              *arg;
    struct tpool_work *next;
};
typedef struct tpool_work tpool_work_t;

struct tpool {
    tpool_work_t    *work_first;
    tpool_work_t    *work_last;
    pthread_mutex_t  work_mutex;
    pthread_cond_t   work_cond;
    pthread_cond_t   working_cond;
    size_t           working_cnt;
    size_t           thread_cnt;
    bool             stop;
};

static tpool_work_t *tpool_work_create(thread_func_t func, void *arg) {
    tpool_work_t *work;

    if (func == NULL)
        return NULL;

    work       = malloc(sizeof(*work));
    work->func = func;
    work->arg  = arg;
    work->next = NULL;
    return work;
}

static void tpool_work_destroy(tpool_work_t *work) {
    if (work == NULL)
        return;
    free(work);
}


static tpool_work_t *tpool_work_get(tpool_t *tm) {
    tpool_work_t *work;

    if (tm == NULL)
        return NULL;

    work = tm->work_first;
    if (work == NULL)
        return NULL;

    if (work->next == NULL) {
        tm->work_first = NULL;
        tm->work_last  = NULL;
    } else {
        tm->work_first = work->next;
    }
    return work;
}

static void *tpool_worker(void *arg) {
    tpool_t      *tm = arg;
    tpool_work_t *work;

    while (1) {
        pthread_mutex_lock(&(tm->work_mutex));

        while (tm->work_first == NULL && !tm->stop)
            pthread_cond_wait(&(tm->work_cond), &(tm->work_mutex));

        if (tm->stop)
            break;

        work = tpool_work_get(tm);
        tm->working_cnt++;
        pthread_mutex_unlock(&(tm->work_mutex));

        if (work != NULL) {
            work->func(work->arg);
            tpool_work_destroy(work);
        }

        pthread_mutex_lock(&(tm->work_mutex));
        tm->working_cnt--;
        if (!tm->stop && tm->working_cnt == 0 && tm->work_first == NULL)
            pthread_cond_signal(&(tm->working_cond));
        pthread_mutex_unlock(&(tm->work_mutex));
    }

    tm->thread_cnt--;
    pthread_cond_signal(&(tm->working_cond));
    pthread_mutex_unlock(&(tm->work_mutex));
    return NULL;
}

tpool_t *tpool_create(size_t num) {
    tpool_t   *tm;
    pthread_t  thread;
    size_t     i;

    if (num == 0)
        num = 2;

    tm             = calloc(1, sizeof(*tm));
    tm->thread_cnt = num;

    pthread_mutex_init(&(tm->work_mutex), NULL);
    pthread_cond_init(&(tm->work_cond), NULL);
    pthread_cond_init(&(tm->working_cond), NULL);

    tm->work_first = NULL;
    tm->work_last  = NULL;

    for (i=0; i<num; i++) {
        pthread_create(&thread, NULL, tpool_worker, tm);
        pthread_detach(thread);
    }

    return tm;
}

void tpool_destroy(tpool_t *tm) {
    tpool_work_t *work;
    tpool_work_t *work2;

    if (tm == NULL)
        return;

    pthread_mutex_lock(&(tm->work_mutex));
    work = tm->work_first;
    while (work != NULL) {
        work2 = work->next;
        tpool_work_destroy(work);
        work = work2;
    }
    tm->work_first = NULL;
    tm->stop = true;
    pthread_cond_broadcast(&(tm->work_cond));
    pthread_mutex_unlock(&(tm->work_mutex));

    tpool_wait(tm);

    pthread_mutex_destroy(&(tm->work_mutex));
    pthread_cond_destroy(&(tm->work_cond));
    pthread_cond_destroy(&(tm->working_cond));

    free(tm);
}

bool tpool_add_work(tpool_t *tm, thread_func_t func, void *arg) {
    tpool_work_t *work;

    if (tm == NULL)
        return false;

    work = tpool_work_create(func, arg);
    if (work == NULL)
        return false;

    pthread_mutex_lock(&(tm->work_mutex));
    if (tm->work_first == NULL) {
        tm->work_first = work;
        tm->work_last  = tm->work_first;
    } else {
        tm->work_last->next = work;
        tm->work_last       = work;
    }

    pthread_cond_broadcast(&(tm->work_cond));
    pthread_mutex_unlock(&(tm->work_mutex));

    return true;
}

void tpool_wait(tpool_t *tm) {
    if (tm == NULL)
        return;

    pthread_mutex_lock(&(tm->work_mutex));
    while (1) {
        if (tm->work_first != NULL || (!tm->stop && tm->working_cnt != 0) || (tm->stop && tm->thread_cnt != 0)) {
            pthread_cond_wait(&(tm->working_cond), &(tm->work_mutex));
        } else {
            break;
        }
    }
    pthread_mutex_unlock(&(tm->work_mutex));
}
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "tpool.h"
#include "financeiro.h"
#include "logistica.h"


static void processar_pedido(Pedido *pedido) {

    printf(
        "\n[WORKER] Processando pedido %d\n",
        pedido->id
    );

    sleep(1);

    int financeiro_aprovado =
        validar_financeiro(
            pedido,
            0.2
        );

    if (!financeiro_aprovado) {

        pedido->status =
            ERRO_FINANCEIRO;

        printf(
            "[WORKER] Pedido %d finalizado com erro financeiro\n",
            pedido->id
        );

        return;
    }

    pedido->status =
        PEDIDO_FINANCEIRO_APROVADO;

    sleep(1);

    int logistica_aprovada =
        validar_logistica(
            pedido,
            0.2
        );

    if (!logistica_aprovada) {

        pedido->status =
            ERRO_LOGISTICA;

        printf(
            "[WORKER] Pedido %d finalizado com erro logistica\n",
            pedido->id
        );

        return;
    }

    pedido->status =
        PEDIDO_REALIZADO;

    printf(
        "[WORKER] Pedido %d concluido com sucesso\n",
        pedido->id
    );
}

static void *worker(void *arg) {
    ThreadPool *pool =
        (ThreadPool *) arg;

    while (!pool->parar) {

        Pedido pedido =
            fila_remover(pool->fila);

        processar_pedido(&pedido);
    }

    return NULL;
}

ThreadPool *tpool_criar(
    int quantidade_threads,
    Fila *fila
) {
    ThreadPool *pool =
        malloc(sizeof(ThreadPool));

    pool->quantidade_threads =
        quantidade_threads;

    pool->fila = fila;

    pool->parar = false;

    pool->threads =
        malloc(
            sizeof(pthread_t)
            * quantidade_threads
        );

    for (
        int i = 0;
        i < quantidade_threads;
        i++
    ) {
        pthread_create(
            &pool->threads[i],
            NULL,
            worker,
            pool
        );
    }

    return pool;
}

void tpool_destruir(
    ThreadPool *pool
) {
    pool->parar = true;

    for (
        int i = 0;
        i < pool->quantidade_threads;
        i++
    ) {
        pthread_cond_broadcast(
            &pool->fila->condicao_n_vazia
        );
    }

    for (
        int i = 0;
        i < pool->quantidade_threads;
        i++
    ) {
        pthread_join(
            pool->threads[i],
            NULL
        );
    }

    free(pool->threads);

    free(pool);
}