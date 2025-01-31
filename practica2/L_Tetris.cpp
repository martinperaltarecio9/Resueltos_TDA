#include<iostream>
#include<vector>
using namespace std;

// Cada subproblema se va a dividir con los siguientes datos:
// desdeF, hastaF, desdeC, hastaC el cuadrante que tengo que llenar y
// i0, j0 la posición fija que no puedo cambiar.
// Luego, el caso base va a ser cuando llegue a un cuadrado de 2x2.

void llenar_2x2 (vector<vector<int>>& A, int i0, int j0, int desdeF, int desdeC, int& cantLs) {
    int l = cantLs + 1;
    for (int i = desdeF; i <= desdeF + 1; i ++) {
        for (int j = desdeC; j <= desdeC + 1; j++) {
            if ((i != i0) || (j != j0)) A[i][j] = l;
        }
    }
    return;
}

int obtener_cuadrante (int i0, int j0, int fila_centro, int col_centro) {
    int cuadrante;
    if ((i0 <= fila_centro) && (j0 <= col_centro)) {
        cuadrante = 1;
    } else if ((i0 <= fila_centro) && (j0 > col_centro)) {
        cuadrante = 2;
    } else if ((i0 > fila_centro) && (j0 <= col_centro)) {
        cuadrante = 3;
    } else {
        cuadrante = 4;
    }
    return cuadrante;
}

int obtener_desdeF (int cuadrante, int desdeF, int fila_centro) {
    if ((cuadrante == 1) || (cuadrante == 2)) return desdeF;
    else return fila_centro + 1;
}

int obtener_desdeC (int cuadrante, int desdeC, int col_centro) {
    if ((cuadrante == 1) || (cuadrante == 3)) return desdeC;
    else return col_centro + 1;
}

void L_Tetris (vector<vector<int>>& A, int i0, int j0, int tam, int desdeF, int desdeC, int& cantLs) {
    // Caso base.
    if (tam == 2) {
        llenar_2x2 (A, i0, j0, desdeF, desdeC, cantLs);
        cantLs ++;
        return;
    }
    // Caso recursivo.
    int nuevo_tam = tam / 2;
    int fila_centro = desdeF + nuevo_tam - 1;
    int col_centro = desdeC + nuevo_tam - 1;
    // cout << fila_centro << " " << col_centro << endl;
    int cuadrante = obtener_cuadrante (i0, j0, fila_centro, col_centro);

    int l = cantLs + 1;
    cantLs ++;

    for (int i = fila_centro; i <= fila_centro + 1; i ++) {
        for (int j = col_centro; j <= col_centro + 1; j ++) {
            int otro_cuadrante = obtener_cuadrante (i, j, fila_centro, col_centro);
            if (otro_cuadrante != cuadrante) {
                A[i][j] = l;
                int nuevo_desdeF = obtener_desdeF (otro_cuadrante, desdeF, fila_centro);
                int nuevo_desdeC = obtener_desdeC (otro_cuadrante, desdeC, col_centro);
                L_Tetris (A, i, j, nuevo_tam, nuevo_desdeF, nuevo_desdeC, cantLs);
            }
        }
    }

    int nuevo_desdeF = obtener_desdeF (cuadrante, desdeF, fila_centro);
    int nuevo_desdeC = obtener_desdeC (cuadrante, desdeC, col_centro);
    L_Tetris (A, i0, j0, nuevo_tam, nuevo_desdeF, nuevo_desdeC, cantLs);

    return;
}

void call_L_Tetris (int n, int pos_i, int pos_j) {
    vector<vector<int>> A (n, vector<int> (n, -1));
    A[pos_i][pos_j] = 0;
    int cantLs = 0;
    L_Tetris (A, pos_i, pos_j, n, 0, 0, cantLs);
    for (int i = 0; i < n; i ++) {
        for (int j = 0; j < n; j ++) cout << A[i][j] << " ";
        cout << endl;
    }
    return;
}

int main ()
{
    // TESTS
    cout << "------------ CASO 4x4 ------------" << endl;
    int n = 4;
    call_L_Tetris (n, 2, 3);
    cout << "------------ CASO 8x8 ------------" << endl;
    n += 4;
    call_L_Tetris (n, 5, 6);

    return 0;
}