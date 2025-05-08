#include <iostream>
#include <string>
#include <cstring>
#include "lista.h"
#include "pilha.h"
#include "fila.h"

using namespace std;

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
    cout << "\n==== Gerenciador de Tarefas ====" << endl;
    cout << "1. Cadastrar tarefa" << endl;
    cout << "2. Listar todas as tarefas" << endl;
    cout << "3. Listar tarefas por prioridade" << endl;
    cout << "4. Buscar tarefa" << endl;
    cout << "5. Editar tarefa" << endl;
    cout << "6. Remover tarefa" << endl;
    cout << "7. Marcar tarefa como concluída" << endl;
    cout << "8. Desfazer última ação" << endl;
    cout << "9. Salvar tarefas" << endl;
    cout << "10. Carregar tarefas" << endl;
    cout << "0. Sair" << endl;
    cout << "Escolha uma opção: ";
}

// Função para validar data
bool validar_data(const string& data) {
    int dia, mes, ano;
    if (sscanf(data.c_str(), "%d/%d/%d", &dia, &mes, &ano) != 3) return false;
    if (dia < 1 || dia > 31) return false;
    if (mes < 1 || mes > 12) return false;
    if (ano < 2000 || ano > 2100) return false;
    return true;
}

// Função para validar prioridade
bool validar_prioridade(int prioridade) {
    return prioridade >= 1 && prioridade <= 5;
}

// Função para buscar tarefa
Tarefa* buscar_tarefa(Lista* lista, int id) {
    Tarefa* atual = lista->inicio;
    while (atual) {
        if (atual->id == id) return atual;
        atual = atual->proxima;
    }
    return nullptr;
}

// Função para editar tarefa
void editar_tarefa(Tarefa* tarefa) {
    string titulo, descricao, data;
    int prioridade;

    cout << "Novo título (ou Enter para manter '" << tarefa->titulo << "'): ";
    getline(cin, titulo);
    if (!titulo.empty()) strcpy(tarefa->titulo, titulo.c_str());

    cout << "Nova descrição (ou Enter para manter '" << tarefa->descricao << "'): ";
    getline(cin, descricao);
    if (!descricao.empty()) strcpy(tarefa->descricao, descricao.c_str());

    cout << "Nova prioridade (1-5) (ou 0 para manter " << tarefa->prioridade << "): ";
    cin >> prioridade;
    cin.ignore();
    if (prioridade > 0 && validar_prioridade(prioridade)) tarefa->prioridade = prioridade;

    cout << "Nova data (dd/mm/aaaa) (ou Enter para manter '" << tarefa->data << "'): ";
    getline(cin, data);
    if (!data.empty() && validar_data(data)) strcpy(tarefa->data, data.c_str());
}

int main() {
    Lista lista;
    Pilha<Tarefa*> pilhaAcoes;
    Fila<Tarefa*> filaPrioridade;
    
    inicializar_lista(&lista);
    
    int opcao, prioridade, id;
    string titulo, descricao, data;
    Tarefa* novaTarefa = nullptr;
    Tarefa* encontrada = nullptr;

    do {
        menu();
        cin >> opcao;
        cin.ignore(); // Limpar buffer

        switch (opcao) {
            case 1: // Cadastrar tarefa
                cout << "Título: ";
                getline(cin, titulo);
                cout << "Descrição: ";
                getline(cin, descricao);
                do {
                    cout << "Prioridade (1-5): ";
                    cin >> prioridade;
                    cin.ignore();
                } while (!validar_prioridade(prioridade));
                
                do {
                    cout << "Data (dd/mm/aaaa): ";
                    getline(cin, data);
                } while (!validar_data(data));
                
                id = gerar_id(&lista);
                novaTarefa = criar_tarefa(id, titulo.c_str(), descricao.c_str(), prioridade, data.c_str());
                inserir_fim(&lista, novaTarefa);
                filaPrioridade.enfileirar(novaTarefa);
                pilhaAcoes.empilhar(novaTarefa);
                cout << "Tarefa cadastrada com sucesso!" << endl;
                break;

            case 2: // Listar todas as tarefas
                listar_tarefas(&lista);
                break;

            case 3: // Listar por prioridade
                cout << "Informe a prioridade (1-5): ";
                cin >> prioridade;
                cin.ignore();
                if (validar_prioridade(prioridade)) {
                    listar_tarefas_por_prioridade(&lista, prioridade);
                } else {
                    cout << "Prioridade inválida!" << endl;
                }
                break;

            case 4: // Buscar tarefa
                cout << "Informe o ID da tarefa: ";
                cin >> id;
                cin.ignore();
                encontrada = buscar_tarefa(&lista, id);
                if (encontrada) {
                    imprimir_tarefa(encontrada);
                } else {
                    cout << "Tarefa não encontrada!" << endl;
                }
                break;

            case 5: // Editar tarefa
                cout << "Informe o ID da tarefa: ";
                cin >> id;
                cin.ignore();
                encontrada = buscar_tarefa(&lista, id);
                if (encontrada) {
                    editar_tarefa(encontrada);
                    cout << "Tarefa atualizada com sucesso!" << endl;
                } else {
                    cout << "Tarefa não encontrada!" << endl;
                }
                break;

            case 6: // Remover tarefa
                cout << "Informe o ID da tarefa a remover: ";
                cin >> id;
                if (remover_tarefa(&lista, id)) {
                    cout << "Tarefa removida!" << endl;
                    // TODO: Atualizar pilha de ações
                } else {
                    cout << "Tarefa não encontrada." << endl;
                }
                break;

            case 7: // Marcar como concluída
                cout << "Informe o ID da tarefa: ";
                cin >> id;
                cin.ignore();
                encontrada = buscar_tarefa(&lista, id);
                if (encontrada) {
                    if (encontrada->concluida) {
                        cout << "Tarefa já está concluída!" << endl;
                    } else {
                        marcar_concluida(encontrada);
                        cout << "Tarefa marcada como concluída!" << endl;
                    }
                } else {
                    cout << "Tarefa não encontrada!" << endl;
                }
                break;

            case 8: // Desfazer última ação
                cout << "Funcionalidade em desenvolvimento..." << endl;
                break;

            case 9: // Salvar tarefas
                cout << "Funcionalidade em desenvolvimento..." << endl;
                break;

            case 10: // Carregar tarefas
                cout << "Funcionalidade em desenvolvimento..." << endl;
                break;

            case 0:
                cout << "Saindo..." << endl;
                break;

            default:
                cout << "Opção inválida!" << endl;
        }
    } while (opcao != 0);

    // Liberar memória
    Tarefa* atual = lista.inicio;
    while (atual) {
        Tarefa* tmp = atual;
        atual = atual->proxima;
        delete tmp;
    }

    return 0;
}
