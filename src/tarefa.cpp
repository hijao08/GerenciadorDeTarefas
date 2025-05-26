#include "tarefa.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>

Tarefa* criar_tarefa(int id, const char* titulo, const char* descricao, int prioridade, const char* data) {
    Tarefa* nova_tarefa = (Tarefa*)malloc(sizeof(Tarefa));
    if (nova_tarefa) {
        nova_tarefa->id = id;
        strncpy(nova_tarefa->titulo, titulo, MAX_TITULO - 1);
        nova_tarefa->titulo[MAX_TITULO - 1] = '\0';
        strncpy(nova_tarefa->descricao, descricao, MAX_DESC - 1);
        nova_tarefa->descricao[MAX_DESC - 1] = '\0';
        nova_tarefa->prioridade = prioridade;
        strncpy(nova_tarefa->data, data, MAX_DATA - 1);
        nova_tarefa->data[MAX_DATA - 1] = '\0';
        nova_tarefa->concluida = 0;  // Inicializa como não concluída
        nova_tarefa->proxima = nullptr;
    }
    return nova_tarefa;
}

void imprimir_tarefa(const Tarefa* tarefa) {
    if (!tarefa) return;
    printf("\n ID: %d\nTítulo: %s\nDescrição: %s\nPrioridade: %d\nData: %s\nStatus: %s\n",
           tarefa->id, tarefa->titulo, tarefa->descricao, tarefa->prioridade, tarefa->data,
           tarefa->concluida ? "Concluída" : "Não concluída");
}
