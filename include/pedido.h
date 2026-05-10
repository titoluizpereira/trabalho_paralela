#ifndef PEDIDO_H
#define PEDIDO_H

typedef enum
{
    PEDIDO_CRIADO,
    PEDIDO_VALIDADO,
    CLIENTE_VALIDADO,
    ERRO_VALIDADE,
    PEDIDO_FINANCEIRO_APROVADO,
    ERRO_FINANCEIRO,
    ERRO_LOGISTICA,
    PEDIDO_REALIZADO,
} Status_Pedido;

typedef struct {
    int id;
    int cliente_id;
    int item_id;
    Status_Pedido status;
} Pedido;

Pedido criar_pedido(int id, int cliente_id, int item_id);

#endif