#include "tarefa.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Tarefa* criar_tarefa(int id, const char* titulo, const char* descricao, int prioridade, const char* data) {
    Tarefa* nova = (Tarefa*)malloc(sizeof(Tarefa));
    if (nova) {
        nova->id = id;
        strcpy(nova->titulo, titulo);
        strcpy(nova->descricao, descricao);
        nova->prioridade = prioridade;
        strcpy(nova->data, data);
        nova->concluida = 0;
        nova->proxima = NULL;
    }
    return nova;
}

void imprimir_tarefa(const Tarefa* tarefa) {
    printf("ID: %d\n", tarefa->id);
    printf("Título: %s\n", tarefa->titulo);
    printf("Descrição: %s\n", tarefa->descricao);
    printf("Prioridade: %d\n", tarefa->prioridade);
    printf("Data: %s\n", tarefa->data);
    printf("Status: %s\n", tarefa->concluida ? "Concluída" : "Pendente");
}

void marcar_concluida(Tarefa* tarefa) {
    if (tarefa) {
        tarefa->concluida = 1;
    }
}

void marcar_nao_concluida(Tarefa* tarefa) {
    if (tarefa) {
        tarefa->concluida = 0;
    }
} 