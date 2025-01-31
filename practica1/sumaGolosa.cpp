#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int sumaGolosa (vector<int>& v) {
    sort (v.begin(), v.end());
    int costo = v[0] + v[1];
    int suma = costo;
    for (int i = 2; i < v.size(); i ++) {
        costo += v[i];
        suma += costo;
    }
    return suma;
}

int main () 
{
    vector<int> v = {1, 2, 7, 1, 1, 5};
    cout << (sumaGolosa (v) == 37) << endl;
    return 0;
}