
template <class T>
Conjunto<T>::Conjunto() : _raiz(NULL) {}

template <class T>
Conjunto<T>::~Conjunto() { 
    destruirNodos(_raiz);
}

template <class T>
bool Conjunto<T>::perteneceSubArbol(Nodo* &nodo, const T& clave) const {
    bool esta = false;
    if(nodo->valor == clave){ // CASO BASE
        esta = true;
    } else if(nodo->izq != NULL && nodo->valor > clave) {
        esta = perteneceSubArbol(nodo->izq,clave);
    } else if(nodo->der != NULL && nodo->valor < clave) {
        esta = perteneceSubArbol(nodo->der, clave);
    }
    return esta;
}

template <class T>
bool Conjunto<T>::pertenece(const T& clave) const {
    Nodo* actual = _raiz;
    bool esta = false;
    if(actual != NULL) {
        if (actual->valor == clave) { // CASO BASE
            esta = true;
        } else if (actual->izq != NULL && actual->valor > clave) {
            esta =  perteneceSubArbol(actual->izq, clave);
        } else if (actual->der != NULL && actual->valor < clave) {
            esta = perteneceSubArbol(actual->der, clave);
        }
    }
    return esta;
}

template <class T>
void Conjunto<T>::insertar(const T& clave) {
    Nodo* actual = _raiz;
    Nodo* nuevo = new Nodo(clave);
    if(_raiz == NULL){
        _raiz = nuevo;
        return;
    }
    while(true){
        if(actual->valor == clave){
            delete nuevo;
            return;
        } else if(actual->valor < clave){
            if(actual->der == NULL){
                actual->der = nuevo;
                return;
            }else{
                actual = actual->der;
            }
        } else if(actual->valor > clave){
            if(actual->izq == NULL){
                actual->izq = nuevo;
                return;
            }else{
                actual = actual->izq;
            }
        }
    }
}

template<class T>
void Conjunto<T>::remover(const T &clave) {
    Nodo* actual = _raiz;
    if(actual == NULL){
        return;
    }
    if(actual->valor == clave && actual->der == NULL && actual->izq == NULL){
        delete actual;
        _raiz = NULL;
    } else {
        Nodo *padre = NULL;
        while (actual->valor != clave) {
            if (actual->valor > clave) {
                padre = actual;
                actual = actual->izq;
            } else {
                padre = actual;
                actual = actual->der;
            }
        }
        // ACTUAL NO TIENE HIJOS Y NO ES RAIZ
        if(actual->der == NULL && actual->izq == NULL){
            if(padre->izq == actual){
                padre->izq = NULL;
            } else {
                padre->der = NULL;
            }
            delete actual;
        } else if (actual->izq == NULL) { // ACTUAL TIENE UN HIJO (IZQ O DER). HAY HIJO DERECHO
            if(padre == NULL){
                _raiz = actual->der;
                delete actual;
            } else { //
                if(padre->izq == actual){
                    padre->izq = actual->der;
                    delete actual;
                } else {
                    padre->der = actual->der;
                    delete actual;
                }
            }
        } else if (actual->der == NULL) { // ACTUAL TIENE UN HIJO (IZQ O DER). HAY HIJO IZQUIERDO
            if (padre == NULL) {
                _raiz = actual->izq;
                delete actual;
            } else { //
                if (padre->izq == actual) {
                    padre->izq = actual->izq;
                    delete actual;
                } else {
                    padre->der = actual->izq;
                    delete actual;
                }
            }
        } else { // ACTUAL TIENE DOS HIJOS
            Nodo* padre_sig = actual;
            Nodo* siguiente = actual->der;
            while(siguiente->izq != NULL){ // Menor del subarbol derecho
                padre_sig = siguiente;
                siguiente = siguiente->izq;
            }
            actual->valor = siguiente->valor;
            if(siguiente == padre_sig->izq){
                padre_sig->izq = siguiente->der;
            } else {
                padre_sig->der = siguiente->der;
            }
            delete siguiente;
        }
    }
}

template <class T>
void Conjunto<T>::buscarElementoSubarbol(Nodo* &actual, const T& clave, Nodo* &nodo) const {
    if(actual->valor == clave){ // CASO BASE
        nodo = actual;
    } else if(actual->izq != NULL && actual->valor > clave) {
        buscarElementoSubarbol(actual->izq,clave,nodo);
    } else if(actual->der != NULL && actual->valor < clave) {
        buscarElementoSubarbol(actual->der, clave,nodo);
    }
}

template <class T>
void Conjunto<T>::buscarElemento(const T& clave, Nodo* &nodo) const {
    Nodo* actual = nodo;
    if (actual->valor == clave) { // CASO BASE
        nodo = actual;
    } else if (actual->izq != NULL && actual->valor > clave) {
        buscarElementoSubarbol(actual->izq, clave, nodo);
    } else if (actual->der != NULL && actual->valor < clave) {
        buscarElementoSubarbol(actual->der, clave, nodo);
    }
}



template <class T>
const T& Conjunto<T>::siguiente(const T& clave) {
    // Buscar clave en arbol binario y pararme ahí.
    Nodo *actual = _raiz;
    Nodo *padre = _raiz;
    while (actual->valor != clave) {
        if (actual->valor > clave) {
            padre = actual;
            actual = actual->izq;
        } else {
            padre = actual;
            actual = actual->der;
        }
    }
    // ELEMENTO TIENE HIJO DERECHO -> Busco minimo en subarbol derecho
    if (actual->der != NULL) {
        return minimoDesde(actual->der);
    }
        // ELEMENTO TIENE !HIJO DERECHO -> Es hijo izquierdo -> Siguiente es padre
    else {
        if (padre->izq == actual) {
            return padre->valor;
        } else { // -> Es hijo derecho -> Siguiente es ultimo padre mayor que el elemento
            Nodo *siguiente = _raiz;
            Nodo *x = _raiz;
            while (x->valor != clave) {
                if (x->valor > clave) {
                    siguiente = x;
                    x = x->izq;
                } else {
                    x = x->der;
                }
            }
            return siguiente->valor;
        }
    }
}

template <class T>
const T& Conjunto<T>::minimoDesde(Nodo* min) const {
    while(min->izq != NULL){
        min = min->izq;
    }
    return min->valor;
}

template <class T>
const T& Conjunto<T>::minimo() const {
    Nodo* min = _raiz;
    while(min->izq != NULL){
        min = min->izq;
    }
    return min->valor;
}

template <class T>
const T& Conjunto<T>::maximo() const {
    Nodo* max = _raiz;
    while(max->der != NULL){
        max = max->der;
    }
    return max->valor;
}

template <class T>
unsigned int Conjunto<T>::contarNodosDesde(Nodo* nodo) const {
    unsigned int contador = 0;
    if(nodo != NULL){
        contador = 1 + contarNodosDesde(nodo->izq) + contarNodosDesde(nodo->der);
    }
    return contador;
}

template <class T>
unsigned int Conjunto<T>::cardinal() const {
    return contarNodosDesde(_raiz);
}

template <class T>
void Conjunto<T>::mostrar(std::ostream&) const {
    assert(false);
}

template <class T>
void Conjunto<T>::destruirNodos(Nodo* nodo) {
    if(nodo != NULL){
        destruirNodos(nodo->izq);
        destruirNodos(nodo->der);
        delete nodo;
    }
    _raiz = NULL;
}

