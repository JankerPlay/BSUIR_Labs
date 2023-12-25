#include <iostream>
using namespace std;
int main() {
    long double a, b, c, Y, N;
    int d;
    cin >> a >> b >> c >> N;
    if (N == 2)
        d = 1;
    else if (N == 56)
        d = 2;
    else if (N == 7)
        d = 3;
    else if (N == 3)
        d = 4;
    else
        d = 5;
    switch (d)
    {
    case 1:
        cout << b * c - a * a;
        break;
    case 2:
        cout << b * c;
        break;
    case 3:
        cout << a * a + c;
        break;
    case 4:
        cout << a - b * c;
        break;
    case 5:
        cout << (a + b) * (a + b) * (a + b);
        break;
    }
     return 0;
}