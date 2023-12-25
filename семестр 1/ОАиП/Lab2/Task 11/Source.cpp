#include <iostream>
#include <cmath>
using namespace std;
int main() {
    long double R, P, Q;
    setlocale(LC_ALL, "russian");
    cin >> R >> P >> Q;
    if (R <= P * sin(Q) / 2)
        cout << "Сможет";
    else 
        cout << "Не сможет";
    return 0;
}