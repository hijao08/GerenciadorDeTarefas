#include "tarefa.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>

Tarefa* criar_tarefa(int id, const char* titulo, const char* descricao, int prioridade, const char* data) {
    Tarefa* nova = (Tarefa*)malloc(sizeof(Tarefa));
    if (!nova) return nullptr;
    nova->id = id;
    strncpy(nova->titulo, titulo, MAX_TITULO-1);
    nova->titulo[MAX_TITULO-1] = '\0';
    strncpy(nova->descricao, descricao, MAX_DESC-1);
    nova->descricao[MAX_DESC-1] = '\0';
    nova->prioridade = prioridade;
    strncpy(nova->data, data, MAX_DATA-1);
    nova->data[MAX_DATA-1] = '\0';
    nova->proxima = nullptr;
    return nova;
}

void imprimir_tarefa(const Tarefa* tarefa) {
    if (!tarefa) return;
    printf("ID: %d\nTítulo: %s\nDescrição: %s\nPrioridade: %d\nData: %s\n",
           tarefa->id, tarefa->titulo, tarefa->descricao, tarefa->prioridade, tarefa->data);
}
