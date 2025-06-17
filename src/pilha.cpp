#include "pilha.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void inicializar_pilha(Pilha* pilha) {
    pilha->elementos = (Acao**)malloc(MAX_PILHA * sizeof(Acao*));
    pilha->topo = -1;
    pilha->capacidade = MAX_PILHA;
}

void destruir_pilha(Pilha* pilha) {
    while (!pilha_vazia(pilha)) {
        Acao* acao = desempilhar(pilha);
        free(acao);
    }
    free(pilha->elementos);
    pilha->elementos = NULL;
    pilha->topo = -1;
    pilha->capacidade = 0;
}

void empilhar(Pilha* pilha, TipoAcao tipo, Tarefa* tarefa) {
    if (pilha->topo < pilha->capacidade - 1) {
        Acao* nova_acao = (Acao*)malloc(sizeof(Acao));
        nova_acao->tipo = tipo;
        nova_acao->tarefa = tarefa;
        pilha->elementos[++pilha->topo] = nova_acao;
    } else {
        printf("Erro: Pilha cheia!\n");
    }
}

void empilhar_edicao(Pilha* pilha, Tarefa* tarefa, const char* titulo_anterior, 
                     const char* descricao_anterior, const char* data_anterior, 
                     int prioridade_anterior, int concluida_anterior) {
    if (pilha->topo < pilha->capacidade - 1) {
        Acao* nova_acao = (Acao*)malloc(sizeof(Acao));
        nova_acao->tipo = ACAO_EDITAR;
        nova_acao->tarefa = tarefa;
        strcpy(nova_acao->titulo_anterior, titulo_anterior);
        strcpy(nova_acao->descricao_anterior, descricao_anterior);
        strcpy(nova_acao->data_anterior, data_anterior);
        nova_acao->prioridade_anterior = prioridade_anterior;
        nova_acao->concluida_anterior = concluida_anterior;
        pilha->elementos[++pilha->topo] = nova_acao;
    } else {
        printf("Erro: Pilha cheia!\n");
    }
}

Acao* desempilhar(Pilha* pilha) {
    if (!pilha_vazia(pilha)) {
        return pilha->elementos[pilha->topo--];
    }
    return NULL;
}

Tarefa* topo_pilha(Pilha* pilha) {
    if (!pilha_vazia(pilha)) {
        return pilha->elementos[pilha->topo]->tarefa;
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