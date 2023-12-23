#include <bits/stdc++.h>
#define ll long long
#define ld long double
using namespace std;
vector<ld> Solve_Gauss(vector<vector<ld>>& A, vector<ld>& B) {
    for (ll i = 0; i < B.size() - 1; i++) {             // Прямой ход метода Гаусса
        if (A[i][i] == 0)
            for (ll j = i + 1; j < B.size(); j++)
                if (A[j][i] != 0) {
                    swap(A[i], A[j]);
                    swap(B[i], B[j]);
                    break;
                }
        for (ll j = i + 1; j < B.size(); j++) {
            ld m = A[j][i] / A[i][i];
            for (ll k = i; k < B.size(); k++)
                A[j][k] = A[j][k] - m * A[i][k];
            B[j] = B[j] - m * B[i];
        }
    }
    vector<ld> x(B.size());     // Обратный ход метода Гаусса
    for (ll i = B.size() - 1; i >= 0; i--) {
        ld s = 0;
        for (ll j = i + 1; j < B.size(); j++)
            s += A[i][j] * x[j];
        x[i] = (B[i] - s) / A[i][i];
    }
    return x;
}
vector<vector<ld>> Add_Matrix(vector<vector<ld>>& A, vector<vector<ld>>& B) {
    ll size = 5;
    vector<vector<ld>> result{
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0}
    };
    for (ll i = 0; i < size; i++)
        for (ll j = 0; j < size; j++)
            result[i][j] = 6 * A[i][j] + B[i][j];
    return result;
}
vector<ld> Solve_GaussStolb(vector<vector<ld>>& A, vector<ld>& B){        // По столбцу
    for (ll k = 0; k < A.size(); k++) {             // Прямой ход метода Гаусса
        ll maxRow = k;               // Поиск максимального элемента в k-ом столбце
        ld maxElement = abs(A[k][k]);
        for (ll i = k + 1; i < A.size(); i++)
            if (abs(A[i][k]) > maxElement) {
                maxElement = abs(A[i][k]);
                maxRow = i;
            }
        if (maxRow != k) {              // Перестановка строк, если найденный максимальный элемент не находится на диагонали
            swap(A[k], A[maxRow]);
            swap(B[k], B[maxRow]);
        }
        for (ll i = k + 1; i < A.size(); i++) {            // Приведение к треугольному виду
            ld coefficient = A[i][k] / A[k][k];
            for (ll j = k; j < A.size(); j++)
                A[i][j] -= coefficient * A[k][j];
            B[i] -= coefficient * B[k];
        }
    }
    vector<ld> x(A.size());             // Обратный ход метода Гаусса
    for (ll k = A.size() - 1; k >= 0; k--) {
        x[k] = B[k];
        for (ll i = k + 1; i < A.size(); i++)
            x[k] -= A[k][i] * x[i];
        x[k] /= A[k][k];
    }
    return x;
}
vector<ld> Solve_GaussALL(vector<vector<ld>>& A, vector<ld>& B) {       // По всей матрице
    for (ll i = 0; i < A.size(); i++) {             // Находим главный элемент для текущей строки
        ld maxElement = abs(A[i][i]);
        ll maxIndex = i;
        for (ll k = i + 1; k < A.size(); k++)
            if (abs(A[k][i]) > maxElement) {
                maxElement = abs(A[k][i]);
                maxIndex = k;
            }
        for (ll k = i; k < A.size(); k++)            // Меняем текущую строку с строкой, содержащей главный элемент
            swap(A[i][k], A[maxIndex][k]);
        swap(B[i], B[maxIndex]);
        for (ll j = i + 1; j < A.size(); j++) {                // Приводим матрицу к треугольному виду
            ld ratio = A[j][i] / A[i][i];
            for (ll k = i; k < A.size(); k++)
                A[j][k] -= ratio * A[i][k];
            B[j] -= ratio * B[i];
        }
    }
    vector<ld> x(A.size());            // Обратный ход метода Гаусса
    for (ll i = A.size() - 1; i >= 0; i--) {
        x[i] = B[i];
        for (ll j = i + 1; j < A.size(); j++)
            x[i] -= A[i][j] * x[j];
        x[i] /= A[i][i];
    }
    return x;
}
void Print_matrix(vector<ld> A)
{
    for (ld value : A)
        cout << fixed << setprecision(5) << value << " ";
    cout << "\n";
}
int main() {
    vector<vector<ld>> C = {
            {0.2, 0, 0.2, 0, 0.0},
            {0, 0.2, 0, 0.2, 0},
            {0.2, 0, 0.2, 0, 0.2},
            {0, 0.2, 0, 0.2, 0},
            {0, 0, 0.2, 0, 0.2}
    };

    vector<vector<ld>> D = {
            {2.33, 0.81, 0.67, 0.92, -0.53},
            {-0.53, 2.33, 0.81, 0.67, 0.92},
            {0.92, -0.53, 2.33, 0.81, 0.67},
            {0.67, 0.92, -0.53, 2.33, 0.81},
            {0.81, 0.67, 0.92, -0.53, 2.33}
    };

    vector<vector<ld>> A = Add_Matrix(D, C);
    vector<ld> b = { 4.2001,4.2001,4.2001,4.2001,4.2001 };
    cout << "Solve 1: " << endl;
    Print_matrix(Solve_Gauss(A, b));
    Print_matrix(Solve_GaussStolb(A, b));
    Print_matrix(Solve_GaussALL(A, b));
}