

#ifndef TP3_LOLLAPATUZA_H
#define TP3_LOLLAPATUZA_H

#endif //TP3_LOLLAPATUZA_H
#include <string>
#include <map>
#include <list>
#include "tipos.h"
#include "puesto.h"
#include <vector>
#include <set>

using namespace std;

class lollapatuza{
public:
    //Constructor
    lollapatuza(map<int,puesto> Ps, set<Persona> Pers);

    void registrarCompra(IdPuesto idPuesto, Persona a, Producto i, Nat &c);

    void hackearItem(Persona p, Producto i );

    const Nat& gastoTotalPersona(const Persona per) const;

    Persona mayorGastador() const;

    const IdPuesto& puestoConMenorStockDe(const Producto &i) const;

    const set<Persona>& obtenerPersonas() const;

    const map<IdPuesto ,puesto>& obtenerPuestos() const;

private:
    map<IdPuesto ,puesto> puestos; //DiccLog puestoID a Puesto, aed2_Puesto está en tipos.h
    set<Persona> personas;
    Persona mayorgastador;
    map<Persona,Nat> gastoPorPersona;  //diccLog(persona,dinero)
    map<Persona,map<Producto ,map<IdPuesto ,IdPuesto>>> puestosHackeables; //diccLog(persona,diccLog(item,diccLog(puestoID, puestoID))
    map<Nat,map<Persona,Persona>> gastos; //diccLog(dinero, diccLog(persona,persona))
    map<Persona, Nat> gastoPorPersonaInicial(set<Persona> per);
    map<Nat,map<Persona,Persona>> gastosIniciales(set<Persona> per);
};