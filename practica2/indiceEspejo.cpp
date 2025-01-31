#include<iostream>
#include<vector>
using namespace std;

void indiceEspejo (const vector<int>& v, int& ind, int i, int j) {
    if (i == j - 1) {
        if (i + 1 == v[i]) {
            ind = i + 1; 
            return;
        } else if (j + 1 == v[j]) {
            ind = j + 1;
            return;
        }
        return;
    }
    int medio = (i + j) / 2;
    // Caso a_medio > medio + 1 (=> el índice solo puede estar atrás de 'medio').
    if (v[medio] > medio + 1) return indiceEspejo (v, ind, i, medio);
    // Caso a_medio < medio + 1 (=> el índice solo puede estar adelante de 'medio').
    if (v[medio] < medio + 1) return indiceEspejo (v, ind, medio, j);
    // Caso a_medio == medio + 1.
    ind = medio + 1;
    return;
}

void call_indiceEspejo (const vector<int>& v) {
    int ind = - 1;
    indiceEspejo (v, ind, 0, v.size() - 1);
    if (ind != - 1) cout << "El índice espejo es " << ind << "." << endl;
    else cout << "No hay índice espejo." << endl;
}

int main ()
{
    // TEST ENUNCIADO
    vector<int> v = {-4, -1, 2, 4, 7};
    call_indiceEspejo (v);
    // TESTS PROPIOS
    vector<int> w = {1, 4, 7, 9, 6, 11};
    call_indiceEspejo (w);
    vector<int> x = {-4, -1, 2, 5, 7};
    call_indiceEspejo (x);

    return 0;
}