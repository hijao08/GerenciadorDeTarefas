# Gerenciador de Tarefas

Um sistema de gerenciamento de tarefas implementado em C, utilizando estruturas de dados como Lista, Pilha e Fila.

## Funcionalidades do Menu

### 1. Cadastrar tarefa

- **Estruturas utilizadas**: Lista, Fila e Pilha
- **Como funciona**:
  - Cria uma nova tarefa com ID, título, descrição, prioridade e data
  - Insere na Lista (para armazenamento principal)
  - Enfileira na Fila (para processamento em ordem de cadastro)
  - Empilha na Pilha (para histórico de ações)

### 2. Listar todas as tarefas

- **Estrutura utilizada**: Lista
- **Como funciona**: Percorre a lista encadeada mostrando todas as tarefas cadastradas

### 3. Listar tarefas por prioridade

- **Estrutura utilizada**: Lista
- **Como funciona**: Percorre a lista mostrando apenas as tarefas com a prioridade especificada

### 4. Buscar tarefa

- **Estrutura utilizada**: Lista
- **Como funciona**: Busca uma tarefa específica pelo ID na lista

### 5. Editar tarefa

- **Estrutura utilizada**: Lista
- **Como funciona**: Localiza a tarefa pelo ID e permite editar seus atributos

### 6. Remover tarefa

- **Estrutura utilizada**: Lista
- **Como funciona**: Remove a tarefa da lista pelo ID

### 7. Marcar tarefa como concluída

- **Estrutura utilizada**: Lista
- **Como funciona**: Localiza a tarefa pelo ID e marca como concluída

### 8. Desfazer última ação

- **Estrutura utilizada**: Pilha
- **Como funciona**: Utiliza a pilha para desfazer a última ação realizada (em desenvolvimento)

### 9. Processar tarefas na ordem de cadastro

- **Estrutura utilizada**: Fila
- **Como funciona**: Processa as tarefas na ordem em que foram cadastradas, usando a estrutura FIFO (First In, First Out) (em desenvolvimento)

### 10. Salvar tarefas

- **Estrutura utilizada**: Lista
- **Como funciona**: Salva todas as tarefas da lista em um arquivo texto (tarefas.txt)

### 11. Carregar tarefas

- **Estruturas utilizadas**: Lista, Fila e Pilha
- **Como funciona**:
  - Lê as tarefas do arquivo texto
  - Recria as estruturas de dados com as tarefas carregadas
  - Mantém a ordem original das tarefas

## Estruturas de Dados Utilizadas

### Lista

- Estrutura principal para armazenamento das tarefas
- Implementada como lista encadeada
- Mantém controle do tamanho atual

### Fila

- Usada para processar tarefas na ordem de cadastro (FIFO)
- Útil para manter a ordem cronológica das tarefas

### Pilha

- Usada para histórico de ações
- Permite implementar funcionalidade de desfazer (LIFO)

## Compilação

```bash
g++ src/main.cpp src/lista.cpp src/tarefa.cpp src/pilha.cpp src/fila.cpp -o gerenciador
```

## Execução

```bash
./gerenciador
```

## Requisitos

- GCC ou outro compilador C++
- Sistema operacional Unix-like (Linux, macOS)
