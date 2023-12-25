#include <iostream>
#include <math.h>
int main() {
    using namespace std;
    float h, t;
    cout << "h = ";
    cin >> h;
    cout.precision(10);
    t = sqrt(2 / 9.81 * h);
    std::cout << "t = " << t;
    return 0;
}