//
// Created by matias_sarm on 28/06/23.
//
#include "lollapatuza.h"

lollapatuza::lollapatuza(map<IdPuesto ,puesto> Ps, set<Persona> Pers): puestos(Ps), personas(Pers), mayorgastador(0), gastoPorPersona(
        gastoPorPersonaInicial(Pers)), puestosHackeables(), gastos(){};

Persona lollapatuza::mayorGastador() const{
    return mayorgastador;
}

const set<Persona>& lollapatuza::obtenerPersonas() const{
    return personas;
}

const map<IdPuesto,puesto>& lollapatuza::obtenerPuestos() const{
    return puestos;
}

const IdPuesto& lollapatuza::puestoConMenorStockDe(const Producto &i) const{
    auto res = puestos.begin();
    for(auto it = puestos.begin(); it != puestos.end(); it++){
        if(it->second.obtenerStock(i) > res->second.obtenerStock(i)){
            res = it;
        }
    }
    return res->first;
}

const Nat &lollapatuza::gastoTotalPersona(const Persona per) const {
    return gastoPorPersona.at(per);
}

map<Persona,Nat> lollapatuza::gastoPorPersonaInicial(set<Persona> per){
    map<Persona,Nat> a;
    for(auto it = per.begin(); it!=per.end(); it++){
        a.insert({*it, 0});
    }
    return a;
}

void lollapatuza::hackearItem(Persona per, Producto i) {
auto it = puestosHackeables.at(per).at(i).begin();
IdPuesto id = it->first;
bool esHackeable = puestos.at(id).hackearP(per,i);
if(!esHackeable){
    puestosHackeables.at(per).at(i).erase(it);
}
if(puestosHackeables.at(per).at(i).empty()){
    puestosHackeables.at(per).erase(i);
}
if(puestosHackeables.at(per).empty()){
    puestosHackeables.erase(per);
}
Nat gastoAnt = gastoPorPersona.at(per);
Nat gastoNuevo = gastoPorPersona.at(per) - puestos.at(id).obtenerPrecio(i);

if(gastoNuevo != 0){
    gastoPorPersona.at(per) = gastoNuevo;
    if(gastos.count(gastoNuevo) == 1){
        gastos.at(gastoNuevo).insert(make_pair(per,per));
    }else{
        map<Persona ,Persona > mapPers;
        mapPers.insert(make_pair(per,per));
        gastos.insert(make_pair(gastoNuevo,mapPers));
    }
}else{
    gastoPorPersona.erase(per);
}
gastos.at(gastoAnt).erase(per);
if(gastos.at(gastoAnt).empty()){
    gastos.erase(gastoAnt);
}

if(per == mayorgastador){
    if(gastos.count(gastoAnt) == 1){
        Persona nuevoGastador = gastos.at(gastoAnt).begin()->first;
        mayorgastador = nuevoGastador;

    }else{
        auto itNuevoGastador = gastos.end()--;
        Nat mayorGasto = itNuevoGastador->first;
        Persona nuevoGastador = gastos.at(mayorGasto).begin()->first;
        mayorgastador = nuevoGastador;
    }
}
}

void lollapatuza::registrarCompra(IdPuesto idPuesto, Persona per, Producto i, Nat &c) {

    puestos.at(idPuesto).venta(per,i,c);
    if(gastoPorPersona.count(per)==1){
        Nat gastoAnt = gastoPorPersona.at(per);
        Nat gastoNuevo = gastoPorPersona.at(per) + puestos.at(idPuesto).calcularCompra(i,c);
        gastoPorPersona.at(per)=gastoNuevo;
        gastos.at(gastoAnt).erase(per);
        if(gastos.at(gastoAnt).empty()){
            gastos.erase(gastoAnt);
        }
        if(gastos.count(gastoNuevo) == 1){
            gastos.at(gastoNuevo).insert(make_pair(per,per));
        }else{
            map<Persona ,Persona > mapPers;
            mapPers.insert(make_pair(per,per));
            gastos.insert(make_pair(gastoNuevo,mapPers));
        }
    }
    else{
        Nat gastoNuevo=puestos.at(idPuesto).calcularCompra(i,c);
        gastoPorPersona.insert(make_pair(per,gastoNuevo));
        if(gastos.count(gastoNuevo) == 1){
            gastos.at(gastoNuevo).insert(make_pair(per,per));
        }else{
            map<Persona ,Persona > mapPers;
            mapPers.insert(make_pair(per,per));
            gastos.insert(make_pair(gastoNuevo,mapPers));
        }

    }
    Nat gastoNuevo=gastoPorPersona.at(per);
    if(per!=mayorgastador && gastoNuevo>gastoPorPersona.at(mayorgastador)){
        mayorgastador=per;
    }
    if(puestos.at(idPuesto).obtenerDescuento(i,c)==0) {
        if(puestosHackeables.count(per)==1){
            if(puestosHackeables.at(per).count(i)==1){
                if(puestosHackeables.at(per).at(i).count(idPuesto)==0) {
                    puestosHackeables.at(per).at(i).insert(make_pair(idPuesto,idPuesto));
                }
            }else{
                map<IdPuesto,IdPuesto> a;
                a.insert(make_pair(idPuesto,idPuesto));
                puestosHackeables.at(per).insert(make_pair(i,a));
            }
        }else{
            map<Producto ,map<IdPuesto ,IdPuesto>> b;
            map<IdPuesto ,IdPuesto > c;
            c.insert((make_pair(idPuesto,idPuesto)));
            b.insert(make_pair(i,c));
            puestosHackeables.insert(make_pair(per,b));
        }
    }
}
