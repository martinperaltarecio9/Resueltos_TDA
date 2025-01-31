#include<iostream>
#include<vector>
using namespace std;

int maxParejas (vector<int>& v, vector<int>& u) {
    if (v.size() > u.size()) return maxParejas (u, v);
    int res = 0;
    int j0 = 0;
    for (int i = 0; i < v.size(); i ++) {
        for (int j = j0; j < u.size(); j ++) {
            if (abs (v[i] - u[j]) <= 1) {
                res ++;
                j0 = j + 1;
                break;
            } else if (u[j] - v[i] > 1) {
                j0 = j;
                break;
            } else if (j == u.size() - 1) {
                return res;
            }
        }
        if (j0 == u.size()) break;
    }
    return res;
}

int main () 
{
    vector<int> v1 = {1, 2, 4, 6};
    vector<int> u1 = {1, 5, 5, 7, 9};
    cout << (maxParejas (v1, u1) == 3) << endl;
    vector<int> v2 = {1, 1, 1, 1, 1};
    vector<int> u2 = {1, 2, 3};
    cout << (maxParejas (v2, u2) == 2) << endl;

    return 0;
}