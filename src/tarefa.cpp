#include "tarefa.h"
#include <iostream>
#include <cstring>

using namespace std;

Tarefa* criar_tarefa(int id, const char* titulo, const char* descricao, int prioridade, const char* data) {
    Tarefa* nova = new Tarefa;
    if (nova) {
        nova->id = id;
        strcpy(nova->titulo, titulo);
        strcpy(nova->descricao, descricao);
        nova->prioridade = prioridade;
        strcpy(nova->data, data);
        nova->concluida = false;
        nova->proxima = nullptr;
    }
    return nova;
}

void imprimir_tarefa(const Tarefa* tarefa) {
    cout << "ID: " << tarefa->id << endl;
    cout << "Título: " << tarefa->titulo << endl;
    cout << "Descrição: " << tarefa->descricao << endl;
    cout << "Prioridade: " << tarefa->prioridade << endl;
    cout << "Data: " << tarefa->data << endl;
    cout << "Status: " << (tarefa->concluida ? "Concluída" : "Pendente") << endl;
}

void marcar_concluida(Tarefa* tarefa) {
    if (tarefa) {
        tarefa->concluida = true;
    }
}

void marcar_nao_concluida(Tarefa* tarefa) {
    if (tarefa) {
        tarefa->concluida = false;
    }
}
