# Gerenciador de Tarefas

Um aplicativo de linha de comando em C++ para gerenciar tarefas e compromissos de forma eficiente.

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

- Seu Nome - [@seu-usuario](https://github.com/seu-usuario)

## 🙏 Agradecimentos

- A todos os contribuidores que ajudaram no desenvolvimento deste projeto
- À comunidade open source por inspirar e fornecer ferramentas essenciais
