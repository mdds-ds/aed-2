#include "puesto.h"

puesto::puesto(Menu m, Stock s, Promociones p): stock(s), menu(m), promos(p), ventas(), gastoPorPersona(){}




const Nat  puesto::obtenerStock(const Producto& i) const  {
    if(stock.count(i) == 1) {
        return stock.at(i);
    }else{                              // hacemos esto para simplificarnos la implementacion de puestoConMenorStockDe
        return 0;
    }
}


const Nat&  puesto::obtenerPrecio(const Producto& i)  const{
    return menu.at(i);
}


const Nat puesto::obtenerDescuento(const Producto& i, const Nat& cant)  {
    Nat res = 0;
    if (promos.count(i) == 1){
        if (promos.at(i).count(cant)==1){
            return promos.at(i).at(cant);
        }else{
           auto iter = promos.at(i).insert(make_pair(cant, 1)).first;
            if (iter-- != promos.at(i).end()){


                promos.at(i).erase(cant);
                return (iter->second);
            }else{
                promos.at(i).erase(iter);
                return 0;
            }

        }
    }
    return 0;
}




const Nat  puesto::obtenerGasto(const Persona & a)  const{
    if (gastoPorPersona.count(a)==1){
        return gastoPorPersona.at(a);
    }else{
        return 0;
    }


}

int puesto::calcularCompra(const Producto &i,const Nat &cant){
    int res = (menu.at(i) * (100-(obtenerDescuento(i,cant)))) /100 * cant;
    return res;
}


void puesto::venta(const Persona &per, const Producto &i, const Nat &cant) {

    stock.at(i) = stock.at(i) - cant;
    if(gastoPorPersona.count(per) == 1) {
        gastoPorPersona.at(per) = gastoPorPersona.at(per) + calcularCompra(i, cant);
    } else {
        gastoPorPersona.insert(make_pair(per,calcularCompra(i, cant)));
    }

    if (ventas.count(per)==1){
        if (ventas.at(per).count(i)==1){
            ventas.at(per).at(i).push_back(cant);
            if (obtenerDescuento(i,cant)==0){
                itL it = ventas.at(per).at(i).end()--;

                if (itVentasSinPromo.count(per) == 1){

                    if (itVentasSinPromo.at(per).count(i)==1){
                        itVentasSinPromo.at(per).at(i).push_back(it);
                    }else{
                        itVentasSinPromo.at(per).insert(make_pair(i,list<itL>()));
                        itVentasSinPromo.at(per).at(i).push_back(it);
                    }
                }else{
                    map<Producto ,list<itL>> a;
                    a.insert(make_pair(i,list<itL>()));
                    a.at(i).push_back(it);
                    itVentasSinPromo.insert(make_pair(per,a));
                }
            }
        } else {

            ventas.at(per).insert(make_pair(i,list<Nat>()));
            ventas.at(per).at(i).push_back(cant);

            if (obtenerDescuento(i,cant)==0){
                itL it = ventas.at(per).at(i).end()--;

                if (itVentasSinPromo.count(per) == 1){

                    if (itVentasSinPromo.at(per).count(i)==1){
                        itVentasSinPromo.at(per).at(i).push_back(it);
                    }else{
                        itVentasSinPromo.at(per).insert(make_pair(i,list<itL>()));
                        itVentasSinPromo.at(per).at(i).push_back(it);
                    }
                }else{
                    map<Producto ,list<itL>> a;
                    a.insert(make_pair(i,list<itL>()));
                    a.at(i).push_back(it);
                    itVentasSinPromo.insert(make_pair(per,a));
                }
            }
        }
    } else {
        map<Producto,list<Nat>> compras;
        compras.insert(make_pair(i,list<Nat>()));
        compras.at(i).push_back(cant);
        ventas.insert(make_pair(per,compras));

        if (obtenerDescuento(i,cant)==0){
            itL it = --ventas.at(per).at(i).end();

            if (itVentasSinPromo.count(per) == 1){

                if (itVentasSinPromo.at(per).count(i)==1){
                    itVentasSinPromo.at(per).at(i).push_back(it);
                }else{
                    itVentasSinPromo.at(per).insert(make_pair(i,list<itL>()));
                    itVentasSinPromo.at(per).at(i).push_back(it);
                }
            }else{
                map<Producto ,list<itL>> a;
                a.insert(make_pair(i,list<itL>()));
                a.at(i).push_back(it);
                itVentasSinPromo.insert(make_pair(per,a));
            }
        }
    }
}

bool puesto::hackearP(const Persona per, const Producto i){
    bool res = true;
    auto it = *itVentasSinPromo.at(per).at(i).begin();
    if(*it > 1){
        *it =  *it - 1;
    } else {
        ventas.at(per).at(i).erase(it);
        itVentasSinPromo.at(per).at(i).pop_front();
        if(ventas.at(per).at(i).empty()){
            ventas.at(per).erase(i);
            if(ventas.at(per).empty()){
                ventas.erase(per);
            }
        }
        if(itVentasSinPromo.at(per).at(i).empty()){
            itVentasSinPromo.at(per).erase(i);
            res = false;
            if(itVentasSinPromo.at(per).empty()){
                itVentasSinPromo.erase(per);
            }
        }
    }

    if(gastoPorPersona.at(per) - menu.at(i)== 0){
        gastoPorPersona.erase(per);
    }else{
        gastoPorPersona.at(per) = gastoPorPersona.at(per) - menu.at(i);
    }

    stock.at(i) = stock.at(i) +1;
    return res;
}
