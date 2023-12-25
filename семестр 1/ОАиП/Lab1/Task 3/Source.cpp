#include <iostream>
int main() {
    using namespace std;
    float a, t, v0, x;
    cout << "t = ";
    cin >> t;
    cout << "a = ";
    cin >> a;
    cout << "v0 = ";
    cin >> v0;
    x = (v0 * t) + a * t * t / 2;
      std::cout << "x = " << x;
    return 0;
}