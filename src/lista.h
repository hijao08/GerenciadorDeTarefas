#ifndef LISTA_H
#define LISTA_H

#include "tarefa.h"

typedef struct {
    Tarefa* inicio;
} Lista;

void inicializar_lista(Lista* lista);
void inserir_fim(Lista* lista, Tarefa* tarefa);
void listar_tarefas(const Lista* lista);
Tarefa* remover_tarefa(Lista* lista, int id);
Tarefa* buscar_tarefa(Lista* lista, int id);

#endif
