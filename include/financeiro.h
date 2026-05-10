#ifndef FINANCEIRO_H
#define FINANCEIRO_H

#include "pedido.h"
#include "fila.h"

typedef struct {
    Fila* fila_entrada;
    Fila* fila_saida;
    double taxa_falha;
} ValidadorFinanceiro;

int validar_financeiro(Pedido* pedido, double taxa_falha);

void* executar_financeiro(void* arg);

#endif