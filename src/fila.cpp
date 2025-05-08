#include "fila.h"
#include <iostream>

using namespace std;

template<typename T>
Fila<T>::Fila(int tamanho) {
    elementos = new T[tamanho];
    capacidade = tamanho;
    frente = 0;
    tras = -1;
    tamanho_atual = 0;
}

template<typename T>
Fila<T>::~Fila() {
    delete[] elementos;
}

template<typename T>
void Fila<T>::enfileirar(T elemento) {
    if (!cheia()) {
        tras = (tras + 1) % capacidade;
        elementos[tras] = elemento;
        tamanho_atual++;
    } else {
        cout << "Erro: Fila cheia!" << endl;
    }
}

template<typename T>
T Fila<T>::desenfileirar() {
    if (!vazia()) {
        T elemento = elementos[frente];
        frente = (frente + 1) % capacidade;
        tamanho_atual--;
        return elemento;
    }
    cout << "Erro: Fila vazia!" << endl;
    return nullptr;
}

template<typename T>
T Fila<T>::primeiro() {
    if (!vazia()) {
        return elementos[frente];
    }
    cout << "Erro: Fila vazia!" << endl;
    return nullptr;
}

template<typename T>
bool Fila<T>::vazia() {
    return tamanho_atual == 0;
}

template<typename T>
bool Fila<T>::cheia() {
    return tamanho_atual == capacidade;
}

template<typename T>
int Fila<T>::tamanho() {
    return tamanho_atual;
}

// Instanciação explícita para Tarefa*
template class Fila<Tarefa*>;
