#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "lista.h"

int gerar_id(Lista* lista) {
    int max_id = 0;
    Tarefa* atual = lista->inicio;
    while (atual) {
        if (atual->id > max_id) max_id = atual->id;
        atual = atual->proxima;
    }
    return max_id + 1;
}

void menu() {
    printf("\n==== Gerenciador de Tarefas ====\n");
    printf("1. Cadastrar tarefa\n");
    printf("2. Listar tarefas\n");
    printf("3. Remover tarefa\n");
    printf("4. Sair\n");
    printf("Escolha uma opção: ");
}

int main() {
    Lista lista;
    inicializar_lista(&lista);
    int opcao, prioridade, id;
    char titulo[MAX_TITULO], descricao[MAX_DESC], data[MAX_DATA];

    do {
        menu();
        scanf("%d", &opcao);
        getchar(); // Limpar buffer

        switch (opcao) {
            case 1:
                printf("Título: ");
                fgets(titulo, MAX_TITULO, stdin); titulo[strcspn(titulo, "\n")] = 0;
                printf("Descrição: ");
                fgets(descricao, MAX_DESC, stdin); descricao[strcspn(descricao, "\n")] = 0;
                printf("Prioridade (1-5): ");
                scanf("%d", &prioridade);
                getchar();
                printf("Data (dd/mm/aaaa): ");
                fgets(data, MAX_DATA, stdin); data[strcspn(data, "\n")] = 0;
                id = gerar_id(&lista);
                inserir_fim(&lista, criar_tarefa(id, titulo, descricao, prioridade, data));
                printf("Tarefa cadastrada com sucesso!\n");
                break;
            case 2:
                listar_tarefas(&lista);
                break;
            case 3:
                printf("Informe o ID da tarefa a remover: ");
                scanf("%d", &id);
                if (remover_tarefa(&lista, id))
                    printf("Tarefa removida!\n");
                else
                    printf("Tarefa não encontrada.\n");
                break;
            case 4:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 4);

    // Liberar memória
    Tarefa* atual = lista.inicio;
    while (atual) {
        Tarefa* tmp = atual;
        atual = atual->proxima;
        free(tmp);
    }

    return 0;
}
