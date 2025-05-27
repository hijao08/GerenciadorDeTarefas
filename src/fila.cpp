#include "fila.h"
#include <stdio.h>
#include <stdlib.h>

void inicializar_fila(Fila* fila) {
    fila->elementos = (Tarefa**)malloc(MAX_FILA * sizeof(Tarefa*));
    if (fila->elementos == NULL) {
        printf("Erro ao alocar memória para a fila!\n");
        exit(1);
    }
    fila->frente = 0;
    fila->tras = -1;
    fila->capacidade = MAX_FILA;
    fila->tamanho_atual = 0;
}

void destruir_fila(Fila* fila) {
    free(fila->elementos);
    fila->elementos = NULL;
    fila->frente = 0;
    fila->tras = -1;
    fila->capacidade = 0;
    fila->tamanho_atual = 0;
}

void enfileirar(Fila* fila, Tarefa* elemento) {
    if (!fila_cheia(fila)) {
        fila->tras = (fila->tras + 1) % fila->capacidade;
        fila->elementos[fila->tras] = elemento;
        fila->tamanho_atual++;
    } else {
        printf("Erro: Fila cheia!\n");
    }
}

Tarefa* desenfileirar(Fila* fila) {
    if (!fila_vazia(fila)) {
        Tarefa* elemento = fila->elementos[fila->frente];
        fila->frente = (fila->frente + 1) % fila->capacidade;
        fila->tamanho_atual--;
        return elemento;
    }
    printf("Erro: Fila vazia!\n");
    return NULL;
}

Tarefa* primeiro_fila(Fila* fila) {
    if (!fila_vazia(fila)) {
        return fila->elementos[fila->frente];
    }
    return NULL;
}

int fila_vazia(Fila* fila) {
    return fila->tamanho_atual == 0;
}

int fila_cheia(Fila* fila) {
    return fila->tamanho_atual == fila->capacidade;
}

int tamanho_fila(Fila* fila) {
    return fila->tamanho_atual;
} 