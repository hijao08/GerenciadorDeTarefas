#include "lista.h"
#include <cstdio>
#include <cstdlib>

void inicializar_lista(Lista* lista) {
    lista->inicio = nullptr;
}

void inserir_fim(Lista* lista, Tarefa* tarefa) {
    if (!lista->inicio) {
        lista->inicio = tarefa;
        tarefa->proxima = nullptr;
        return;
    }

    Tarefa* atual = lista->inicio;
    while (atual->proxima) {
        atual = atual->proxima;
    }
    atual->proxima = tarefa;
    tarefa->proxima = nullptr;
}

Tarefa* buscar_tarefa(Lista* lista, int id) {
    Tarefa* atual = lista->inicio;
    while (atual) {
        if (atual->id == id) {
            return atual;
        }
        atual = atual->proxima;
    }
    return nullptr;
}

Tarefa* remover_tarefa(Lista* lista, int id) {
    if (!lista->inicio) return nullptr;

    Tarefa* atual = lista->inicio;
    Tarefa* anterior = nullptr;

    while (atual && atual->id != id) {
        anterior = atual;
        atual = atual->proxima;
    }

    if (!atual) return nullptr;

    if (!anterior) {
        lista->inicio = atual->proxima;
    } else {
        anterior->proxima = atual->proxima;
    }

    atual->proxima = nullptr;
    return atual;
}

void listar_tarefas(const Lista* lista) {
    Tarefa* atual = lista->inicio;
    if (!atual) {
        printf("Nenhuma tarefa cadastrada.\n");
        return;
    }

    printf("\nLista de Tarefas:\n");
    while (atual) {
        printf("ID: %d\n", atual->id);
        printf("Título: %s\n", atual->titulo);
        printf("Descrição: %s\n", atual->descricao);
        printf("Prioridade: %d\n", atual->prioridade);
        printf("Data: %s\n", atual->data);
        printf("Status: %s\n", atual->concluida ? "Concluída" : "Não concluída");
        printf("-------------------\n");
        atual = atual->proxima;
    }
}
