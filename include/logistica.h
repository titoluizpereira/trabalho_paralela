#ifndef LOGISTICA_H
#define LOGISTICA_H

#include "pedido.h"
#include "fila.h"

typedef struct {
    Fila* fila_entrada;
      double taxa_falha;
} ValidadorLogistica;

int validar_logistica(Pedido* pedido, double taxa_falha);

void* executar_logistica(void* arg);

#endif