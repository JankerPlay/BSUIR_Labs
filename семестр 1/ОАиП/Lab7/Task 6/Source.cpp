#include <iostream>
#include <string>
#include <algorithm>

struct Array
{
    bool positive = true;
    int size;
    int* arr;
};

Array StringToLongNumber(std::string& inp);
void LongNumberPrint(const Array& numb, int base, bool AsArray = true);
Array Sum(const Array& a, const Array& b, int base);
Array Minus(const Array& a, const Array& b, int base);
bool Compare(const Array& a, const Array& b);
void Operations(Array& a, Array& b, int base);

int main()
{
        int base = 100;
        std::string numb1;
        Array a;
        Array b;
        std::cin >> base;
            std::cin >> numb1;
            std::transform(numb1.begin(), numb1.end(), numb1.begin(), ::tolower);
        a = StringToLongNumber(numb1); //O(numb1.size)
            std::cin >> numb1;
            std::transform(numb1.begin(), numb1.end(), numb1.begin(), ::tolower);
        b = StringToLongNumber(numb1);
        Array SumAB;
        SumAB.positive = true;
        if (a.positive && b.positive) // O(a.size + b.size)
            SumAB = Sum(a, b, base);
        else if (!a.positive && !b.positive)
        {
            SumAB = Sum(a, b, base);
            SumAB.positive = false;
        }
        else if (a.positive && !b.positive)
        {
            SumAB = Minus(a, b, base);
        }
        else
        {
            SumAB = Minus(b, a, base);
        }
        std::cout << "Sum = a + b = ";
        LongNumberPrint(SumAB, base, false);

        Array Diff;
        if (a.positive && b.positive) // O(a.size + b.size)
            Diff = Minus(a, b, base);
        else if (a.positive && !b.positive)
        {
            b.positive = true;
            Diff = Sum(a, b, base);
            b.positive = false;
        }
        else if (!a.positive && !b.positive)
        {
            b.positive = true;
            Diff = Minus(b, a, base);
            b.positive = false;
        }
        else
        {
            a.positive = false;
            b.positive = false;
            Diff = Sum(a, b, base);
            Diff.positive = false;
            b.positive = true;
        }
        std::cout << "Diff = a - b = ";
        LongNumberPrint(Diff, base, false);

        Diff.positive = !Diff.positive;
        std::cout << "Diff = b - a = ";
        LongNumberPrint(Diff, base, false);


    return 0;
}
bool Compare(const Array& a, const Array& b) //O(a.size)
{
    if (a.size > b.size)
        return true;
    if (a.size < b.size)
        return false;
    for (int i = a.size - 1; i >= 0; i--)
    {
        if (a.arr[i] < b.arr[i])
            return false;
        if (a.arr[i] > b.arr[i])
            break;
    }
    return true;
}

Array Minus(const Array& a, const Array& b, int base) // O(a.size + b.size)
{
    if (!Compare(a, b))
    {
        Array res = Minus(b, a, base);
        res.positive = false;
        return res;
    }
    Array res;
    res.size = std::max(a.size, b.size) + 1;
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

Array Sum(const Array& a, const Array& b, int base) // O(a.size + b.size)
{
    Array res;
    res.size = std::max(a.size, b.size) + 1;
    res.arr = (int*)calloc(res.size, res.size * 4);
    if (a.size > b.size)
    {
        for (int i = 0; i < a.size; i++)
        {
            res.arr[i] = a.arr[i];
        }
        for (int i = 0; i < b.size; i++)
        {
            res.arr[i] += b.arr[i];
            res.arr[i + 1] += res.arr[i] / base;
            res.arr[i] %= base;
        }
        for (int i = b.size; i < a.size; i++)
        {
            res.arr[i + 1] += res.arr[i] / base;
            res.arr[i] %= base;
        }
    }
    else
    {
        for (int i = 0; i < b.size; i++)
        {
            res.arr[i] = b.arr[i];
        }
        for (int i = 0; i < a.size; i++)
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

void LongNumberPrint(const Array& numb, int base, bool AsArray)
{
    if (numb.positive)
        std::cout << '+';
    else
        std::cout << '-';
    if (AsArray)
    {
        for (int i = numb.size - 1; i >= 0; i--)
        {
            std::cout << numb.arr[i] << ' ';
        }
        std::cout << '\n';
    }
    else
    {
        for (int i = numb.size - 1; i >= 0; i--)
        {
            if (numb.arr[i] >= 10)
                std::cout << char(numb.arr[i] - 10 + 'A');
            else
                std::cout << numb.arr[i];
        }
        std::cout << '\n';
    }
}

Array StringToLongNumber(std::string& inp)
{
    Array res;
    res.size = inp.size();
    res.arr = (int*)malloc(res.size * 4);
    if (inp[0] == '-')
        res.positive = false;
    for (int i = res.size - 1, j = 0; i >= 0; i--, j++)
    {
        if (inp[i] >= '0' && inp[i] <= '9')
            res.arr[j] = inp[i] - '0';
        else if (inp[i] != '+' && inp[i] != '-')
        {
            res.arr[j] = inp[i] - 'a' + 10;
        }
        else if (inp[i] == '+' || inp[i] == '-')
            res.size--;
    }
    return res;
}

bool NumberChecker(const std::string& numb, int base)
{
    if (numb[0] != '+' && numb[0] != '-' && !((numb[0] >= '0' && numb[0] <= '9')
        || (numb[0] >= 'a' && numb[0] <= 'a' + base - 10)))
        return false;
    int a = 0;
    if (numb[0] == '+' || numb[0] == '-')
        a = 1;
    if (base > 10)
    {
        for (int i = a; i < numb.size(); i++)
        {
            if (!((numb[i] >= '0' && numb[i] <= '9') || (numb[i] >= 'a' && numb[i] < 'a' + base - 10)))
                return false;
        }
    }
    else
    {
        for (int i = a; i < numb.size(); i++)
        {
            if (numb[i] < '0' || numb[i] >= '0' + base)
                return false;
        }
    }
    return true;
}
