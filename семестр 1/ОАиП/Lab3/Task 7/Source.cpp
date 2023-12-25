#include <iostream>     
#include <iomanip> 
#include <cmath>
using namespace std;
long double factorial(long double n)
{
    long double sum, znak;
    sum = n;
    if (n == 0)
    {
        sum = 1;
        return sum;
    }
    while (n > 1)
    {
        sum = sum * (n - 1);
        n--;
    }
    return(sum);
}
long double logarifm(long double x)
{
    long double LN2 = 0.693147180559945309417232121458176568, znak = 0;
    const long double e = 1e-9;
    const long double lnln = LN2;
    int k = 0;
    if (x < 1e-1)
    {
        x = x / x / x;
        znak = 1;
    }
    while (x > 2.0)
    {
        x /= 2.0;
        k++;
    }
    x -= 1.;
    long double s = 0;
    int n = 1;
    long double an = x;
    while (abs(an) > e) {
        s += an;
        ++n;
        an *= -x * (n - 1) / n;
    }
    s += k * lnln;
    if (znak == 1)
        s = -s;
    return s;
}
long double sinys(double x) {
    long double sum = 0, n = 100, xs = x, pi = acos(-1), q = 1;
    xs /= 2 * pi;
    while (xs > 1)
    {
        xs /= 10;
        q++;
    }
    for (int i = 0; i < q - 1; i++)
    {
        xs -= long(xs);
        xs *= 10;
    }
    xs -= long(xs);
    xs *= 2 * pi;
    x = xs;
    for (long long k = 0; k < 100; k++) {
        sum += pow(-1, k) * pow(x, 2 * k + 1) / factorial(2 * k + 1);
    }
    return sum;
}
long double cosinys(long double x)
{
    long double sum = 0, n = 100, xs = x, pi = acos(-1), q = 1;
    xs /= 2 * pi;
    while (xs > 1)
    {
        xs /= 10;
        q++;
    }
    for (int i = 0; i < q - 1; i++)
    {
        xs -= long(xs);
        xs *= 10;
    }
    xs -= long(xs);
    xs *= 2 * pi;
    x = xs;
    for (long long k = 0; k < 100; k++)
    {
        sum += pow(-1, k) * pow(x, 2 * k) / factorial(2 * k);
    }
    return sum;
}
int main() {
    long double x, a, b, c;
    cin >> x;
    a = sinys(x);
    b = cosinys(x);
    c = logarifm(x);
    cout << setprecision(20) << a << endl;
    cout << setprecision(20) << sin(x) << endl;
    cout << setprecision(20) << b << endl;
    cout << setprecision(20) << cos(x) << endl;
    cout << setprecision(20) << c << endl;
    cout << setprecision(20) << log(x) << endl;
    return 0;
}