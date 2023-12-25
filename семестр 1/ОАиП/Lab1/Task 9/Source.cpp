#include <iostream>
int main() {
    using namespace std;
    long a, b;
    cout << "a = ";
    cin >> a;
    if (a == 2147483647 or a == -2147483648)
        cout << "ERROR";
    else
    {
        cout << "b = ";
        cin >> b;

        if (b == 2147483647 or b == -2147483648)
            cout << "ERROR";
        else
        {
            a = a + b; std::cout << "\n" << a;
            b = a - b; std::cout << "\n" << b;
            a = a - b; std::cout << "\n" << a;
            cout << "\na=" << a;
            cout << "\nb=" << b;
        }
    }
    return 0;
}