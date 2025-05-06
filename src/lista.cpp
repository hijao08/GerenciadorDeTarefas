#include "lista.h"
#include <cstdio>
#include <cstdlib>

void inicializar_lista(Lista* lista) {
    lista->inicio = nullptr;
}

void inserir_fim(Lista* lista, Tarefa* tarefa) {
    if (!lista->inicio) {
        lista->inicio = tarefa;
    } else {
        Tarefa* atual = lista->inicio;
        while (atual->proxima) {
            atual = atual->proxima;
        }
        atual->proxima = tarefa;
    }
}

void listar_tarefas(const Lista* lista) {
    Tarefa* atual = lista->inicio;
    if (!atual) {
        printf("Lista vazia!\n");
        return;
    }
    while (atual) {
        imprimir_tarefa(atual);
        printf("---------------------\n");
        atual = atual->proxima;
    }
}

int remover_tarefa(Lista* lista, int id) {
    Tarefa* atual = lista->inicio;
    Tarefa* anterior = nullptr;
    while (atual) {
        if (atual->id == id) {
            if (anterior) {
                anterior->proxima = atual->proxima;
            } else {
                lista->inicio = atual->proxima;
            }
            free(atual);
            return 1;
        }
        anterior = atual;
        atual = atual->proxima;
    }
    return 0;
}
