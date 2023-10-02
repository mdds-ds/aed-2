#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <cmath>

using namespace std;


int cantidadTest;
int n;
vector<int> tiempos;

vector<int> descontentos;


int aux (){
    vector<pair<int,int>> coef(n);
    for(int i =0; i< tiempos.size();i++){
        pair<int,int> tupla = make_pair(descontentos[i]/tiempos[i],i);
        //tuple<float,int> tupla = tuple(float(descontentos[i]/tiempos[i]),i);
        coef[i] = tupla;
    }

    sort(coef.begin(), coef.end());

    int res = 0;
    int minutos = 0;
    for (int i = n-1; i >= 0; --i) {
        minutos += tiempos[(coef[i].second)];
        long long desc = descontentos[(coef[i].second)] * minutos;
        res = (desc % int((pow(10,9) + 7)))+ res;
    }

    res = int(res) % int((pow(10,9) + 7));

    return res;

}



// 100000 100000 10000 20000

int main() {

    cin >> cantidadTest;
    for(int j = 0; j<cantidadTest; j++){
        cin >> n;

        tiempos.resize(n);
        descontentos.resize(n);
        for(int i=0; i<n; i++){
            int tiempo;
            cin >> tiempo;
            tiempos[i] = int(tiempo) % int((pow(10,9) + 7));
        }

        for(int i=0; i<n; i++){
            int molestia;
            cin >> molestia;
            descontentos[i] = int(molestia) % int((pow(10,9) + 7));
        }

        int res = aux();
        cout << res << "\n";
    }

}
