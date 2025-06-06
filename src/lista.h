#ifndef LISTA_H
#define LISTA_H

#include "tarefa.h"

typedef struct {
    Tarefa* inicio;
    int tamanho;
} Lista;

void inicializar_lista(Lista* lista);
void inserir_fim(Lista* lista, Tarefa* tarefa);
void listar_tarefas(const Lista* lista);
void listar_tarefas_por_prioridade(const Lista* lista, int prioridade);
int remover_tarefa(Lista* lista, int id);

#endif
