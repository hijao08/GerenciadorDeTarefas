#include "pilha.h"
#include <stdio.h>
#include <stdlib.h>

void inicializar_pilha(Pilha* pilha) {
    pilha->elementos = (Tarefa**)malloc(MAX_PILHA * sizeof(Tarefa*));
    if (pilha->elementos == NULL) {
        printf("Erro ao alocar memória para a pilha!\n");
        exit(1);
    }
    pilha->topo = -1;
    pilha->capacidade = MAX_PILHA;
}

void destruir_pilha(Pilha* pilha) {
    free(pilha->elementos);
    pilha->elementos = NULL;
    pilha->topo = -1;
    pilha->capacidade = 0;
}

void empilhar(Pilha* pilha, Tarefa* elemento) {
    if (!pilha_cheia(pilha)) {
        pilha->topo++;
        pilha->elementos[pilha->topo] = elemento;
    } else {
        printf("Erro: Pilha cheia!\n");
    }
}

Tarefa* desempilhar(Pilha* pilha) {
    if (!pilha_vazia(pilha)) {
        Tarefa* elemento = pilha->elementos[pilha->topo];
        pilha->topo--;
        return elemento;
    }
    printf("Erro: Pilha vazia!\n");
    return NULL;
}

Tarefa* topo_pilha(Pilha* pilha) {
    if (!pilha_vazia(pilha)) {
        return pilha->elementos[pilha->topo];
    }
    return NULL;
}

int pilha_vazia(Pilha* pilha) {
    return pilha->topo == -1;
}

int pilha_cheia(Pilha* pilha) {
    return pilha->topo == pilha->capacidade - 1;
}

int tamanho_pilha(Pilha* pilha) {
    return pilha->topo + 1;
} 