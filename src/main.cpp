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
    printf("8. Desfazer última criação/edição de tarefa\n");
    printf("9. Processar tarefas na ordem de cadastro\n");
    printf("10. Salvar tarefas\n");
    printf("11. Carregar tarefas\n");
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

void salvar_tarefas(Lista* lista) {
    FILE* arquivo = fopen("tarefas.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo para salvar!\n");
        return;
    }

    Tarefa* atual = lista->inicio;
    while (atual != NULL) {
        fprintf(arquivo, "%d|%s|%s|%d|%s|%d\n",
                atual->id,
                atual->titulo,
                atual->descricao,
                atual->prioridade,
                atual->data,
                atual->concluida);
        atual = atual->proxima;
    }

    fclose(arquivo);
    printf("Tarefas salvas com sucesso!\n");
}

void carregar_tarefas(Lista* lista, Fila* filaPrioridade, Fila* filaOrdemCadastro, Pilha* pilha) {
    FILE* arquivo = fopen("tarefas.txt", "r");
    if (arquivo == NULL) {
        printf("Nenhum arquivo de tarefas encontrado!\n");
        return;
    }

    // Limpar lista atual
    Tarefa* atual = lista->inicio;
    while (atual) {
        Tarefa* tmp = atual;
        atual = atual->proxima;
        free(tmp);
    }
    lista->inicio = NULL;
    lista->tamanho = 0;

    // Limpar filas e pilha
    while (!fila_vazia(filaPrioridade)) {
        desenfileirar(filaPrioridade);
    }
    while (!fila_vazia(filaOrdemCadastro)) {
        desenfileirar(filaOrdemCadastro);
    }
    while (!pilha_vazia(pilha)) {
        Acao* acao = desempilhar(pilha);
        if (acao) free(acao);
    }

    char linha[1000];
    while (fgets(linha, sizeof(linha), arquivo)) {
        int id, prioridade, concluida;
        char titulo[MAX_TITULO], descricao[MAX_DESC], data[MAX_DATA];
        
        char* token = strtok(linha, "|");
        id = atoi(token);
        
        token = strtok(NULL, "|");
        strcpy(titulo, token);
        
        token = strtok(NULL, "|");
        strcpy(descricao, token);
        
        token = strtok(NULL, "|");
        prioridade = atoi(token);
        
        token = strtok(NULL, "|");
        strcpy(data, token);
        
        token = strtok(NULL, "|");
        concluida = atoi(token);

        Tarefa* novaTarefa = criar_tarefa(id, titulo, descricao, prioridade, data);
        if (concluida) {
            marcar_concluida(novaTarefa);
        }
        
        inserir_fim(lista, novaTarefa);
        enfileirar(filaPrioridade, novaTarefa);
        enfileirar(filaOrdemCadastro, novaTarefa);
        empilhar(pilha, ACAO_CRIAR, novaTarefa);
    }

    fclose(arquivo);
    printf("Tarefas carregadas com sucesso!\n");
}

int main() {
    Lista lista;
    Pilha pilhaAcoes;
    Fila filaPrioridade;
    Fila filaOrdemCadastro;  // Nova fila para ordem de cadastro
    
    inicializar_lista(&lista);
    inicializar_pilha(&pilhaAcoes);
    inicializar_fila(&filaPrioridade);
    inicializar_fila(&filaOrdemCadastro);  // Inicializar nova fila
    
    int opcao, prioridade, id;
    char titulo[MAX_TITULO], descricao[MAX_DESC], data[MAX_DATA];
    Tarefa* novaTarefa = NULL;
    Tarefa* encontrada = NULL;
    bool tarefa_processada = false;
    Acao* ultima_acao = NULL;  // Movido para fora do switch

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
                enfileirar(&filaOrdemCadastro, novaTarefa);
                empilhar(&pilhaAcoes, ACAO_CRIAR, novaTarefa);
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
                    // Guardar estado anterior
                    char titulo_anterior[MAX_TITULO];
                    char descricao_anterior[MAX_DESC];
                    char data_anterior[MAX_DATA];
                    int prioridade_anterior = encontrada->prioridade;
                    int concluida_anterior = encontrada->concluida;
                    
                    strcpy(titulo_anterior, encontrada->titulo);
                    strcpy(descricao_anterior, encontrada->descricao);
                    strcpy(data_anterior, encontrada->data);
                    
                    editar_tarefa(encontrada);
                    empilhar_edicao(&pilhaAcoes, encontrada, titulo_anterior, 
                                  descricao_anterior, data_anterior, 
                                  prioridade_anterior, concluida_anterior);
                    printf("Tarefa atualizada com sucesso!\n");
                } else {
                    printf("Tarefa não encontrada!\n");
                }
                break;

            case 6: // Remover tarefa
                printf("Informe o ID da tarefa a remover: ");
                scanf("%d", &id);
                encontrada = buscar_tarefa(&lista, id);
                if (encontrada) {
                    empilhar(&pilhaAcoes, ACAO_REMOVER, encontrada);
                    if (remover_tarefa(&lista, id)) {
                        printf("Tarefa removida!\n");
                    }
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
                        empilhar(&pilhaAcoes, ACAO_CONCLUIR, encontrada);
                        marcar_concluida(encontrada);
                        printf("Tarefa marcada como concluída!\n");
                    }
                } else {
                    printf("Tarefa não encontrada!\n");
                }
                break;

            case 8: // Desfazer última ação
                if (pilha_vazia(&pilhaAcoes)) {
                    printf("Não há ações para desfazer!\n");
                    break;
                }

                ultima_acao = desempilhar(&pilhaAcoes);
                if (ultima_acao == NULL) {
                    printf("Erro ao desfazer ação!\n");
                    break;
                }

                switch (ultima_acao->tipo) {
                    case ACAO_CRIAR:
                        // Remover a tarefa da lista e das filas
                        remover_tarefa(&lista, ultima_acao->tarefa->id);
                        printf("Criação da tarefa desfeita!\n");
                        break;

                    case ACAO_EDITAR:
                        // Restaurar estado anterior
                        strcpy(ultima_acao->tarefa->titulo, ultima_acao->titulo_anterior);
                        strcpy(ultima_acao->tarefa->descricao, ultima_acao->descricao_anterior);
                        strcpy(ultima_acao->tarefa->data, ultima_acao->data_anterior);
                        ultima_acao->tarefa->prioridade = ultima_acao->prioridade_anterior;
                        ultima_acao->tarefa->concluida = ultima_acao->concluida_anterior;
                        printf("Edição da tarefa desfeita!\n");
                        break;

                    case ACAO_REMOVER:
                        // Restaurar a tarefa removida
                        inserir_fim(&lista, ultima_acao->tarefa);
                        enfileirar(&filaPrioridade, ultima_acao->tarefa);
                        enfileirar(&filaOrdemCadastro, ultima_acao->tarefa);
                        printf("Remoção da tarefa desfeita!\n");
                        break;

                    case ACAO_CONCLUIR:
                        // Desmarcar como concluída
                        ultima_acao->tarefa->concluida = 0;
                        printf("Conclusão da tarefa desfeita!\n");
                        break;
                }

                free(ultima_acao);
                break;

            case 9: // Processar tarefas na ordem de cadastro
                printf("\nProcessando próxima tarefa na ordem de cadastro:\n");
                if (fila_vazia(&filaOrdemCadastro)) {
                    printf("Não há tarefas para processar!\n");
                    break;
                }
                
                // Criar uma fila temporária para manter as tarefas
                Fila filaTemp;
                inicializar_fila(&filaTemp);
                
                // Procurar a primeira tarefa não concluída
                tarefa_processada = false;  // Apenas resetando a variável
                while (!fila_vazia(&filaOrdemCadastro)) {
                    Tarefa* tarefa = desenfileirar(&filaOrdemCadastro);
                    
                    if (!tarefa_processada && !tarefa->concluida) {
                        printf("Processando tarefa:\n");
                        imprimir_tarefa(tarefa);
                        marcar_concluida(tarefa);
                        printf("Tarefa marcada como concluída!\n");
                        tarefa_processada = true;
                    }
                    
                    enfileirar(&filaTemp, tarefa);
                }
                
                if (!tarefa_processada) {
                    printf("Todas as tarefas já estão concluídas!\n");
                }
                
                // Restaurar as tarefas na fila original
                while (!fila_vazia(&filaTemp)) {
                    Tarefa* tarefa = desenfileirar(&filaTemp);
                    enfileirar(&filaOrdemCadastro, tarefa);
                }
                
                destruir_fila(&filaTemp);
                break;

            case 10: // Salvar tarefas
                salvar_tarefas(&lista);
                break;

            case 11: // Carregar tarefas
                carregar_tarefas(&lista, &filaPrioridade, &filaOrdemCadastro, &pilhaAcoes);
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
    destruir_fila(&filaOrdemCadastro);  // Destruir a nova fila

    return 0;
} 