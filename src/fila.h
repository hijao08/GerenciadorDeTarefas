// fila.h
#include "tarefa.h"

typedef struct {
    Tarefa *dados[100];
    int inicio;
    int fim;
    int tamanho;
} Fila;

void inicializar_fila(Fila *fila);
void enfileirar(Fila *fila, Tarefa *tarefa);
Tarefa* desenfileirar(Fila *fila);
int fila_vazia(Fila *fila);
int fila_cheia(Fila *fila);
