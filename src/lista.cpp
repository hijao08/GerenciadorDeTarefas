#include "lista.h"
#include <iostream>

using namespace std;

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
        cout << "Lista vazia!" << endl;
        return;
    }
    while (atual) {
        imprimir_tarefa(atual);
        cout << "---------------------" << endl;
        atual = atual->proxima;
    }
}

void listar_tarefas_por_prioridade(const Lista* lista, int prioridade) {
    Tarefa* atual = lista->inicio;
    bool encontrou = false;
    
    while (atual) {
        if (atual->prioridade == prioridade) {
            imprimir_tarefa(atual);
            cout << "---------------------" << endl;
            encontrou = true;
        }
        atual = atual->proxima;
    }
    
    if (!encontrou) {
        cout << "Nenhuma tarefa encontrada com prioridade " << prioridade << "!" << endl;
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
            delete atual;
            return 1;
        }
        anterior = atual;
        atual = atual->proxima;
    }
    return 0;
}
