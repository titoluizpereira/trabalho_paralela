#include <stdio.h>
#include <string.h>
#include "item.h"


Item criar_item(int id, int valor, char *nome){
    Item i;

    i.id = id;
    i.valor = valor;
    strcpy(i.nome, nome);

    return i;
}