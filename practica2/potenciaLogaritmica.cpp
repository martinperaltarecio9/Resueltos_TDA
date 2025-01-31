#include<iostream>
#include<cmath>
using namespace std;

int potencia (int a, int b) {
    if (b == 0) return 1;
    int mitad = b / 2;
    int aux = potencia (a, mitad);
    if (b % 2 == 0) return (aux * aux);
    else return (aux * aux * a);
}

int main ()
{
    // TESTS
    int a = 3;
    int b = 7;
    cout << (potencia (a, b) == pow (a, b)) << endl;
    int a1 = 19;
    int b1 = 2;
    cout << (potencia (a1, b1) == pow (a1, b1)) << endl;

    return 0;
}