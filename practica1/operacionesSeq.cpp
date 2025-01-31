#include<iostream>
#include<vector>
#include<cmath>
using namespace std;

// Esta estrategia resuelve la superposición de problemas.
// No mejora la complejidad temporal de peor caso.

void insertar (vector<bool>& x, int val) {
    if (val >= x.size()) return;
    x[val] = true;
    return;
}

bool bottom_up (const vector<int>& v, vector<bool>& v1, vector<bool>& v2, int exchange) {
    if (exchange == v.size() - 1) return (v1[v1.size() - 1]);
    for (int i = 0; i < v1.size(); i ++) {
        if (v1[i] == true) {
            v1[i] = false;
            insertar (v2, i + v[exchange + 1]);
            insertar (v2, i * v[exchange + 1]);
            insertar (v2, pow (i, v[exchange + 1]));
        }
    }
    exchange ++;
    return bottom_up (v, v2, v1, exchange);
}

bool call_bottom_up (const vector<int>& v, int w) {
    vector<bool> v1 (w + 1, false);
    vector<bool> v2 (w + 1, false);
    v1[v[0]] = true;
    int exchange = 0;
    return (bottom_up (v, v1, v2, exchange));
}

int main ()
{
    vector<int> v = {3, 1, 5, 2, 1};
    cout << (call_bottom_up (v, 12) == true) << endl;
    cout << (call_bottom_up (v, 400) == true) << endl;
    cout << (call_bottom_up (v, 401) == true) << endl;
    cout << (call_bottom_up (v, 4) == false) << endl;
    cout << (call_bottom_up (v, 21) == false) << endl;

    return 0;
}