#include <iostream>
#include <algorithm>
#define ll long long
using namespace std;
struct A
{
    bool znak = 1;
    int size;
    int* arr;
};
bool Compare(const A& a, const A& b)
{
    if (a.size > b.size)
        return 1;
    if (a.size < b.size)
        return 0;
    for (ll i = a.size - 1; i >= 0; i--)
    {
        if (a.arr[i] < b.arr[i])
            return 0;
        if (a.arr[i] > b.arr[i])
            break;
    }
    return 1;
}
A Minus(const A& a, const A& b, int base)
{
    if (!Compare(a, b))
    {
        A res = Minus(b, a, base);
        res.znak = 0;
        return res;
    }
    A res;
    res.size = max(a.size, b.size) + 1;
    res.arr = (int*)calloc(res.size, res.size * 4);
    for (int i = 0; i < a.size; i++)
    {
        res.arr[i] = a.arr[i];
    }
    for (int i = 0; i < b.size; i++)
    {
        res.arr[i] -= b.arr[i];
        if (res.arr[i] < 0)
        {
            res.arr[i] += base;
            res.arr[i + 1]--;
        }
    }
    if (!res.arr[res.size - 1])
        res.size--;
    return res;
}

A Sum(const A& a, const A& b, int base)
{
    A res;
    res.size = max(a.size, b.size) + 1;
    res.arr = (int*)calloc(res.size, res.size * 4);
    if (a.size > b.size)
    {
        for (ll i = 0; i < a.size; i++)
        {
            res.arr[i] = a.arr[i];
        }
        for (ll i = 0; i < b.size; i++)
        {
            res.arr[i] += b.arr[i];
            res.arr[i + 1] += res.arr[i] / base;
            res.arr[i] %= base;
        }
        for (ll i = b.size; i < a.size; i++)
        {
            res.arr[i + 1] += res.arr[i] / base;
            res.arr[i] %= base;
        }
    }
    else
    {
        for (ll i = 0; i < b.size; i++)
        {
            res.arr[i] = b.arr[i];
        }
        for (ll i = 0; i < a.size; i++)
        {
            res.arr[i] += a.arr[i];
            res.arr[i + 1] += res.arr[i] / base;
            res.arr[i] %= base;
        }
        for (int i = a.size; i < b.size; i++)
        {
            res.arr[i + 1] += res.arr[i] / base;
            res.arr[i] %= base;
        }
    }
    if (!res.arr[res.size - 1])
        res.size--;
    return res;
}

void print(const A& numb, int base, bool AsA)
{
    if (!numb.znak)
        cout << '-';
    if (AsA)
    {
        for (ll i = numb.size - 1; i >= 0; i--)
        {
            cout << numb.arr[i] << ' ';
        }
        cout << endl;
    }
    else
    {
        for (ll i = numb.size - 1; i >= 0; i--)
        {
            if (numb.arr[i] >= 10)
                cout << char(numb.arr[i] - 10 + 'A');
            else
                cout << numb.arr[i];
        }
        cout << endl;
    }
}
A toll(string& inp)
{
    A res;
    res.size = inp.size();
    res.arr = (int*)malloc(res.size * 4);
    if (inp[0] == '-')
        res.znak = 0;
    for (ll i = res.size - 1, j = 0; i >= 0; i--, j++)
    {
        if (inp[i] >= '0' and inp[i] <= '9')
            res.arr[j] = inp[i] - '0';
        else if (inp[i] != '+' and inp[i] != '-')

            res.arr[j] = inp[i] - 'a' + 10;
        else if (inp[i] == '+' or inp[i] == '-')
            res.size--;
    }
    return res;
}
int main()
{
    ll base = 100;
    string num1, num2;
    A a;
    A b;
    cin >> base;
    cin >> num1;
    transform(num1.begin(), num1.end(), num1.begin(), tolower);
    a = toll(num1);
    cin >> num2;
    transform(num2.begin(), num2.end(), num2.begin(), tolower);
    b = toll(num2);
        A SumAB;
        SumAB.znak = 1;
        if (a.znak and b.znak)
            SumAB = Sum(a, b, base);
        else if (!a.znak and !b.znak)
        {
            SumAB = Sum(a, b, base);
            SumAB.znak = 0;
        }
        else if (a.znak and !b.znak)
        {
            SumAB = Minus(a, b, base);
        }
        else
        {
            SumAB = Minus(b, a, base);
        }
        cout << "a + b = ";
        print(SumAB, base, 0);
        A Diff;
        if (a.znak and b.znak)
            Diff = Minus(a, b, base);
        else if (a.znak and !b.znak)
        {
            b.znak = 1;
            Diff = Sum(a, b, base);
            b.znak = 0;
        }
        else if (!a.znak and !b.znak)
        {
            b.znak = 1;
            Diff = Minus(b, a, base);
            b.znak = 0;
        }
        else
        {
            a.znak = 0;
            b.znak = 0;
            Diff = Sum(a, b, base);
            Diff.znak = 0;
            b.znak = 1;
        }
        cout << "a - b = ";
        print(Diff, base, 0);
    return 0;
}