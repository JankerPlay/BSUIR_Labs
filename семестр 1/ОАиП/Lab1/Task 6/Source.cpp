#include <iostream>
#include <cmath>
int main() {
    using namespace std;
    float A, b, D, x, S, p, K, Y, B, C, n, Q, z, y, T, m, k, h, d;
    int O;
    cout << "choose variant = ";
    cin >> O;
    switch (O)
    {
    case 1:
        cout << "D = ";
        cin >> D;
        cout << "x = ";
        cin >> x;
        b = x + D;
        A = D * x / b;
        S = (A * A + b * cos(x)) / (D * D * D + (A + D - b));
        std::cout << "S = " << S;
    break;
    case 2:
        cout << "K = ";
        cin >> K;
        cout << "x = ";
        cin >> x;
        cout << "p = ";
        cin >> p;
        cout << "D = ";
        cin >> D;
        cout << "C = ";
        cin >> C;
        A = x + sin(p);
        B = exp(K);
        Y = 1 + K * K / (2 * A * B) - B + D * C;
        std::cout << "Y = " << Y;
        break;
    case 3:
        cout << "x = ";
        cin >> x;
        cout << "p = ";
        cin >> p;
        cout << "n = ";
        cin >> n;
        cout << "K = ";
        cin >> K;
        cout << "D = ";
        cin >> D;
        C = p - n;
        B = cos(x);
        Q = B * B / (K * D) + B * C * C * C;
        std::cout << "Q = " << Q;
        break;
    case 4:
        cout << "x = ";
        cin >> x;
        cout << "y = ";
        cin >> y;
        cout << "z = ";
        cin >> z;
        cout << "K = ";
        cin >> K;
        cout << "C = ";
        cin >> C;
        cout << "D = ";
        cin >> D;
        A = x - y;
        B = sqrt(z);
        T = cos(x) + A * A / (K - C * D) - B;
        std::cout << "T = " << T;
        break;
    case 5:
        cout << "x = ";
        cin >> x;
        cout << "n = ";
        cin >> n;
        cout << "m = ";
        cin >> m;
        cout << "K = ";
        cin >> K;
        D = tan(x);
        A = fabs(n + m);
        Y = 1.29 + K / A + D * D;
        std::cout << "Y = " << Y;
        break;
    case 6:
        cout << "x = ";
        cin >> x;
        cout << "y = ";
        cin >> y;
        cout << "C = ";
        cin >> C;
        cout << "K = ";
        cin >> K;
        A = x + y;
        D = labs(C - A);
        S = 10.1 + A / C + D / (K * K);
        std::cout << "S = " << S;
        break;
    case 7:
        cout << "x = ";
        cin >> x;
        cout << "p = ";
        cin >> p;
        cout << "h = ";
        cin >> h;
        cout << "K = ";
        cin >> K;
        cout << "C = ";
        cin >> C;
        cout << "D = ";
        cin >> D;
        A = x - p;
        B = log(h);
        Y = 0.78 * B + A * A * A / (K * C * D);
        std::cout << "Y = " << Y;
        break;
    case 8:
        cout << "x = ";
        cin >> x;
        cout << "d = ";
        cin >> d;
        cout << "C = ";
        cin >> C;
        cout << "K = ";
        cin >> K;
        A = log10(x);
        B = x + exp(d);
        Y = A + B - (C * C / K);
        std::cout << "Y = " << Y;
        break;
    case 9:
        cout << "x = ";
        cin >> x;
        cout << "z = ";
        cin >> z;
        cout << "p = ";
        cin >> p;
        cout << "K = ";
        cin >> K;
        cout << "C = ";
        cin >> C;
        cout << "D = ";
        cin >> D;
        A = sin(x) - z;
        B = labs(p - x);
        Y = pow(A + B, 2) - K / (C * D);
        std::cout << "Y = " << Y;
        break;
    case 10:
        cout << "D = ";
        cin >> D;
        cout << "C = ";
        cin >> C;
        cout << "x = ";
        cin >> x;
        cout << "z = ";
        cin >> z;
        cout << "k = ";
        cin >> k;
        A = log(x) - k;
        B = sqrt(z);
        Y = pow(D, 2) + (pow(C, 2) / (0.75 * A)) + B;
        std::cout << "Y = " << Y;
        break;
    default:
        break;
    }
    return 0;
}