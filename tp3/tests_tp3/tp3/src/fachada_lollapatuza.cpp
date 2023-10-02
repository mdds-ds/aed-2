#include "fachada_lollapatuza.h"
#include "puesto.h"

FachadaLollapatuza::FachadaLollapatuza(const set<Persona> &personas, const map<IdPuesto, aed2_Puesto> &infoPuestos):
lolla(diccAEDADiccPuestos(infoPuestos), personas){}

map<IdPuesto,puesto> FachadaLollapatuza::diccAEDADiccPuestos(map<IdPuesto,aed2_Puesto> infoPuestos){
    map<IdPuesto,puesto> puestos;
    for(auto it = infoPuestos.begin(); it != infoPuestos.end(); it++){
        puesto p = AED2APuesto(it->second);
        puestos.insert({it->first, p});
    }
    return puestos;
}

puesto FachadaLollapatuza::AED2APuesto(aed2_Puesto aed) {
    return puesto(aed.menu, aed.stock, aed.promociones);
}

void FachadaLollapatuza::registrarCompra(Persona persona, Producto producto, Nat cant, IdPuesto idPuesto) {
    // TODO: Completar
    lolla.registrarCompra(idPuesto,persona,producto,cant);
}

void FachadaLollapatuza::hackear(Persona persona, Producto producto) {
    // TODO: Completar
    lolla.hackearItem(persona,producto);
}

Nat FachadaLollapatuza::gastoTotal(Persona persona) const {
    // TODO: Completar
    return lolla.gastoTotalPersona(persona);
}

Persona FachadaLollapatuza::mayorGastador() const {
    // TODO: Completar
    return lolla.mayorGastador();
}


IdPuesto FachadaLollapatuza::menorStock(Producto producto) const {
   // TODO: Completar
    return lolla.puestoConMenorStockDe(producto);
}

const set<Persona> &FachadaLollapatuza::personas() const {
    // TODO: Completar
    return lolla.obtenerPersonas();
}

Nat FachadaLollapatuza::stockEnPuesto(IdPuesto idPuesto, const Producto &producto) const {
    // TODO: Completar

    map<IdPuesto,puesto> a;
    a =lolla.obtenerPuestos();
   return (a.at(idPuesto)).obtenerStock(producto);

}

Nat FachadaLollapatuza::descuentoEnPuesto(IdPuesto idPuesto, const Producto &producto, Nat cantidad) const {
    // TODO: Completar
    map<IdPuesto,puesto> a = lolla.obtenerPuestos();
    return (a.at(idPuesto)).obtenerDescuento(producto,cantidad);
}

Nat FachadaLollapatuza::gastoEnPuesto(IdPuesto idPuesto, Persona persona) const {
    // TODO: Completar
    map<IdPuesto,puesto> a =lolla.obtenerPuestos();
    return (a.at(idPuesto)).obtenerGasto(persona);
}

set<IdPuesto> FachadaLollapatuza::idsDePuestos() const {
    // TODO: Completar
    set<IdPuesto> res;
    map<IdPuesto,puesto> a =lolla.obtenerPuestos();
    for(auto it = a.begin(); it != a.end(); it++){
        res.insert(it->first);
    }
    return res;
}
