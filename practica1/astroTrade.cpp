#include<iostream>
#include<vector>
using namespace std;

int bottom_up (const vector<int>& P, vector<int>& v1, vector<int>& v2, int exchange) {
    // Para entender lo que está haciendo (como quedaría la "matriz"):
    //for (int i = 0; i < v1.size(); i ++)
    //cout << v1[i] << " ";
    //cout << endl;
    if (exchange == P.size() - 1) return v1[0];
    for (int j = 0; j < v2.size(); j ++) {
        if (j == 0) v2[j] = max (v1[j], v1[j + 1] + P[exchange + 1]);
        else if (j == v2.size() - 1) v2[j] = max (v1[j], v1[j - 1] - P[exchange + 1]);
        else v2[j] = max (v1[j], max (v1[j + 1] + P[exchange + 1], v1[j - 1] - P[exchange + 1]));
    }
    return bottom_up (P, v2, v1, exchange + 1);
}

int call_bottom_up (const vector<int>& P) {
    int inf_neg = - 1000000;
    vector<int> v1 (P.size(), inf_neg);
    vector<int> v2 (P.size(), inf_neg);
    v1[0] = 0;
    v1[1] = - P[0];
    int exchange = 0;
    return (bottom_up (P, v1, v2, 0));
}

int main () 
{
    vector<int> P = {3, 2, 5, 6};
    cout << (call_bottom_up (P) == 6) << endl;

    vector<int> P_1 = {3, 6, 10};
    cout << (call_bottom_up (P_1) == 7) << endl;

    vector<int> P_2 = {2, 3, 5, 6, 1, 17, 10};
    cout << (call_bottom_up (P_2) == 27) << endl;

    return 0;
}