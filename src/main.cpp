#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
    printf("2. Listar todas as tarefas\n");
    printf("3. Listar tarefas por prioridade\n");
    printf("4. Buscar tarefa\n");
    printf("5. Editar tarefa\n");
    printf("6. Remover tarefa\n");
    printf("7. Marcar tarefa como concluída\n");
    printf("8. Desfazer última ação\n");
    printf("9. Salvar tarefas\n");
    printf("10. Carregar tarefas\n");
    printf("0. Sair\n");
    printf("Escolha uma opção: ");
}

int validar_data(const char* data) {
    int dia, mes, ano;
    if (sscanf(data, "%d/%d/%d", &dia, &mes, &ano) != 3) return 0;
    if (dia < 1 || dia > 31) return 0;
    if (mes < 1 || mes > 12) return 0;
    if (ano < 2000 || ano > 2100) return 0;
    return 1;
}

int validar_prioridade(int prioridade) {
    return prioridade >= 1 && prioridade <= 5;
}

Tarefa* buscar_tarefa(Lista* lista, int id) {
    Tarefa* atual = lista->inicio;
    while (atual) {
        if (atual->id == id) return atual;
        atual = atual->proxima;
    }
    return NULL;
}

void editar_tarefa(Tarefa* tarefa) {
    char titulo[MAX_TITULO], descricao[MAX_DESC], data[MAX_DATA];
    int prioridade;

    printf("Novo título (ou Enter para manter '%s'): ", tarefa->titulo);
    fgets(titulo, MAX_TITULO, stdin);
    titulo[strcspn(titulo, "\n")] = 0;
    if (strlen(titulo) > 0) strcpy(tarefa->titulo, titulo);

    printf("Nova descrição (ou Enter para manter '%s'): ", tarefa->descricao);
    fgets(descricao, MAX_DESC, stdin);
    descricao[strcspn(descricao, "\n")] = 0;
    if (strlen(descricao) > 0) strcpy(tarefa->descricao, descricao);

    printf("Nova prioridade (1-5) (ou 0 para manter %d): ", tarefa->prioridade);
    scanf("%d", &prioridade);
    getchar();
    if (prioridade > 0 && validar_prioridade(prioridade)) tarefa->prioridade = prioridade;

    printf("Nova data (dd/mm/aaaa) (ou Enter para manter '%s'): ", tarefa->data);
    fgets(data, MAX_DATA, stdin);
    data[strcspn(data, "\n")] = 0;
    if (strlen(data) > 0 && validar_data(data)) strcpy(tarefa->data, data);
}

int main() {
    Lista lista;
    Pilha pilhaAcoes;
    Fila filaPrioridade;
    
    inicializar_lista(&lista);
    inicializar_pilha(&pilhaAcoes);
    inicializar_fila(&filaPrioridade);
    
    int opcao, prioridade, id;
    char titulo[MAX_TITULO], descricao[MAX_DESC], data[MAX_DATA];
    Tarefa* novaTarefa = NULL;
    Tarefa* encontrada = NULL;

    do {
        menu();
        scanf("%d", &opcao);
        getchar(); // Limpar buffer

        switch (opcao) {
            case 1: // Cadastrar tarefa
                printf("Título: ");
                fgets(titulo, MAX_TITULO, stdin);
                titulo[strcspn(titulo, "\n")] = 0;
                
                printf("Descrição: ");
                fgets(descricao, MAX_DESC, stdin);
                descricao[strcspn(descricao, "\n")] = 0;
                
                do {
                    printf("Prioridade (1-5): ");
                    scanf("%d", &prioridade);
                    getchar();
                } while (!validar_prioridade(prioridade));
                
                do {
                    printf("Data (dd/mm/aaaa): ");
                    fgets(data, MAX_DATA, stdin);
                    data[strcspn(data, "\n")] = 0;
                } while (!validar_data(data));
                
                id = gerar_id(&lista);
                novaTarefa = criar_tarefa(id, titulo, descricao, prioridade, data);
                inserir_fim(&lista, novaTarefa);
                enfileirar(&filaPrioridade, novaTarefa);
                empilhar(&pilhaAcoes, novaTarefa);
                printf("Tarefa cadastrada com sucesso!\n");
                break;

            case 2: // Listar todas as tarefas
                listar_tarefas(&lista);
                break;

            case 3: // Listar por prioridade
                printf("Informe a prioridade (1-5): ");
                scanf("%d", &prioridade);
                getchar();
                if (validar_prioridade(prioridade)) {
                    listar_tarefas_por_prioridade(&lista, prioridade);
                } else {
                    printf("Prioridade inválida!\n");
                }
                break;

            case 4: // Buscar tarefa
                printf("Informe o ID da tarefa: ");
                scanf("%d", &id);
                getchar();
                encontrada = buscar_tarefa(&lista, id);
                if (encontrada) {
                    imprimir_tarefa(encontrada);
                } else {
                    printf("Tarefa não encontrada!\n");
                }
                break;

            case 5: // Editar tarefa
                printf("Informe o ID da tarefa: ");
                scanf("%d", &id);
                getchar();
                encontrada = buscar_tarefa(&lista, id);
                if (encontrada) {
                    editar_tarefa(encontrada);
                    printf("Tarefa atualizada com sucesso!\n");
                } else {
                    printf("Tarefa não encontrada!\n");
                }
                break;

            case 6: // Remover tarefa
                printf("Informe o ID da tarefa a remover: ");
                scanf("%d", &id);
                if (remover_tarefa(&lista, id)) {
                    printf("Tarefa removida!\n");
                } else {
                    printf("Tarefa não encontrada.\n");
                }
                break;

            case 7: // Marcar como concluída
                printf("Informe o ID da tarefa: ");
                scanf("%d", &id);
                getchar();
                encontrada = buscar_tarefa(&lista, id);
                if (encontrada) {
                    if (encontrada->concluida) {
                        printf("Tarefa já está concluída!\n");
                    } else {
                        marcar_concluida(encontrada);
                        printf("Tarefa marcada como concluída!\n");
                    }
                } else {
                    printf("Tarefa não encontrada!\n");
                }
                break;

            case 8: // Desfazer última ação
                printf("Funcionalidade em desenvolvimento...\n");
                break;

            case 9: // Salvar tarefas
                printf("Funcionalidade em desenvolvimento...\n");
                break;

            case 10: // Carregar tarefas
                printf("Funcionalidade em desenvolvimento...\n");
                break;

            case 0:
                printf("Saindo...\n");
                break;

            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 0);

    // Liberar memória
    Tarefa* atual = lista.inicio;
    while (atual) {
        Tarefa* tmp = atual;
        atual = atual->proxima;
        free(tmp);
    }

    destruir_pilha(&pilhaAcoes);
    destruir_fila(&filaPrioridade);

    return 0;
} 