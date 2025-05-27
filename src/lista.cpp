#include "lista.h"
#include <stdio.h>
#include <stdlib.h>

void inicializar_lista(Lista* lista) {
    lista->inicio = NULL;
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

void listar_tarefas_por_prioridade(const Lista* lista, int prioridade) {
    Tarefa* atual = lista->inicio;
    int encontrou = 0;
    
    while (atual) {
        if (atual->prioridade == prioridade) {
            imprimir_tarefa(atual);
            printf("---------------------\n");
            encontrou = 1;
        }
        atual = atual->proxima;
    }
    
    if (!encontrou) {
        printf("Nenhuma tarefa encontrada com prioridade %d!\n", prioridade);
    }
}

int remover_tarefa(Lista* lista, int id) {
    Tarefa* atual = lista->inicio;
    Tarefa* anterior = NULL;
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