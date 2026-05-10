#include <stdio.h>
#include <string.h>
#include "pedido.h"


Pedido criar_pedido(int id, int cliente_id, int item_id){
    Pedido p;

    p.id = id;
    p.cliente_id = cliente_id;
    p.item_id = item_id;
   
    p.status = PEDIDO_VALIDADO;

    return p;
}