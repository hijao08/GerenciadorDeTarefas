// pilha.h
#ifndef PILHA_H
#define PILHA_H

#include "tarefa.h"

#define MAX_PILHA 100

typedef struct {
    Tarefa** elementos;
    int topo;
    int capacidade;
} Pilha;

void inicializar_pilha(Pilha* pilha);
void destruir_pilha(Pilha* pilha);
void empilhar(Pilha* pilha, Tarefa* elemento);
Tarefa* desempilhar(Pilha* pilha);
Tarefa* topo_pilha(Pilha* pilha);
int pilha_vazia(Pilha* pilha);
int pilha_cheia(Pilha* pilha);
int tamanho_pilha(Pilha* pilha);

#endif

