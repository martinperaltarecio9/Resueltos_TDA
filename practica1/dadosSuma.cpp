#include <iostream>
#include <vector>
#include <chrono>
using namespace std;

int distinguibles (int n, int s, int k) {
    if (s > k*n) return 0;
    if (s < 0) return 0;
    // Si llegue al final y no sumo lo que tengo que sumar.
    if ((n == 0) && (s != 0)) return 0;
    // Si llegue al final y sumo lo que tengo que sumar.
    if ((n == 0) && (s == 0)) return 1;
    // Caso general.
    int suma = 0;
    for (int i = 1; i <= k; i ++) {
        suma += distinguibles (n - 1, s - i, k);
    }
    return suma;
}

int topDownD (vector<vector<int>>& M, int n, int s, int k) {
    // Si 's' es negativo paro.
    if (s < 0) return 0;
    // Si veo que ni haciendo que todas las que me quedan valgan k llego, paro.
    if (s > n*k) { // Aca esta el min {s, n * k}.
        M[n][s] = 0;
        return 0; 
    }
    // Si ya lo calcule antes.
    if (M[n][s] != -1) return M[n][s]; 
    // Si llegue al final y no sumo lo que tengo que sumar.
    if ((n == 0) && (s != 0)) {
        M[n][s] = 0;
        return 0;
    }
    // Si llegue al final y sumo lo que tengo que sumar.
    if ((n == 0) && (s == 0)) {
        M[n][s] = 1;
        return 1;
    }
    // Caso general.
    int suma = 0;
    for (int i = 1; i <= s; i ++) {
        suma += topDownD (M, n - 1, s - i, k);
    }
    M[n][s] = suma;
    return suma;
}

int indistinguibles (int n, int s, int k) {
    if (s < 0) return 0;
    if (s > n*k) return 0;
    if (s < n) return 0;
    // Si puse todas y no sumo lo que tengo que sumar.
    if ((n == 0) && (s != 0)) return 0;
    // Si pase por todos los casilleros pero no puse todas las bolas.
    if ((k == 0) && (n != 0)) return 0;
    // Si puse todas y sumo lo que tengo que sumar.
    if ((n == 0) && (s == 0)) return 1;
    // Caso general.
    int suma = 0;
    for (int i = 0; i <= n; i ++) {
        suma += indistinguibles (n - i, s - k*i, k - 1);
    }
    return suma;
}

int topDownI (vector<vector<vector<int>>>& M, int n, int s, int k) {
    // Si me pase paro.
    if (s < 0) return 0;
    // Si veo que ni haciendo que todas valgan k llego, paro.
    if (s > n*k) return 0;
    if (s < n) {
        M[n][s][k] = 0;
        return 0;
    }
    // Si puse todas y no sumo lo que tengo que sumar.
    if ((n == 0) && (s != 0)) {
        M[n][s][k] = 0;
        return 0;
    }
    // Si pase por todos los casilleros pero no puse todas las bolas.
    if ((k == 0) && (n != 0)) {
        M[n][s][k] = 0;
        return 0;
    }
    // Si puse todas y sumo lo que tengo que sumar.
    if ((n == 0) && (s == 0)) {
        M[n][s][k] = 1;
        return 1;
    }
    // Caso general.
    int suma = 0;
    for (int i = 0; i <= s; i ++) {
        suma += topDownI (M, n - i, s - k*i, k - 1);
    }
    M[n][s][k] = suma;
    return suma;
}

int main () 
{
    // CASO TEST I (DEL ENUNCIADO).
    int n = 9;
    int s = 21;
    int k = 12;

    auto inicio = chrono::high_resolution_clock::now();
    cout << "Distinguibles Fuerza Bruta da: " << distinguibles (n, s, k) << endl;
    auto fin = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duracion = fin - inicio;
    cout << "Caso distinguibles con fuerza bruta tardó " << duracion.count() << " ms en ejecutarse." << endl;

    auto inicio1 = chrono::high_resolution_clock::now();
    vector<vector<int>> M (n + 1, vector<int> (s + 1, - 1));
    cout << "Distinguibles topDown da: " << topDownD (M, n , s, k) << endl;
    auto fin1 = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duracion1 = fin1 - inicio1;
    cout << "Caso distinguibles con topDown tardó " << duracion1.count() << " ms en ejecutarse." << endl;

    auto inicio2 = chrono::high_resolution_clock::now();
    cout << "Indistinguibles Fuerza Bruta da: " << indistinguibles (n, s, k) << endl;
    auto fin2 = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duracion2 = fin2 - inicio2;
    cout << "Caso indistinguibles con fuerza bruta tardó " << duracion2.count() << " ms en ejecutarse." << endl;

    auto inicio3 = chrono::high_resolution_clock::now();
    vector<vector<vector<int>>> M1 (n + 1, vector<vector<int>> (s + 1, vector<int> (k + 1, -1)));
    cout << "Indistinguibles topDown da: " << topDownI (M1, n , s, k) << endl;
    auto fin3 = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duracion3 = fin3 - inicio3;
    cout << "Caso indistinguibles con topDown tardó " << duracion3.count() << " ms en ejecutarse." << endl;

    return 0;
}