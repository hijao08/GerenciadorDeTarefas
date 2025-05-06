// pilha.h
typedef struct {
    Tarefa *dados[100];
    int topo;
} Pilha;

void inicializar_pilha(Pilha *pilha);
void push(Pilha *pilha, Tarefa *tarefa);
Tarefa* pop(Pilha *pilha);

