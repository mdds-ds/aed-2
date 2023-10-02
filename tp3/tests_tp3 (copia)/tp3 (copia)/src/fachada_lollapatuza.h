#ifndef FACHADA_LOLLAPATUZA_H
#define FACHADA_LOLLAPATUZA_H

#include <set>
#include <map>
#include "tipos.h"
#include "lollapatuza.h"
#include "puesto.h"


class FachadaLollapatuza {
public:
    FachadaLollapatuza(const set<Persona>& personas, const map<IdPuesto, aed2_Puesto>& infoPuestos);

    void registrarCompra(Persona persona, Producto producto, Nat cant, IdPuesto idPuesto);
    void hackear(Persona persona, Producto producto);

    Nat gastoTotal(Persona persona) const;
    Persona mayorGastador() const;
    IdPuesto menorStock(Producto producto) const;

    const set<Persona>& personas() const;

    Nat stockEnPuesto(IdPuesto idPuesto, const Producto& producto) const;
    Nat descuentoEnPuesto(IdPuesto idPuesto, const Producto& producto, Nat cantidad) const;
    Nat gastoEnPuesto(IdPuesto idPuesto, Persona persona) const;

    /**
     * Devuelve el conjunto de los los ids de todos los puestos;
    */
    set<IdPuesto> idsDePuestos() const;
    puesto AED2APuesto(aed2_Puesto aed);

private:
    lollapatuza lolla;

    map<IdPuesto,puesto> diccAEDADiccPuestos(map<IdPuesto,aed2_Puesto> infoPuestos);
};

#endif
