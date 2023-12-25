#include <iostream>
#include <cmath>
int main() {
    using namespace std;
    float b1, q, n, S;
    cout << "b1 = ";
    cin >> b1;
    cout << "n = ";
    cin >> n;
    q = 1 / (n + 1);
    S = b1 * (pow(q,n) - 1) / (q - 1);
    std::cout << "S = " << S;
    return 0;
}