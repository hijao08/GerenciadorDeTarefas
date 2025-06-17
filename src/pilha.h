// pilha.h
#ifndef PILHA_H
#define PILHA_H

#include "tarefa.h"

#define MAX_PILHA 100

typedef enum {
    ACAO_CRIAR,
    ACAO_EDITAR,
    ACAO_REMOVER,
    ACAO_CONCLUIR
} TipoAcao;

typedef struct {
    TipoAcao tipo;
    Tarefa* tarefa;
    // Para edição, guardar estado anterior
    char titulo_anterior[MAX_TITULO];
    char descricao_anterior[MAX_DESC];
    char data_anterior[MAX_DATA];
    int prioridade_anterior;
    int concluida_anterior;
} Acao;

typedef struct {
    Acao** elementos;
    int topo;
    int capacidade;
} Pilha;

void inicializar_pilha(Pilha* pilha);
void destruir_pilha(Pilha* pilha);
void empilhar(Pilha* pilha, TipoAcao tipo, Tarefa* tarefa);
Acao* desempilhar(Pilha* pilha);
int pilha_vazia(Pilha* pilha);
void empilhar_edicao(Pilha* pilha, Tarefa* tarefa, const char* titulo_anterior, 
                     const char* descricao_anterior, const char* data_anterior, 
                     int prioridade_anterior, int concluida_anterior);

#endif

