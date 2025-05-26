#include "pilha.h"
#include "tarefa.h"

void inicializar_pilha(Pilha *pilha) {
    pilha->topo = -1;
}

void push(Pilha *pilha, Tarefa *tarefa) {
    if (pilha->topo < 99) {
        pilha->topo++;
        pilha->dados[pilha->topo] = tarefa;
    }
}

Tarefa* pop(Pilha *pilha) {
    if (pilha->topo >= 0) {
        Tarefa *tarefa = pilha->dados[pilha->topo];
        pilha->topo--;
        return tarefa;
    }
    return nullptr;
}

int pilha_vazia(Pilha *pilha) {
    return pilha->topo == -1;
}

int pilha_cheia(Pilha *pilha) {
    return pilha->topo == 99;
}
