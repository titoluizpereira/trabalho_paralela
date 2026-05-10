#ifndef VALIDACAO_H
#define VALIDACAO_H

#include "pedido.h"
#include "fila.h"

typedef struct {
    Fila* fila_entrada;
    Fila* fila_saida;
    double taxa_falha;
} ValidadorPedido;

int validar_pedido(Pedido* pedido, double taxa_falha);

void* executar_validacao(void* arg);

#endif