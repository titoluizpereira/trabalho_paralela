typedef enum {
    PEDIDO_CRIADO,
    PEDIDO_VALIDADO,
    CLIENTE_VALIDADO,
    ERRO_VALIDADE,
    ERRO_FINANCEIRO,
    ERRO_LOGISTICA,
    PEDIDO_REALIZADO,
} Status_Pedido

typedef struct {
    int id;
    int cliente_id;
    int item_id;
    Status_Pedido status;
} Pedido;

Pedido criar_pedido(int cliente_id, int item_id);