#include<iostream>
#include<vector>
#include<tuple>
using namespace std;

vector<vector<int>> transpose (const vector<vector<int>>& matrix) {
    if (matrix.empty()) return {};
    size_t rows = matrix.size();
    size_t cols = matrix[0].size();
    vector<vector<int>> result (cols, vector<int>(rows));
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            result[j][i] = matrix[i][j];
        }
    }
    return result;
}

int llenarCasillero (int minVida_imas1_j, int minVida_i_jmas1, int elem_i_j, int numOperacion) {
    // Caso general.
    if (numOperacion == 0) {
        if (min (minVida_i_jmas1, minVida_imas1_j) - elem_i_j <= 0) return 1;
        else return min (minVida_i_jmas1, minVida_imas1_j) - elem_i_j;
    } 
    // Si estoy en la última columna.
    if (numOperacion == 1) {
        if (minVida_imas1_j - elem_i_j <= 0) return 1;
        else return minVida_imas1_j - elem_i_j;
    }
    // Si estoy en la última fila.
    if (numOperacion == 2) {
        if (minVida_i_jmas1 - elem_i_j <= 0) return 1;
        else return minVida_i_jmas1 - elem_i_j;
    }
    // Si estoy en la última columna y la última fila.
    if (numOperacion == 3) {
        if (elem_i_j < 0) return (1 + abs (elem_i_j));
        else return 1;
    }
    return 0;
}

// Para matrices con mayor cantidad de filas que de columnas.
// Si pasara lo opuesto, se puede trasponer y da lo mismo.
int bottom_up (const vector<vector<int>>& A, vector<int>& v, vector<int>& w, int fila, int desdeFila) {
    // Si es la última iteración.
    if (fila == -1) return v[0];
   
    // Si necesito calcular más de la última columna.
    if (fila < desdeFila) {
        int aux = w.size();      // lo cual también es igual a la cantidad de columnas de A.
        int nuevoDesdeFila = max (0, desdeFila - aux);
        int nuevoUltIndice = w.size() - 1 + min (0, desdeFila - aux);
        if (fila == A.size() - 1) w[nuevoUltIndice] = llenarCasillero (0, 0, A[fila][aux - 1], 3);
        else w[nuevoUltIndice] = llenarCasillero (w[0], 0, A[fila][aux - 1], 1);
        for (int i = nuevoUltIndice - 1; i >= 0; i --) {
            w[i] = llenarCasillero (w[i + 1], 0, A[nuevoDesdeFila + i][aux - 1], 1);
        }
        return bottom_up (A, v, w, fila, nuevoDesdeFila);
    }

    // Estoy en la última fila.
    if (fila == A.size() - 1) {
        v[v.size() - 1] = w[w.size() - 1];
        for (int j = v.size() - 2; j >= 0; j --) v[j] = llenarCasillero (0, v[j + 1], A[fila][j], 2);
        return bottom_up (A, v, w, fila - 1, desdeFila);
    }

    // Caso general.
    v[v.size() - 1] = w[fila - desdeFila];
    for (int j = v.size() - 2; j >= 0; j --) v[j] = llenarCasillero (v[j], v[j + 1], A[fila][j], 0);
    return bottom_up (A, v, w, fila - 1, desdeFila);
}

int call_bottom_up (const vector<vector<int>>& A) {
    int num_col = (A[0]).size();
    int num_fil = A.size();
    if (num_col > num_fil) {
        vector<vector<int>> B = transpose (A);
        vector<int> v (num_fil, 0);
        vector<int> w (num_fil, 0);
        int fila = num_col - 1;
        int desdeFila = num_col;
        return bottom_up (B, v, w, fila, desdeFila);
    }
    vector<int> v (num_col, 0);
    vector<int> w (num_col, 0);
    int fila = num_fil - 1;
    int desdeFila = num_fil;
    return bottom_up (A, v, w, fila, desdeFila);
}

int main ()
{
    vector<vector<int>> A = {{-2, -3, 3}, {-5, -10, 1}, {10, 30, -5}, {1, 1, 1}};
    vector<vector<int>> B = {{1, -5, 70}, {1, 1, 1}, {-100, 1, -70}};
    vector<vector<int>> C = {{-2, -5, 10, 1}, {-3, -10, 30, 1}, {3, -5, -5, 1}};

    cout << (call_bottom_up (A) == 7) << endl;
    cout << (call_bottom_up (B) == 5) << endl;
    cout << (call_bottom_up (C) == 8) << endl;
    
    return 0;
}