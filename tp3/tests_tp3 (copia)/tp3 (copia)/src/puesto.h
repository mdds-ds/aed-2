
/*
#ifndef TP_LOLLA_PUESTO_H
#define TP_LOLLA_PUESTO_H
*/

#ifndef puesto_h
#define puesto_h

#include <string>
#include <map>
#include <list>
#include "tipos.h"

using namespace std;






class puesto {

public:

    //Constructor
    puesto(Menu m, Stock s, Promociones p);

    const Nat obtenerStock(const Producto&) const ;


    const Nat& obtenerPrecio(const Producto&) const ;


    const Nat obtenerDescuento(const Producto& i, const Nat& cant) ;


    const Nat obtenerGasto(const Persona& per) const;


    void venta(const Persona& per, const Producto& i, const Nat& cant);

    bool hackearP(const Persona per, const Producto i);
    int calcularCompra(const Producto &i,const Nat &cant);





private:

    Menu menu;
    Stock stock;
    Promociones promos;
    map<Persona,Nat> gastoPorPersona;
    map<Persona, map<Producto,list<Nat>>> ventas;
    map<Persona,map<Producto,list<itL>>> itVentasSinPromo;

};

















#endif //puesto_h

//TP_LOLLA_PUESTO_H
