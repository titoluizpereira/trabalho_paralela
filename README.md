# T1: Programação Concorrente - Fluxo de trabalho para um sistema de vendas

Trabalho realizado para a disciplina Programação Paralela e Distribuída (INE5645)

O projeto simula um sistema de fluxo de vendas. Foi desenvolvido em linguagem C utilizando POSIX Threads (`pthread`) para figurar um ambiente concorrente de processamento de pedidos.

Na simulação, os cliente realizam pedidos que passam por múltiplas e independentes etapas de processamento, como validação do pedido, análise financeira e processamento logístico. 

O sistema foi desenvolvido com foco na aplicação de conceitos de programação paralela, sincronização entre threads e comunicação concorrente através de filas compartilhadas.

## Padrões Paralelos Utilizados

A arquitetura do trabalho foi organizada aplicando três padrões de projeto indicados para programação multithread: 

### Produtor/Consumidor

Utilizado para controlar a comunicação entre as etapas do sistema através de filas sincronizadas. Enquanto uma parte do sistema produz pedidos e os insere nas filas, outras threads consomem esses pedidos para processamento.

### Suspensão Controlada

Tem a finalidade de threads de forma segura quando não existem pedidos disponíveis para processamento. As threads permanecem bloqueadas até que novos pedidos sejam inseridos nas filas.

### Pool de Threads

Utilizado para reutilizar múltiplas threads trabalhadoras durante o processamento concorrente dos pedidos, evitando a criação excessiva de novas threads e permitindo gerenciamento mais eficiente das tarefas paralelas.

## Instruções para Compilação

Compilar manualmente:

```bash
gcc src/*.c -Iinclude -o app -pthread
```

Ou utilizar:

```bash
./run.sh
```

## Integrantes

- Patrick Vieira Leite
- Tito Luiz Pereira
- Vitor Andrade Schweitzer
````
