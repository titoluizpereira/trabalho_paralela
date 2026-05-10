#ifndef CLIENTE_H
#define CLIENTE_H

#include "pedido.h"
#include "fila.h"

typedef enum {
    CLIENTE_VALIDO,
    CLIENTE_INVALIDO,
} Status_Cliente;

typedef struct {
    int cliente_id;
    char nome[60];
    char cpf[12];
    char telefone[11];
    Status_Cliente status_cliente;
    int quantidade_pedidos;
} Cliente;

Cliente criar_cliente(int cliente_id, char nome, char cpf, char telefone);

#endif