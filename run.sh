#!/bin/bash

gcc \
src/main.c \
src/sistema.c \
src/cliente.c \
src/pedido.c \
src/item.c \
-Iinclude \
-o app

if [ $? -eq 0 ]; then
    ./app
else
    echo "Erro ao compilar."
fi