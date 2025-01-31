#include <iostream>
#include <vector>
#include <climits>
using namespace std;

void lower (vector<int>& v, int pos) {
    // Caso sin hijos.
    if (2*pos + 1 >= v.size()) return;
    // Caso solo tiene hijo izquierdo.
    if (2*pos + 2 >= v.size()) {
        if (v[pos] < v[2*pos + 1]) {
            swap (v[pos], v[2*pos + 1]);
            return lower (v, 2*pos + 1);
        }
        return;
    }
    // Caso tiene dos hijos.
    if (v[pos] < max (v[2*pos + 1], v[2*pos + 2])) {
        if (v[2*pos + 1] < v[2*pos + 2]) {
            swap (v[pos], v[2*pos + 2]);
            return lower (v, 2*pos + 2);
        }
        swap (v[pos], v[2*pos + 1]);
        return lower (v, 2*pos + 1);
    }
    return;
}

void maxHeap (vector<int>& v) {
    for (int i = v.size()/2 + 1; i >= 0; i --) {
        lower (v, i);
    }
}

int sumaSelectiva (vector<int>& v, int k) {
    // Si quisiera O(nlogn) podría ordenar y agarrar a los 'k' más grandes.
    // Voy a hacer directo O(nlogk).
    maxHeap(v); // tarda O (n)
    int suma = 0;
    for (int i = 1; i <= k; i ++) {
        suma += v[0];
        v[0] = INT_MIN;
        lower (v, 0);
    }
    return suma;
}

int main () 
{
    vector<int> v = {1, 2, 4, 33, 41, 23, -1, -34, 5, 2};
    int k = 4;
    cout << (sumaSelectiva (v, k) == 102) << endl;
    return 0;
}