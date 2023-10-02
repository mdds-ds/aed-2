#ifndef SOLUCION_TIPOS_H
#define SOLUCION_TIPOS_H

#include <string>
#include <map>
#include <list>

using namespace std;

using Persona = int;
using IdPuesto = int;
using Producto = int;
using Nat = unsigned int;
using Stock = map<Producto, Nat>;
using Promociones = map<Producto, map<Nat, Nat>>;
using Menu = map<Producto, Nat>;
using itL = list<Nat>::iterator;

struct aed2_Puesto {
    Stock stock;
    Promociones promociones;
    Menu menu;
};

#endif //SOLUCION_TIPOS_H
