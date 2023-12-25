#include <iostream>
int main() {
    using namespace std;
    int h1,min1,h2,min2,min3,min4,min5,x,y;
    cout << "h1 = ";
    cin >> h1;
    cout << "min1 = ";
    cin >> min1;
    cout << "h2 = ";
    cin >> h2;
    cout << "min2 = ";
    cin >> min2;
    if (min1 >= 60 or min2 >= 60 or h2>h1)
        cout << "ERROR";
    else if (h1==h2 and min2 >min1)
        cout << "ERROR";
    else
    {
        min3 = h1 * 60 + min1;
        min4 = h2 * 60 + min2;
        min5 = min4 - min3;
        x = min5 / 60;
        y = min5 - (x * 60);
        std::cout << "hours = " << x;
        std::cout << "\nminutes = " << y;
    }
    return 0;
}