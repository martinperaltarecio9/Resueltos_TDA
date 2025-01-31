#include<iostream>
#include<vector>
#include<algorithm>
#include<tuple>
using namespace std;

// tengo que hacer un override/overload de varias operaciones del tipo 'tuple<int,int>'

bool operator< (const tuple<int, int>& t1, const tuple<int, int>& t2) {
    if (get<0>(t1) != get<0>(t2)) {
        return get<0>(t1) < get<0>(t2);
    }
    return get<1>(t1) < get<1>(t2);
}
tuple<int, int> operator+ (const tuple<int, int>& t1, const tuple<int, int>& t2) {
    return make_tuple(get<0>(t1) + get<0>(t2), get<1>(t1) + get<1>(t2));
}
ostream& operator<< (ostream& os, const tuple<int, int>& t) {
    os << "(" << get<0>(t) << ", " << get<1>(t) << ")";
    return os;
}

tuple<int,int> bottom_up (const vector<int>& B, const vector<int>& sumaHasta, vector<tuple<int,int>>& v1, vector<tuple<int,int>>& v2, int exchange) {
    if (exchange == B.size()) return v1[v1.size() - 1];
    int k = v2.size();
    for (int j = 0; j < min (sumaHasta[exchange], k); j ++) {
        tuple<int,int> nuevaTupla = make_tuple (B[exchange], 1);
        // O sea, si no me paso cuando considero el billete.
        if (j - B[exchange] >= 0) { 
            v2[j] = min (v1[j - B[exchange]] + nuevaTupla, v1[j]); // que sería el mínimo entre 'poner' el billete y no 'ponerlo'.
        } else { // Si me paso cuando considero el billete.
            v2[j] = min (nuevaTupla, v1[j]);
        }
    }
    return bottom_up (B, sumaHasta, v2, v1, exchange + 1);
}

tuple<int,int> call_bottom_up (const vector<int>& B, int C) {
    int inf_pos = 1000000;
    vector<int> sumaHasta (B.size(), 0);
    int aux = 0;
    for (int j = 0; j < B.size(); j ++) {
        aux += B[j];
        sumaHasta[j] = aux;
    }
    vector<tuple<int,int>> v1 (C + 1, make_tuple (inf_pos, inf_pos));
    vector<tuple<int,int>> v2 (C + 1, make_tuple (inf_pos, inf_pos));
    v1[0] = make_tuple (0, 0);
    int exchange = 0;
    return (bottom_up (B, sumaHasta, v1, v2, exchange));
}

int main () 
{
    vector<int> B = {2, 3, 5, 10, 20, 20};

    cout << (call_bottom_up (B, 14) == make_tuple (15, 2)) << endl;
    cout << (call_bottom_up (B, 40) == make_tuple (40, 2)) << endl;
    cout << (call_bottom_up (B, 11) == make_tuple (12, 2)) << endl;

    return 0;
}