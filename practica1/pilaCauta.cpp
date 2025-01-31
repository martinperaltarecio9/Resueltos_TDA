#include<iostream>
#include<vector>
#include<random>
using namespace std;

int backtracking (const vector<int>& w, const vector<int>& s, int soporteActual, int pos) {
    // Si llegue al final.
    if (pos == w.size()) return 0;
    // Si puedo apilar.
    if (w[pos] <= soporteActual) {
        int nuevoSoporte = min (soporteActual - w[pos], s[pos]);
        int apilo = 1 + backtracking (w, s, nuevoSoporte, pos + 1);
        int noApilo = backtracking (w, s, soporteActual, pos + 1);
        return max (apilo, noApilo);
    }
    // Si no puedo apilar.
    return backtracking (w, s, soporteActual, pos + 1);
}

int call_backtracking (const vector<int>& w, const vector<int>& s) { return backtracking (w, s, 1000000, 0); }

int bottom_up (const vector<int>& w, const vector<int>& s, vector<int>& v1, vector<int>& v2, int exchange) {
    int n = w.size();
    // Primera iteración.
    if (exchange == 0) {
        v1[0] = w[n - 1];
        return bottom_up (w, s, v1, v2, exchange + 1);
    }
    // Última iteración.
    if (exchange == n) {
        int res = 1;
        for (int i = v1.size() - 1; i >=0; i --) {
            if (v1[i] != 1000000) {
                res = i + 1;
                break;
            }
        }
        return res;
    }
    // Caso general.
    v2[0] = min (v1[0], w[n - 1 - exchange]);
    for (int i = 1; i <= exchange; i ++) {
        // ¿Puedo apilar?
        if (v1[i - 1] <= s[n - 1 - exchange]) {
            v2[i] = min (v1[i - 1] + w[n - 1 - exchange], v1[i]);
        } else v2[i] = v1[i];
    }
    return bottom_up (w, s, v2, v1, exchange + 1);
}

int call_bottom_up (const vector<int>& w, const vector<int>& s) {
    int n = w.size();
    int inf = 1000000;
    vector<int> v1 (n, inf);
    vector<int> v2 (n, inf);
    return bottom_up (w, s, v1, v2, 0);
}

void generar_vector_aleatorio (vector<int>& x) {
    int lower = 1;
    int upper = 20;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib (lower, upper);
    for (int i = 0; i < x.size(); i ++) x[i] = distrib(gen);
    return;
}

int main ()
{
    // TESTS MANUALES
    vector<int> w = {12, 7, 5, 8, 13};
    vector<int> s = {12, 12, 5, 17, 10};
    cout << " ------- TESTS MANUALES ------- " << endl;
    cout << "Bottom Up = " << call_bottom_up (w, s) << ". Backtracking = " << call_backtracking (w, s) << "." << endl;
    // TEST PROPIO
    vector<int> w1 = {10, 9, 8, 7};
    vector<int> s1 = {24, 15, 7, 1};
    cout << "Bottom Up = " << call_bottom_up (w1, s1) << ". Backtracking = " << call_backtracking (w1, s1) << "." << endl;
    // Como todavía no estoy seguro, voy a hacer tests aleatorios.
    cout << " -------- TESTS ALEATORIOS -------- " << endl; 
    int cantTests = 30;
    vector<int> x (5);
    vector<int> y (5);
    int pasaCant = 0;
    for (int i = 1; i <= cantTests; i ++) {
        generar_vector_aleatorio (x);
        generar_vector_aleatorio (y);
        if (call_backtracking (x, y) != call_bottom_up (x, y)) {
            cout << "Falla para : x = ";
            for (int i = 0; i < x.size(); i ++) cout << x[i] << " ";
            cout << "e y = ";
            for (int i = 0; i < y.size(); i ++) cout << y[i] << " ";
            cout << endl;
            cout << "Bottom Up = " << call_bottom_up (x, y) << ". Backtracking = " << call_backtracking (x, y) << "." << endl;
        } else {
            pasaCant ++;
        }
    }
    cout << "PASÓ " << pasaCant << " TESTS ALEATORIOS." << endl;

    return 0;
}