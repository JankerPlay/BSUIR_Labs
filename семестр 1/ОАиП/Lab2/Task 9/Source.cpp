#include <iostream>
#include <cmath>
using namespace std;
int main() {
    setlocale(LC_ALL, "russian");        // 10 вариант
    long double d, f, x, c, e, y;
    int a;
    cout << "Выберить f(x) 2x, x^3, x/3\n";
    cin >> a;
    cout << "Введите d, e, c и x\n";
    cin >> d >> e >> c >> x;

     switch (a)
    {
    case 1:
    {
        f = 2*x;
        cout << "f(x)=2x\n";
        break;
    }
    case 2:
    {
        f = x * x * x;
        cout << "f(x)=x^3\n";
        break;
    }
    case 3:
    {
        f = x / 3;
        cout << "f(x)=x/3\n";
        break;
        }
    }
     y = (d * f * pow(e, sin(x) * sin(x) * sin(x)) + c * log(x + 1)) / sqrt(x);
     cout << y;








    return 0;
}