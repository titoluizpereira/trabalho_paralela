#include <stdio.h>
#include <string.h>

#include "sistema.h"

static int gerar_id_cliente(Sistema *s) {
    if (s->quantidade_clientes == 0) {
        return 1;
    }

    Cliente ultimo =
        s->clientes[s->quantidade_clientes - 1];

    return ultimo.id + 1;
}

static int gerar_id_item(Sistema *s) {
    if (s->quantidade_itens == 0) {
        return 1;
    }

    Item ultimo =
        s->itens[s->quantidade_itens - 1];

    return ultimo.id + 1;
}

static int gerar_id_pedido(Sistema *s) {
    if (s->quantidade_pedidos == 0) {
        return 1;
    }

    Pedido ultimo =
        s->pedidos[s->quantidade_pedidos - 1];

    return ultimo.id + 1;
}

Sistema iniciar() {
    Sistema s;

    s.quantidade_clientes = 0;
    s.quantidade_pedidos = 0;
    s.quantidade_itens = 0;

    return s;
}

void cadastrar_cliente(Sistema *s) {
    char nome[60];
    char cpf[12];
    char telefone[12];

    int id = gerar_id_cliente(s);

    printf("Nome: ");
    scanf("%59s", nome);

    printf("CPF: ");
    scanf("%11s", cpf);

    printf("Telefone: ");
    scanf("%11s", telefone);

    Cliente cliente =
        criar_cliente(id, nome, cpf, telefone);

    s->clientes[s->quantidade_clientes] = cliente;

    s->quantidade_clientes++;

    printf("Cliente cadastrado com sucesso.\n");
}

void cadastrar_item(Sistema *s) {
    char nome[60];
    int valor;

    int id = gerar_id_item(s);

    printf("Nome do item: ");
    scanf("%59s", nome);

    printf("valor: ");
    scanf("%i", &valor);

    Item item =
        criar_item(id, valor, nome);

    s->itens[s->quantidade_itens] = item;

    s->quantidade_itens++;

    printf("item cadastrado com sucesso.\n");
}

void cadastrar_pedido(Sistema *s) {
    int cliente_id;
    int item_id;

    int cliente_encontrado = 0;
    int item_encontrado = 0;

    while (!cliente_encontrado) {
        printf("ID do cliente: ");
        scanf("%d", &cliente_id);

        for (int i = 0; i < s->quantidade_clientes; i++) {
            if (s->clientes[i].id == cliente_id) {
                cliente_encontrado = 1;
                break;
            }
        }

        if (!cliente_encontrado) {
            printf("Cliente invalido.\n");
        }
    }

    while (!item_encontrado) {
        printf("ID do item: ");
        scanf("%d", &item_id);

        for (int i = 0; i < s->quantidade_itens; i++) {
            if (s->itens[i].id == item_id) {
                item_encontrado = 1;
                break;
            }
        }

        if (!item_encontrado) {
            printf("item invalido.\n");
        }
    }

    int id = gerar_id_pedido(s);

    Pedido pedido =
        criar_pedido(id, cliente_id, item_id);

    pedido.id = id;

    s->pedidos[s->quantidade_pedidos] = pedido;

    s->quantidade_pedidos++;

    printf("Pedido criado com sucesso.\n");
}


void mostrar_dados(Sistema *s) {
    printf("\n");
    printf("========== CLIENTES ==========\n");

    if (s->quantidade_clientes == 0) {
        printf("Nenhum cliente cadastrado.\n");
    }

    for (int i = 0; i < s->quantidade_clientes; i++) {
        Cliente c = s->clientes[i];

        printf("\n");
        printf("ID: %d\n", c.id);
        printf("Nome: %s\n", c.nome);
        printf("CPF: %s\n", c.cpf);
        printf("Telefone: %s\n", c.telefone);
        printf("Quantidade pedidos: %d\n", c.quantidade_pedidos);
    }

    printf("\n");
    printf("========== ITENS ==========\n");

    if (s->quantidade_itens == 0) {
        printf("Nenhum item cadastrado.\n");
    }

    for (int i = 0; i < s->quantidade_itens; i++) {
        Item item = s->itens[i];

        printf("\n");
        printf("ID: %d\n", item.id);
        printf("Nome: %s\n", item.nome);
        printf("Valor: %d\n", item.valor);
    }

    printf("\n");
    printf("========== PEDIDOS ==========\n");

    if (s->quantidade_pedidos == 0) {
        printf("Nenhum pedido cadastrado.\n");
    }

    for (int i = 0; i < s->quantidade_pedidos; i++) {
        Pedido p = s->pedidos[i];

        printf("\n");
        printf("ID: %d\n", p.id);
        printf("Cliente ID: %d\n", p.cliente_id);
        printf("Item ID: %d\n", p.item_id);
        printf("Status: %d\n", p.status);
    }

    printf("\n");
}