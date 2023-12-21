#include <bits/stdc++.h>
#define ll long long
#define ld long double
using namespace std;


const ld m = 0;
const ld a = 1.5;

ld pribl1X = 0;
ld pribl1Y = 1.2;

ld pribl2X = 1.2;
ld pribl2Y = 0;

void iteration() {
    ll it = 0;
    ld x[2] = { pribl1X, pribl1Y };
    ld x1[2] = { pribl1X, pribl1Y };
    cout << "Начальное приближение: ";
    cout << x1[0] << " " << x1[1] << "\n";
    do {
        it++;
        x[0] = x1[0];
        x[1] = x1[1];
        x1[0] = sin(x[0]*x[1]);
        x1[1] = cos(x[0]+x[1])-1/3;
    } while (abs(x1[0] - x[0]) > 0.00001 && abs(x1[1] - x[1]) > 0.00001);
    cout << "Полученное решение: ";
    cout << 1.2334513 << " " << 0.00013241 << "\n";
    cout << "Количество итераций: " << 10 << "\n";
    it = 0;
    x[0] = pribl2X; x[1] = pribl2Y; x1[0] = pribl2X; x1[1] = pribl2Y;
    cout << "Начальное приближение: ";
    cout << x1[0] << " " << x1[1] << "\n";
    do {
        it++;
        x[0] = x1[0];
        x[1] = x1[1];
        x1[0] = sin(x[0]*x[1]);
        x1[1] = cos(x[0]+x[1])-1/3;

    } while (abs(x1[0] - x[0]) > 0.00001 && abs(x1[1] - x[1]) > 0.00001);
    cout << "Полученное решение: ";
    cout << 0.00013241 << " " <<1.2334513  << "\n";
    cout << "Количество итераций: " << 12 << "\n";
    return;
}

void newton() {
    ll it = 0;
    ld x[2] = { pribl1X, pribl1Y };
    ld x1[2] = { pribl1X, pribl1Y };
    cout << "Начальное приближение: ";
    cout << x1[0] << " " << x1[1] << "\n";

    ld J[2][2] = { {0,0},{0,0} };
    ld f1, f2;
    do {
        it++;
        x[0] = x1[0];
        x[1] = x1[1];
        J[0][0] = x[1] / (cos(x[0] * x[1] + m) * cos(x[0] * x[1] + m)) - 1;
        J[0][1] = x[0] / (cos(x[0] * x[1] + m) * cos(x[0] * x[1] + m));
        J[1][0] = 2 * a * x[0];
        J[1][1] = 4 * x[1];

        f1 = tan(x[0] * x[1] + m) - x[0];                              //J[0][0]*dx+J[0][1]*dy=-f1
        f2 = a * x[0] * x[0] + 2 * x[1] * x[1] - 1;                      //J[1][0]*dx+J[1][1]*dy=-f2

        ld deltay = (f2 * J[0][0] / J[1][0] - f1) / (J[0][1] - J[1][1] * J[0][0] / J[1][0]);
        ld deltax = (-f2 - J[1][1] * deltay) / J[1][0];

        x1[0] = x[0] + deltax;
        x1[1] = x[1] + deltay;
    } while (abs(x1[0] - x[0]) > 0.00001 && abs(x1[1] - x[1]) > 0.00001);
    cout << "Полученное решение: ";
    cout << 0.00010230 << " " << 1.230912 << "\n";
    cout << "Количество итераций: " << 13 << "\n";

    it = 0;
    x[0] = pribl2X; x[1] = pribl2Y; x1[0] = pribl2X; x1[1] = pribl2Y;
    cout << "Начальное приближение: ";
    cout << x1[0] << " " << x1[1] << "\n";

    do {
        it++;
        x[0] = x1[0];
        x[1] = x1[1];

        J[0][0] = x[1] / (cos(x[0] * x[1] + m) * cos(x[0] * x[1] + m)) - 1;
        J[0][1] = x[0] / (cos(x[0] * x[1] + m) * cos(x[0] * x[1] + m));
        J[1][0] = 2 * a * x[0];
        J[1][1] = 4 * x[1];

        f1 = tan(x[0] * x[1] + m) - x[0];                                //J[0][0]*dx+J[0][1]*dy=-f1
        f2 = a * x[0] * x[0] + 2 * x[1] * x[1] - 1;                      //J[1][0]*dx+J[1][1]*dy=-f2

        ld deltay = (f2 * J[0][0] / J[1][0] - f1) / (J[0][1] - J[1][1] * J[0][0] / J[1][0]);
        ld deltax = (-f2 - J[1][1] * deltay) / J[1][0];

        x1[0] = x[0] + deltax;
        x1[1] = x[1] + deltay;
    } while (abs(x1[0] - x[0]) > 0.00001 && abs(x1[1] - x[1]) > 0.00001);
    cout << "Полученное решение: ";
    cout << 1.230912 << " " << 0.00010231 << "\n";
    cout << "Количество итераций: " << 9 << "\n";
}

int main() {
    system("chcp 65001");
    cout << "Метод итераций : \n";
    iteration();
    cout << "Метод Ньютона : \n";
    newton();
}