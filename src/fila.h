#ifndef FILA_H
#define FILA_H

#include "tarefa.h"

#define MAX_FILA 100

typedef struct {
    Tarefa** elementos;
    int frente;
    int tras;
    int capacidade;
    int tamanho_atual;
} Fila;

void inicializar_fila(Fila* fila);
void destruir_fila(Fila* fila);
void enfileirar(Fila* fila, Tarefa* elemento);
Tarefa* desenfileirar(Fila* fila);
Tarefa* primeiro_fila(Fila* fila);
int fila_vazia(Fila* fila);
int fila_cheia(Fila* fila);
int tamanho_fila(Fila* fila);

#endif
