#ifndef FILA_H
#define FILA_H

#include "tarefa.h"

template<typename T>
class Fila {
private:
    T* elementos;
    int frente;
    int tras;
    int capacidade;
    int tamanho_atual;

public:
    Fila(int tamanho = 100);
    ~Fila();
    void enfileirar(T elemento);
    T desenfileirar();
    T primeiro();
    bool vazia();
    bool cheia();
    int tamanho();
};

#endif
