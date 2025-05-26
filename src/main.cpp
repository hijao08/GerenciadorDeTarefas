#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "lista.h"
#include "pilha.h"
#include "fila.h"

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
    printf("4. Desfazer ultima tarefa criada\n");
    printf("5. Adicionar tarefa à fila de pendentes\n");
    printf("6. Processar próxima tarefa pendente\n");
    printf("7. Marcar tarefa como concluída\n");
    printf("8. Sair\n");
    printf("Escolha uma opção: ");
}

int main() {
    Lista lista;
    Pilha pilha_acoes;
    Fila fila_pendentes;
    
    inicializar_lista(&lista);
    inicializar_pilha(&pilha_acoes);
    inicializar_fila(&fila_pendentes);
    
    int opcao, prioridade, id;
    char titulo[MAX_TITULO], descricao[MAX_DESC], data[MAX_DATA];

    do {
        menu();
        scanf("%d", &opcao);
        getchar(); // Limpar buffer

        switch (opcao) {
            case 1: {
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
                Tarefa* nova_tarefa = criar_tarefa(id, titulo, descricao, prioridade, data);
                inserir_fim(&lista, nova_tarefa);
                push(&pilha_acoes, nova_tarefa); // Salva a ação na pilha
                printf("Tarefa cadastrada com sucesso!\n");
                break;
            }
            case 2:
                listar_tarefas(&lista);
                break;
            case 3: {
                printf("Informe o ID da tarefa a remover: ");
                scanf("%d", &id);
                Tarefa* tarefa_removida = remover_tarefa(&lista, id);
                if (tarefa_removida) {
                    push(&pilha_acoes, tarefa_removida); // Salva a tarefa removida na pilha
                    printf("Tarefa removida!\n");
                } else {
                    printf("Tarefa não encontrada.\n");
                }
                break;
            }
            case 4: {
                Tarefa* ultima_acao = pop(&pilha_acoes);
                if (ultima_acao) {
                    if (buscar_tarefa(&lista, ultima_acao->id)) {
                        // Se a tarefa existe na lista, ela foi removida
                        remover_tarefa(&lista, ultima_acao->id);
                        printf("Ação desfeita: tarefa removida foi restaurada\n");
                    } else {
                        // Se a tarefa não existe na lista, ela foi adicionada
                        inserir_fim(&lista, ultima_acao);
                        printf("Ação desfeita: tarefa adicionada foi removida\n");
                    }
                } else {
                    printf("Não há ações para desfazer!\n");
                }
                break;
            }
            case 5: {
                printf("Informe o ID da tarefa para adicionar à fila de pendentes: ");
                scanf("%d", &id);
                Tarefa* tarefa = buscar_tarefa(&lista, id);
                if (tarefa) {
                    enfileirar(&fila_pendentes, tarefa);
                    printf("Tarefa adicionada à fila de pendentes!\n");
                } else {
                    printf("Tarefa não encontrada!\n");
                }
                break;
            }
            case 6: {
                Tarefa* proxima_tarefa = desenfileirar(&fila_pendentes);
                if (proxima_tarefa) {
                    printf("\nProcessando próxima tarefa pendente:\n");
                    printf("ID: %d\n", proxima_tarefa->id);
                    printf("Título: %s\n", proxima_tarefa->titulo);
                    printf("Descrição: %s\n", proxima_tarefa->descricao);
                    printf("Prioridade: %d\n", proxima_tarefa->prioridade);
                    printf("Data: %s\n", proxima_tarefa->data);
                    printf("Status: %s\n", proxima_tarefa->concluida ? "Concluída" : "Não concluída");
                } else {
                    printf("Não há tarefas pendentes na fila!\n");
                }
                break;
            }
            case 7: {
                printf("Informe o ID da tarefa para marcar como concluída: ");
                scanf("%d", &id);
                Tarefa* tarefa = buscar_tarefa(&lista, id);
                if (tarefa) {
                    tarefa->concluida = 1;
                    printf("Tarefa marcada como concluída!\n");
                } else {
                    printf("Tarefa não encontrada!\n");
                }
                break;
            }
            case 8:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 8);

    // Liberar memória
    Tarefa* atual = lista.inicio;
    while (atual) {
        Tarefa* tmp = atual;
        atual = atual->proxima;
        free(tmp);
    }

    return 0;
}
