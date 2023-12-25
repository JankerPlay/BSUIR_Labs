#include <iostream>
using namespace std;
int main() {
    long double x, y;
    bool i;
    cin >> x >> y;
    i = x > y;
    cout << (i ? x : y);
    return 0;
}