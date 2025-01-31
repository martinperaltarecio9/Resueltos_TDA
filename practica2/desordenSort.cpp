#include<iostream>
#include<vector>
#include<list>
using namespace std;

int cantParejas0n2 (vector<int>& v) {
    int res = 0;
    for (int i = 0; i < v.size(); i ++) {
        for (int j = i + 1; j < v.size(); j ++) {
            if (v[i] > v[j]) res ++;
        }
    }
    return res;
}

// Mergear dos subarreglos del tipo v[desde ... medio], v[medio+1 ... hasta].
int merge (vector<int>& v, int desde, int medio, int hasta) {
    int res = 0;
    int n = medio - desde + 1;
    int m = hasta - medio;
    // Creo dos copias.
    vector<int> x (n);
    vector<int> y (m);
    for (int i = desde; i <= medio; i ++) x[i - desde] = v[i];
    for (int i = medio + 1; i <= hasta; i ++) y[i - medio - 1] = v[i];
    // Hago el merge.
    int i = 0;
    int j = 0;
    int k = 0;
    while ((i < n) && (j < m)) {
        if (x[i] > y[j]) {
            res += n - i;
            v[desde + k] = y[j];
            j ++;
        } else {
            v[desde + k] = x[i];
            i ++;
        }
        k ++;
    }
    while (i < n) {
        v[desde + k] = x[i];
        i ++;
        k ++;
    }
    while (j < m) {
        v[desde + k] = y[j];
        j ++;
        k ++;
    }
    return res;
}

int mergeSortMod (vector<int>& v, int desde, int hasta) {
    if (desde >= hasta) return 0;
    if (desde == hasta - 1) {
        int aux;
        if (v[desde] > v[hasta]) {
            aux = v[desde];
            v[desde] = v[hasta];
            v[hasta] = aux;
            return 1;
        }
        return 0;
    }
    int medio = (hasta + desde) / 2;
    int cantParejas = 0;
    cantParejas += mergeSortMod(v, desde, medio);
    cantParejas += mergeSortMod(v, medio + 1, hasta);
    cantParejas += merge(v, desde, medio, hasta);
    return cantParejas;
}

int main ()
{
    vector<int> w = {4, 13, 11, 2, 3, 7, 8, 6, 1};
    vector<int> w_copy = {4, 13, 11, 2, 3, 7, 8, 6, 1};
    cout << (mergeSortMod (w, 0, w.size() - 1) == cantParejas0n2 (w_copy)) << endl;

    return 0;
}