// pilha.h
#ifndef PILHA_H
#define PILHA_H

#include "tarefa.h"

template<typename T>
class Pilha {
private:
    T* elementos;
    int topo;
    int capacidade;

public:
    Pilha(int tamanho = 100);
    ~Pilha();
    void empilhar(T elemento);
    T desempilhar();
    T topoPilha();
    bool vazia();
    bool cheia();
    int tamanho();
};

#endif

