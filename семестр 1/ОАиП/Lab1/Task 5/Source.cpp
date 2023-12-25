#include <iostream>
int main() {
    using namespace std;
    float a1, a100, n, R, S, N;
    cout << "a1 = ";
    cin >> a1;
    cout << "a100 = ";
    cin >> a100;
    cout << "n = ";
    cin >> n;
    N = n + 10;
    R = (a100 - a1) / 99;
    S = N / 2 * (2 * a1 + (N - 1) * R);
    std::cout << "R = " << R;
    std::cout << "\nS = " << S;
    return 0;
}