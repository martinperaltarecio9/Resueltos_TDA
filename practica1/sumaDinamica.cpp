#include<iostream>
#include<vector>
using namespace std;

// Usando una estrategia bottom-up.
bool subset_sum (vector<int>& C, vector<bool>& v1, vector<bool>& v2, int exchange) {
    if (exchange == C.size()) return (v1[v1.size() - 1]);
    for (int j = 0; j < v2.size(); j ++) {
        if (j - C[exchange] >= 0) v2[j] = (v1[j]) || (v1[j - C[exchange]]);
        else v2[j] = v1[j];
    }
    return subset_sum (C, v2, v1, exchange + 1);
}

bool call_subset_sum (vector<int>& C, int k) {
    vector<bool> v1 (k + 1, false);
    vector<bool> v2 (k + 1, false);
    v1[0] = true;
    int exchange = 0;
    return subset_sum (C, v1, v2, exchange);
}

int main () 
{
    // TEST
    vector<int> C = {3, 4, 51, 2, 4, 1, 2, 89};

    cout << (call_subset_sum (C, 93) == true) << endl;
    cout << (call_subset_sum (C, 45) == false) << endl;
    cout << (call_subset_sum (C, 15) == true) << endl;
    cout << (call_subset_sum (C, 52) == true) << endl;
    cout << (call_subset_sum (C, 17) == false) << endl;

    return 0;
}