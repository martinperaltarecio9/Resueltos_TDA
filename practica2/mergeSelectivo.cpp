#include<iostream>
#include<vector>
using namespace std;

// El desafío adicional queda sin hacer, lo que hice tarda O(log^2(n)).

int posEn (vector<int>& v, int elem) {
    int high = v.size() - 1;
    int low = 0;
    if (v[high] < elem) return high + 1;
    while (low < high) {
        int mid = (high + low) / 2;
        if (v[mid] < elem) low = mid + 1;
        else high = mid;
    }
    return low;
}

int i_esimo_merged (vector<int>& v, vector<int>& w, int i) {
    int high = v.size() - 1;
    int low = 0;
    int pos_mid;
    while (low < high) {
        int mid = (high + low) / 2;
        int pos_mid = mid + posEn (w, v[mid]);
        if (pos_mid + 1 < i) low = mid + 1;
        else high = mid;
    }
    if (posEn (w, v[low]) + low + 1 != i) return i_esimo_merged (w, v, i);
    return v[low];
}

int main ()
{
    // TEST 'posEn'.
    vector<int> v = {1, 3, 5};
    int elem = 6;
    // cout << posEn (v, elem) << endl;

    // TEST i-ésimo.
    vector<int> w = {2, 4, 6};
    // merge = {1, 2, 3, 4, 5, 6}
    cout << (i_esimo_merged (v, w, 1) == 1) << endl;
    cout << (i_esimo_merged (v, w, 2) == 2) << endl;
    cout << (i_esimo_merged (v, w, 3) == 3) << endl;
    cout << (i_esimo_merged (v, w, 4) == 4) << endl;
    cout << (i_esimo_merged (v, w, 5) == 5) << endl;
    cout << (i_esimo_merged (v, w, 6) == 6) << endl;

    return 0;
}