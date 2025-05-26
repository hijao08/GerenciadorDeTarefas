#ifndef TAREFA_H
#define TAREFA_H

#define MAX_TITULO 50
#define MAX_DESC 200
#define MAX_DATA 11

typedef struct Tarefa {
    int id;
    char titulo[MAX_TITULO];
    char descricao[MAX_DESC];
    int prioridade;
    char data[MAX_DATA];
    int concluida;  // 0 = não concluída, 1 = concluída
    Tarefa* proxima;
} Tarefa;

Tarefa* criar_tarefa(int id, const char* titulo, const char* descricao, int prioridade, const char* data);
void imprimir_tarefa(const Tarefa* tarefa);

#endif
