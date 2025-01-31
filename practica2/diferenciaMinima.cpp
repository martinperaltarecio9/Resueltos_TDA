#include<iostream>
#include<vector>
using namespace std;

int dif (vector<int>& A, vector<int>& B, int i) {return abs (A[i] - B[i]);}

int min_dif (vector<int>& A, vector<int>& B) {
    int high = A.size() - 1;
    int low = 0;
    while (low < high) {
        int mid = (high + low) / 2;
        if (dif (A, B, mid) > dif (A, B, mid + 1)) {
            low = mid + 1;
        } else if (dif (A, B, mid) > dif (A, B, mid - 1)) {
            high = mid;
        } else {
            low = mid;
            break;
        }
    }
    return dif (A, B, low);
}

int main ()
{
    // TEST ENUNCIADO
    vector<int> A = {1, 2, 3, 4};
    vector<int> B = {6, 4, 2, 1};
    cout << (min_dif (A, B) == 1) << endl;

    // TESTS PROPIOS
    vector<int> A1 = {1, 2, 5, 99};
    vector<int> B1 = {102, 101, 100, 99};
    cout << (min_dif (A1, B1) == 0) << endl;
    
    vector<int> A2 = {17, 18, 19, 20};
    vector<int> B2 = {15, 14, 13, 11};
    cout << (min_dif (A2, B2) == 2) << endl;

    vector<int> A3 = {1, 2, 3, 4, 11, 13};
    vector<int> B3 = {10, 9, 8, 7, 2, 1};
    cout << (min_dif (A3, B3) == 3) << endl;

    return 0;
}