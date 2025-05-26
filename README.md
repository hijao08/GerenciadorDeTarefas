# Gerenciador de Tarefas

Um sistema de gerenciamento de tarefas implementado em C++ que utiliza diferentes estruturas de dados para organizar e manipular tarefas.

## Estruturas de Dados Utilizadas

### Lista Encadeada

- Utilizada para armazenar todas as tarefas do sistema
- Permite inserção e remoção eficiente de tarefas
- Mantém as tarefas organizadas por ordem de inserção

### Pilha

- Utilizada para implementar o sistema de "desfazer" ações
- Armazena as últimas ações realizadas (adição ou remoção de tarefas)
- Permite desfazer a última ação realizada

### Fila

- Utilizada para gerenciar tarefas pendentes
- Implementa o conceito FIFO (First In, First Out)
- Permite organizar tarefas que precisam ser processadas em ordem

## Funcionalidades do Menu

### 1. Cadastrar tarefa

- **Estrutura utilizada**: Lista Encadeada e Pilha
- **Funcionalidade**: Permite adicionar uma nova tarefa ao sistema
- **Detalhes**:
  - Solicita título, descrição, prioridade e data
  - Armazena na lista encadeada
  - Registra a ação na pilha para possível desfazer

### 2. Listar tarefas

- **Estrutura utilizada**: Lista Encadeada
- **Funcionalidade**: Exibe todas as tarefas cadastradas
- **Detalhes**: Mostra ID, título, descrição, prioridade e data de cada tarefa

### 3. Remover tarefa

- **Estrutura utilizada**: Lista Encadeada e Pilha
- **Funcionalidade**: Remove uma tarefa específica do sistema
- **Detalhes**:
  - Solicita o ID da tarefa a ser removida
  - Remove da lista encadeada
  - Registra a ação na pilha para possível desfazer

### 4. Desfazer última ação

- **Estrutura utilizada**: Pilha
- **Funcionalidade**: Desfaz a última ação realizada (adição ou remoção)
- **Detalhes**:
  - Recupera a última ação da pilha
  - Restaura o estado anterior do sistema

### 5. Adicionar tarefa à fila de pendentes

- **Estrutura utilizada**: Fila
- **Funcionalidade**: Adiciona uma tarefa existente à fila de pendentes
- **Detalhes**:
  - Solicita o ID da tarefa
  - Adiciona à fila para processamento posterior

### 6. Processar próxima tarefa pendente

- **Estrutura utilizada**: Fila
- **Funcionalidade**: Processa a próxima tarefa da fila de pendentes
- **Detalhes**:
  - Remove a primeira tarefa da fila
  - Exibe os detalhes da tarefa para processamento

### 7. Sair

- **Funcionalidade**: Encerra o programa
- **Detalhes**: Libera toda a memória alocada antes de encerrar

## Compilação e Execução

Para compilar o projeto:

```bash
g++ -o gerenciador src/*.cpp
```

Para executar:

```bash
./gerenciador
```

## Requisitos

- Compilador C++ (g++ recomendado)
- Sistema operacional compatível com C++

## Limitações

- Capacidade máxima de 100 tarefas na pilha
- Capacidade máxima de 100 tarefas na fila
- Tamanho máximo do título: 100 caracteres
- Tamanho máximo da descrição: 500 caracteres
- Tamanho máximo da data: 11 caracteres (formato dd/mm/aaaa)

## 📋 Funcionalidades

- ✨ Adicionar novas tarefas com título, descrição, prioridade e data
- 📝 Listar todas as tarefas ou filtrar por prioridade
- ✅ Marcar tarefas como concluídas
- 🔍 Buscar tarefas por ID
- ✏️ Editar tarefas existentes
- 🗑️ Remover tarefas
- ⭐ Gerenciar prioridades (1-5)
- 📅 Organizar por data
- 🔄 Desfazer última ação (em desenvolvimento)
- 💾 Salvar e carregar tarefas (em desenvolvimento)

## 🚀 Como Compilar

1. Certifique-se de ter o GCC instalado:

```bash
g++ --version
```

2. Clone o repositório:

```bash
git clone https://github.com/seu-usuario/gerenciador-tarefas.git
cd gerenciador-tarefas
```

3. Compile o projeto:

```bash
g++ src/main.cpp src/lista.cpp src/tarefa.cpp src/pilha.cpp src/fila.cpp -o gerenciador
```

## 💻 Como Usar

1. Execute o programa:

```bash
./gerenciador
```

2. Use o menu interativo para:
   - Cadastrar novas tarefas
   - Listar tarefas existentes
   - Buscar tarefas específicas
   - Editar tarefas
   - Remover tarefas
   - Marcar tarefas como concluídas

## 📦 Estrutura do Projeto

```
src/
├── main.cpp      # Programa principal e interface do usuário
├── tarefa.h      # Definição da estrutura de tarefas
├── tarefa.cpp    # Implementação das funções de tarefas
├── lista.h       # Definição da estrutura de lista
├── lista.cpp     # Implementação das funções de lista
├── pilha.h       # Definição da estrutura de pilha
├── pilha.cpp     # Implementação das funções de pilha
├── fila.h        # Definição da estrutura de fila
└── fila.cpp      # Implementação das funções de fila
```

## 🛠️ Requisitos

- GCC 7.0 ou superior
- Sistema operacional Unix-like (Linux, macOS)
- Make (opcional, para compilação automatizada)

## 🤝 Contribuindo

1. Faça um fork do projeto
2. Crie uma branch para sua feature (`git checkout -b feature/nova-feature`)
3. Commit suas mudanças (`git commit -m 'Adiciona nova feature'`)
4. Push para a branch (`git push origin feature/nova-feature`)
5. Abra um Pull Request

## 📝 Licença

Este projeto está sob a licença MIT. Veja o arquivo [LICENSE](LICENSE) para mais detalhes.

## 👥 Autores

- João Vitor Soares - [@seu-usuario](https://github.com/hijao08)

## 🙏 Agradecimentos

- A todos os contribuidores que ajudaram no desenvolvimento deste projeto
- À comunidade open source por inspirar e fornecer ferramentas essenciais
