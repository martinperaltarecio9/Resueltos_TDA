#include <iostream>
#include <vector>
using namespace std;

int rutaEficiente (const vector<int>& estaciones, int aut, vector<int>& dondeParo, int ultParada) {
    if (estaciones[estaciones.size() - 1] - estaciones[ultParada] <= aut) return 0;
    for (int i = ultParada + 1; i < estaciones.size(); i ++) {
        if (estaciones[i] - estaciones[ultParada] > aut) {
            dondeParo[i - 1] = 1;
            return 1 + rutaEficiente (estaciones, aut, dondeParo, i - 1);
        }
    }
    return 0;
}

int main () 
{
    vector<int> estaciones = {0, 23, 70, 115, 135, 200, 223, 248, 290, 344, 350, 400, 401, 445, 500};
    int aut = 65;
    vector<int> dondeParar (estaciones.size(), 0);
    cout << (rutaEficiente (estaciones, aut, dondeParar, 0) == 9)<< endl;
    cout << "Donde parar: {";
    for (int i = 0; i < dondeParar.size(); i ++) {
        if (i == dondeParar.size() - 1) cout << dondeParar[i];
        else cout << dondeParar[i] << ", ";
    }
    cout << "}" << endl;
    return 0;
}