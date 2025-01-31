#include<iostream>
#include<vector>
using namespace std;

bool masIzquierda (const vector<int>& v, const vector<int>& sumaHasta, int i, int j) {
    if (i == j - 1) return (v[i] >= v[j]);
    int medio = (i + j) / 2;
    if (2 * sumaHasta[medio] < sumaHasta[j]) return false;
    return (masIzquierda (v, sumaHasta, i, medio) && masIzquierda (v, sumaHasta, medio + 1, j));
}

bool call_masIzquierda (const vector<int>& v) {
    vector<int> sumaHasta (v.size(), 0);
    int suma = 0;
    for (int i = 0; i < sumaHasta.size(); i ++) {
        suma += v[i];
        sumaHasta[i] = suma;
    }
    return masIzquierda (v, sumaHasta, 0, v.size() - 1);
}

int main ()
{
    // TESTS DEL ENUNCIADO
    vector<int> v = {8, 6, 7, 4, 5, 1, 3, 2};
    vector<int> w = {8, 4, 7, 6, 5, 1, 3, 2};
    cout << (call_masIzquierda (v) == true) << endl;
    cout << (call_masIzquierda (w) == false) << endl;
    return 0;
}