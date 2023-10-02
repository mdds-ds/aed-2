#include "Lista.h"
#include <cassert>

Lista::Lista(): prim(NULL), ult(NULL) {}

Lista::Lista(const Lista& l) : Lista() {
    //Inicializa una lista vacía y luego utiliza operator= para no duplicar el código de la copia de una lista.
    *this = l;
}

Lista::~Lista() {
    destruirNodos();
}

Lista& Lista::operator=(const Lista& aCopiar) {
    destruirNodos();
    copiarNodos(aCopiar);
    return *this;
}

void Lista::agregarAdelante(const int& elem) {
    Nodo* nuevo = new Nodo(NULL, elem, prim);
    if(prim == NULL && ult == NULL){
        prim = nuevo;
        ult = nuevo;
    } else {
        prim->ant = nuevo;
        prim = nuevo;
    }
}

void Lista::agregarAtras(const int& elem) {
    Nodo* nuevo = new Nodo(ult, elem, NULL);
    if(prim == NULL && ult == NULL){
        prim = nuevo;
        ult = nuevo;
    } else {
        ult->sig = nuevo;
        ult = nuevo;
    }
}

void Lista::eliminar(Nat i) {
    Nodo* actual = prim;
    for (int j = 0; j < i; ++j) {
        actual = actual->sig;
    }
    Nodo* anterior = actual->ant;
    actual = actual->sig;
    actual->ant = anterior;
    anterior->sig = actual;
}

int Lista::longitud() const {
    Nodo* actual = prim;
    int contador = 0;
    while (actual != NULL) {
        contador++;
        actual = actual->sig;
    }
    return contador;
    //return -1;
}

const int& Lista::iesimo(Nat i) const {
    Nodo* actual = prim;
    for (int j = 0; j < i; ++j) {
        actual = actual->sig;
    }
    return actual->valor;
    assert(false);
}

int& Lista::iesimo(Nat i) {
    Nodo* actual = prim;
    for (int j = 0; j < i; ++j) {
        actual = actual->sig;
    }
    return actual->valor;
    assert(false);
}

void Lista::mostrar(ostream& o) {
    // Completar
}

void Lista::destruirNodos() {
    Nodo* actual = prim;
    while (actual != NULL) {
        Nodo* siguiente = actual->sig;
        delete actual;
        actual = siguiente;
    }
    prim = NULL;
}

void Lista::copiarNodos(const Lista &aCopiar) {
    Nodo* actual = aCopiar.prim;
    while (actual != NULL) {
        agregarAtras(actual->valor);
        actual = actual->sig;
    }
}