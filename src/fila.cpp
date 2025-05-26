#include "fila.h"
#include "tarefa.h"

void inicializar_fila(Fila *fila) {
    fila->inicio = 0;
    fila->fim = -1;
    fila->tamanho = 0;
}

void enfileirar(Fila *fila, Tarefa *tarefa) {
    if (!fila_cheia(fila)) {
        fila->fim = (fila->fim + 1) % 100;
        fila->dados[fila->fim] = tarefa;
        fila->tamanho++;
    }
}

Tarefa* desenfileirar(Fila *fila) {
    if (!fila_vazia(fila)) {
        Tarefa *tarefa = fila->dados[fila->inicio];
        fila->inicio = (fila->inicio + 1) % 100;
        fila->tamanho--;
        return tarefa;
    }
    return nullptr;
}

int fila_vazia(Fila *fila) {
    return fila->tamanho == 0;
}

int fila_cheia(Fila *fila) {
    return fila->tamanho == 100;
}
