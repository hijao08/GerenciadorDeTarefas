#include "pilha.h"
#include <iostream>

using namespace std;

template <typename T>
Pilha<T>::Pilha(int tamanho) {
    elementos = new T[tamanho];
    capacidade = tamanho;
    topo = -1;
}

template <typename T>
Pilha<T>::~Pilha() {
    delete[] elementos;
}

template <typename T>
void Pilha<T>::empilhar(T elemento) {
    if (!cheia()) {
        topo++;
        elementos[topo] = elemento;
    } else {
        cout << "Erro: Pilha cheia!" << endl;
    }
}

template <typename T>
T Pilha<T>::desempilhar() {
    if (!vazia()) {
        T elemento = elementos[topo];
        topo--;
        return elemento;
    }
    cout << "Erro: Pilha vazia!" << endl;
    return nullptr;
}

template <typename T>
T Pilha<T>::topoPilha() {
    if (!vazia()) {
        return elementos[topo];
    }
    cout << "Erro: Pilha vazia!" << endl;
    return nullptr;
}

template <typename T>
bool Pilha<T>::vazia() {
    return topo == -1;
}

template <typename T>
bool Pilha<T>::cheia() {
    return topo == capacidade - 1;
}

template <typename T>
int Pilha<T>::tamanho() {
    return topo + 1;
}

// Instanciação explícita para o tipo Tarefa
template class Pilha<Tarefa*>;
