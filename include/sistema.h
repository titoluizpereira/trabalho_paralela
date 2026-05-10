#ifndef SISTEMA_H
#define SISTEMA_H

#include "cliente.h"
#include "pedido.h"
#include "item.h"

#define MAX_CLIENTES 100
#define MAX_PEDIDOS 100
#define MAX_ITENS 100

typedef struct {
    Cliente clientes[MAX_CLIENTES];
    Pedido pedidos[MAX_PEDIDOS];
    Item itens[MAX_ITENS];

    int quantidade_clientes;
    int quantidade_pedidos;
    int quantidade_itens;

} Sistema;

Sistema iniciar();

void cadastrar_cliente(Sistema *s);
void cadastrar_item(Sistema *s);
void cadastrar_pedido(Sistema *s);
void mostrar_dados(Sistema *s);
#endif