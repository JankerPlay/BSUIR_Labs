#include <iostream>
#include <cmath>
using namespace std;
int main() {
    setlocale(LC_ALL, "russian");
    long double x1, y1, r, x2, y2, R, X, Y, Z;
    cin >> x1 >> y1 >> r >> x2 >> y2 >> R;
    X = fabs(x1 - x2);
    Y = fabs(y1 - y2);
    Z = sqrt(X * X + Y * Y);
    if (R > r + Z)
        cout << "Да";
    else if (r > R + Z)
    cout << "Да, но справедливо обратное для двух фигур";
    else if (r + R >= Z)
    cout << "Фигуры пересекаются";
    else
    cout << "Ни одно условие не выполнено";
    return 0;
}