#ifndef ITEM_H
#define ITEM_H


typedef struct {
    int id;
    int valor;
    char nome[60];;
} Item;

Item criar_item(int id, int valor, char *nome);

#endif