template <typename T>
string_map<T>::string_map(): raiz(NULL), _size(0){}

template <typename T>
string_map<T>::string_map(const string_map<T>& aCopiar) : string_map() { *this = aCopiar; } // Provisto por la catedra: utiliza el operador asignacion para realizar la copia.

template <typename T>
string_map<T>::~string_map(){
    destruirNodos(raiz);
}

template<typename T>
void string_map<T>::insert(const pair<string, T> &par) {
    if(par.first.size() == 0){
        return;
    } else {
        if(raiz == NULL) {
            Nodo* nuevo = new Nodo;
            raiz = nuevo;
        }
        Nodo* actual = raiz;
        int j = 0;
        while(j<par.first.size() && actual->siguientes[int(par.first[j])] != NULL) {
            actual = actual->siguientes[int(par.first[j])];
            j++;
        }
        while(j<par.first.size()){
            Nodo* nuevo = new Nodo();
            actual->siguientes[int(par.first[j])] = nuevo;
            actual = actual->siguientes[int(par.first[j])];
            j++;
        }
        if(actual->definicion != NULL){
            delete actual->definicion;
        }
        T* def = new T(par.second);
        actual->definicion = def;
        _size++;
    }
}

template <typename T>
T& string_map<T>::operator[](const string& clave){
    // COMPLETAR
}


template <typename T>
int string_map<T>::count(const string& clave) const{
    if(raiz == NULL || clave.size() == 0){
        return 0;
    } else {
        Nodo* actual = raiz;
        int j = 0;
        while(j<clave.size() && actual != NULL){
            actual = actual->siguientes[int(clave[j])];
            j++;
        }
        if(actual == NULL){
            return 0;
        } else {
            if(actual->definicion != NULL){
                return 1;
            } else {
                return 0;
            }
        }
    }
}

template <typename T>
const T& string_map<T>::at(const string& clave) const {
    Nodo* actual = raiz;
    int j = 0;
    while(j<clave.size()){
        if(actual->siguientes[int(clave[j])] != NULL){
            actual = actual->siguientes[int(clave[j])];
        }
        j++;
    }
    return *(actual->definicion);
}

template <typename T>
T& string_map<T>::at(const string& clave) {
    Nodo* actual = raiz;
    int j = 0;
    while(j<clave.size()){
        if(actual->siguientes[int(clave[j])] != NULL){
            actual = actual->siguientes[int(clave[j])];
        }
        j++;
    }
    return *(actual->definicion);
}

/*void string_map<T>::erase(const string& clave) {
    Nodo* actual = raiz;
    Nodo* ultimo = NULL;
    int indice = 0;
    int i = 0;
    while(indice < clave.size()){
        if ((cantHijos(actual)>1 or actual->definicion!= NULL) and i<clave.size()-1){
            ultimo = actual;
            i = indice;
        }
        actual = actual->siguientes[int(clave[indice])];
        indice++;
    }
    _size--;
    delete actual->definicion;
    actual->definicion = NULL;
    if(esHoja(actual)==false){
        return;
    }
    if(ultimo==NULL and esHoja(actual)){
        destruirNodos(raiz);
        raiz=NULL;
    }else{
        if (esHoja(actual) ){
            ultimo = raiz;
            actual = ultimo->siguientes[int(clave[i])];
            ultimo->siguientes[int(clave[i])] = NULL;
            ultimo = actual;
            i++;
            while (actual!=NULL){
                actual = ultimo->siguientes[int(clave[i])];
                delete ultimo;
                ultimo = actual;
                i++;
            }
        }
    }
}*/

template <typename T>
void string_map<T>::erase(const string& clave) {
    Nodo* actual = raiz;
    Nodo* ultimo = raiz;
    int j = 0; // Contador de letras de la clave
    int i = 0; // Indice del ultimo nodo con dos o mas hijos
    while(j<clave.size()){
        if((cantHijos(actual)>1 || actual->definicion!= NULL) && i<clave.size()-1){
            ultimo = actual;
            i = j;
        }
        actual = actual->siguientes[int(clave[j])];
        j++;
    }
    _size--;
    delete actual->definicion;
    actual->definicion = NULL;
    if(ultimo==NULL && esHoja(actual)){
        destruirNodos(raiz);
    }else{
        if (esHoja(actual)){
            ultimo = raiz;
            actual = ultimo->siguientes[int(clave[i])];
            ultimo->siguientes[int(clave[i])] = NULL;
            ultimo = actual;
            i++;
            while (actual!=NULL){
                actual = ultimo->siguientes[int(clave[i])];
                delete ultimo;
                ultimo = actual;
                i++;
            }
        }
    }
}

template <typename T>
bool string_map<T>::esHoja(Nodo* nodo) {
    bool res = true;
    for (int i = 0; i < nodo->siguientes.size(); ++i) {
        if(nodo->siguientes[i] != NULL){
            res = false;
        }
    }
    return res;
}

template <typename T>
int string_map<T>::cantHijos(Nodo* actual) const{
    int hijos = 0;
    for(int i = 0; i<actual->siguientes.size(); i++){
        if(actual->siguientes[i] != NULL){
            hijos++;
        }
    }
    return hijos;
}

template <typename T>
int string_map<T>::size() const{
    return _size;
}

template <typename T>
bool string_map<T>::empty() const{
    return _size == 0;
}

template <typename T>
string_map<T>& string_map<T>::operator=(const string_map<T>& d) {
    destruirNodos(raiz);
    if (d.raiz != NULL){
        Nodo* nuevo = new Nodo;
        raiz = nuevo;
        copiarNodos(d.raiz, raiz);
    }else{
        raiz = NULL;
    }
}

template <typename T>
void string_map<T>::destruirNodos(Nodo* nodo){
    if(nodo != NULL){
        for(int i = 0; i<nodo->siguientes.size(); i++){
            destruirNodos(nodo->siguientes[i]);
        }
        delete nodo->definicion;
    }
    delete nodo;
}

template <typename T>
void string_map<T>::copiarNodos(const Nodo* d, Nodo* n) {
    if(d->definicion != NULL){
        T* def = new T(*(d->definicion));
        n->definicion = def;
    }
    for (int i = 0; i < d->siguientes.size(); ++i) {
        if (d->siguientes[i] != NULL){
            Nodo* nuevo1 = new Nodo;
            n->siguientes[i] = nuevo1;
            copiarNodos(d->siguientes[i], n->siguientes[i]);
        }
    }
}