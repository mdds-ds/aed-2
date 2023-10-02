#include <iostream>
#include <list>

using namespace std;

using uint = unsigned int;

// Pre: 0 <= mes < 12
uint dias_en_mes(uint mes) {
    uint dias[] = {
            // ene, feb, mar, abr, may, jun
            31, 28, 31, 30, 31, 30,
            // jul, ago, sep, oct, nov, dic
            31, 31, 30, 31, 30, 31
    };
    return dias[mes - 1];
}

// Ejercicio 7, 8, 9 y 10

// Clase Fecha
class Fecha {
public:
    Fecha(int mes, int dia);
    int mes();
    int dia();
    // Completar declaraciones funciones
    void incrementar_dia();
#if EJ >= 9 // Para ejercicio 9
    bool operator==(Fecha o);
#endif

private:
    //Completar miembros internos
    int _mes;
    int _dia;
};

Fecha::Fecha(int mes, int dia): _mes(mes), _dia(dia) {}

int Fecha::mes(){
    return _mes;
}

int Fecha::dia(){
    return _dia;
}

ostream& operator<<(ostream &os, Fecha f){
    os << f.dia() << "/" << f.mes();
    return os;
}

#if EJ >= 9
bool Fecha::operator==(Fecha o) {
    bool igual_dia = this->dia() == o.dia();
    // Completar iguadad (ej 9)
    bool igual_mes = this->mes() == o.mes();
    return igual_dia && igual_mes;
}

void Fecha::incrementar_dia() {
    _dia++;
    if (_dia > dias_en_mes(_mes)){
        _dia = 1;
        _mes++;
        if(_mes > 12){
            _mes = 1;
        }
    }
}

#endif



// Ejercicio 11, 12

// Clase Horario
class Horario {
public:
    Horario(uint hora, uint min);
    uint hora();
    uint min();
    bool operator<(Horario h);
    // Completar declaraciones funciones

private:
    //Completar miembros internos
    int _hora;
    int _min;
};



uint Horario::hora() {
    return _hora;
}

uint Horario::min() {
    return _min;
}

Horario::Horario(uint hora, uint min): _hora(hora), _min(min) {}

bool Horario::operator<(Horario h) {
    if(h.hora() > _hora){
        return true;
    } else {
        if(h.hora() == _hora){
            if (h.min() > _min){
                return true;
            } else {
                return false;
            }
        } else {
            return false;
        }
    }
}

ostream& operator<<(ostream &os, Horario h){
    os << h.hora() << ":" << h.min();
    return os;
}

// Ejercicio 13
#if EJ>=13
class Recordatorio {
public:
    Recordatorio(Fecha fecha, Horario horario, string msg);
    Fecha fecha();
    Horario horario();
    string msg();
    bool operator<(Recordatorio r);
private:
    Fecha _fecha;
    Horario _horario;
    string _msg;
};

Recordatorio::Recordatorio(Fecha fecha, Horario horario, string msg) :
        _fecha(fecha), _horario(horario), _msg(msg){
}

Fecha Recordatorio::fecha() {
    return _fecha;
}

Horario Recordatorio::horario() {
    return _horario;
}

string Recordatorio::msg() {
    return _msg;
}

bool Recordatorio::operator<(Recordatorio r) {
    bool res;
    if (horario() < r.horario()) {
        res = true;
    } else {
        res = false;
    }

    return res;
}

ostream& operator<<(ostream& os, Recordatorio r) {
    os << r.msg()<< " @ " <<r.fecha() << " " << r.horario();
    return os;
}
# endif



// Ejercicio 14
class Agenda {
public:
    Agenda(Fecha fecha_inicial);
    void agregar_recordatorio(Recordatorio rec);
    void incrementar_dia();
    list<Recordatorio> recordatorios_de_hoy();
    Fecha hoy();

private:
    Fecha _fecha;
    list<Recordatorio> _recordatorios;

};

Agenda::Agenda(Fecha fecha_inicial) :
        _fecha(fecha_inicial){
}

Fecha Agenda::hoy() {
    return _fecha;
}

void Agenda::incrementar_dia() {
    _fecha.incrementar_dia();
}

void Agenda::agregar_recordatorio(Recordatorio rec) {
    _recordatorios.push_back(rec);
}

list <Recordatorio> Agenda::recordatorios_de_hoy() {
    list<Recordatorio> rec_de_hoy;
    list<Recordatorio> record = _recordatorios;
    for (int i = 0; i < _recordatorios.size(); ++i) {
        if (record.front().fecha() == _fecha) {
            rec_de_hoy.push_back(record.front());
        }
        record.pop_front();
    }
    rec_de_hoy.sort();
    return rec_de_hoy;
}

ostream& operator<<(ostream& os, Agenda a) {
    list<Recordatorio> rec_de_hoy = a.recordatorios_de_hoy();
    os << a.hoy() << endl;
    os << "=====" << endl;
    for (int i = 0; i < a.recordatorios_de_hoy().size(); ++i) {
        os << rec_de_hoy.front() << endl;
        rec_de_hoy.pop_front();
    }
    return os;
}

