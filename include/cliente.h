#ifndef CLIENTE_H
#define CLIENTE_H

typedef enum {
    CLIENTE_VALIDO,
    CLIENTE_INVALIDO,
} Status_Cliente;

typedef struct {
    int id;
    char nome[60];
    char cpf[12];
    char telefone[11];
    Status_Cliente status;
    int quantidade_pedidos;
} Cliente;

Cliente criar_cliente(int id, char *nome, char *cpf, char *telefone);

#endif