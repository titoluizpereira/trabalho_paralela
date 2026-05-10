#include <stdio.h>
#include <string.h>
#include "cliente.h"


Cliente criar_cliente(int id, char *nome, char *cpf, char *telefone){
    Cliente c;

    c.id = id;
    strcpy(c.nome, nome);
    strcpy(c.cpf, cpf);
    strcpy(c.telefone, telefone);

    c.status = CLIENTE_VALIDO;
    c.quantidade_pedidos = 0;

    return c;
}