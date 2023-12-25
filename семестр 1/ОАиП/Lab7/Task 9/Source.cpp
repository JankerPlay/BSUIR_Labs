#include <iostream>
#include <algorithm>
#include <vector>
#define ll long long
#define vi vector<ll>
using namespace std;
string perevod(ll a)
{
    string s;
    ll mod, bin;
    while (a)
    {
        mod = a % 3;
        a /= 3;
        s.push_back(mod+48);
    }
    while (s.size() < 5)
    {
        s += '0';
    }
    return s;
}
ll obratno(string s)
{
    reverse(s.begin(), s.end());
    ll a=0;
    for (ll i = 0; i < 5; i++)
    {
        if (s[i] == '0')
            a += 0 * pow(3, i);
        if (s[i] == '1')
            a += 1 * pow(3, i);
        if (s[i] == '2')
            a += 2 * pow(3, i);
    }
    return a;
}
int main() {
    setlocale(LC_ALL, "");
    ll a;
    cin >> a;
    string s;
        s = perevod(a);
        reverse(s.begin(), s.end());
        cout << s << endl;
        vi mas;
        if (s[4] == '0')
        {
            ll x = 1;
            while (x <= 240)
            {
                mas.push_back(x);
                mas.push_back(x+1);
                x += 3;
            }
        }
        if (s[3] == '0')
        {
            ll x = 3;
            while (x <= 240)
            {
                mas.push_back(x);
                mas.push_back(x + 1);
                mas.push_back(x + 2);
                mas.push_back(x + 3);
                mas.push_back(x + 4);
                mas.push_back(x + 5);
                x += 9;
            }
        }
        if (s[2] == '0')
        {
            ll x = 9;
            while (x <= 240)
            {
                mas.push_back(x);
                x++;
                if (x == 27 or x == 54 or x == 81 or x == 108 or x == 135 or x == 162 or x == 189 or x == 216)
                    x += 9;
            }
        }
       if (s[1] == '0')
        {
            ll x = 27;
            while (x <= 240)
            {
                mas.push_back(x);
                x++;
                if (x == 81 or x == 135 or x == 189)
                    x += 27;
            }
        }
       if (s[0] == '0')
       {
           mas.push_back(81);
           mas.push_back(162);
       }
       sort(mas.begin(), mas.end());
       mas.erase(unique(mas.begin(), mas.end()), mas.end());
       cout << "Бочки в который точно нету яда" << endl;
        for (ll i = 0; i < mas.size(); i++)
            cout << mas[i] << " ";
        mas.clear();
        if (s[4] == '1')
        {
            ll x = 1;
            while (x <= 240)
            {
                mas.push_back(x);
                x += 3;
            }
            cout << endl;
            cout << "Бочки от который мог умереть 1-й в 1-й день ";
            for (ll i = 0; i < mas.size(); i++)
                cout << mas[i] << " ";
            mas.clear();
        }
        if (s[4] == '2')
        {
            ll x = 2;
            while (x <= 240)
            {
                mas.push_back(x);
                x += 3;
            }
            cout << endl;
            cout << "Бочки от который мог умереть 1-й в 2-й день ";
            for (ll i = 0; i < mas.size(); i++)
                cout << mas[i] << " ";
            mas.clear();
        }
       if (s[3] == '1')
        {
            ll x = 3;
            while (x <= 240)
            {
                mas.push_back(x);
                mas.push_back(x + 1);
                mas.push_back(x + 2);
                x += 9;
            }
            cout << endl;
            cout << "Бочки от который мог умереть 2-й в 1-й день ";
            for (ll i = 0; i < mas.size(); i++)
                cout << mas[i] << " ";
            mas.clear();
        }
       if (s[3] == '2')
       {
           ll x = 6;
           while (x <= 240)
           {
               mas.push_back(x);
               mas.push_back(x + 1);
               mas.push_back(x + 2);
               x += 9;
           }
           cout << endl;
           cout << "Бочки от который мог умереть 2-й в 2-й день ";
           for (ll i = 0; i < mas.size(); i++)
               cout << mas[i] << " ";
           mas.clear();
       }
         if (s[2] == '1')
        {
            ll x = 9;
            while (x <= 240)
            {
                mas.push_back(x);
                x++;
                if (x == 18 or x == 45 or x == 72 or x == 99 or x == 126 or x == 153 or x == 180 or x == 207 or x == 234)
                    x += 18;
            }
            cout << endl;
            cout << "Бочки от который мог умереть 3-й в 1-й день ";
            for (ll i = 0; i < mas.size(); i++)
                cout << mas[i] << " ";
            mas.clear();
        }
         if (s[2] == '2')
         {
             ll x = 18;
             while (x <= 240)
             {
                 mas.push_back(x);
                 x++;
                 if (x == 27 or x == 54 or x == 81 or x == 107 or x == 135 or x == 162 or x == 189 or x == 216)
                     x += 18;
             }
             cout << endl;
             cout << "Бочки от который мог умереть 3-й в 2-й день ";
             for (ll i = 0; i < mas.size(); i++)
                 cout << mas[i] << " ";
             mas.clear();
         }
       if (s[1] == '1')
        {
            ll x = 27;
            while (x <= 240)
            {
                mas.push_back(x);
                x++;
                if (x == 54 or x == 135 or x == 216)
                    x += 54;
            }
            cout << endl;
            cout << "Бочки от который мог умереть 4-й в 1-й день ";
            for (ll i = 0; i < mas.size(); i++)
                cout << mas[i] << " ";
            mas.clear();
        }
       if (s[1] == '2')
       {
           ll x = 54;
           while (x <= 240)
           {
               mas.push_back(x);
               x++;
               if (x == 81 or x == 162)
                   x += 54;
           }
           cout << endl;
           cout << "Бочки от который мог умереть 4-й в 2-й день ";
           for (ll i = 0; i < mas.size(); i++)
               cout << mas[i] << " ";
           mas.clear();
       }
       if (s[0] == '1')
        {
           ll x = 81;
           while (x <= 161)
           {
               mas.push_back(x);
               x++;
           }
           cout << endl;
           cout << "Бочки от который мог умереть 5-й в 1-й день ";
           for (ll i = 0; i < mas.size(); i++)
               cout << mas[i] << " ";
           mas.clear();
        }
       if (s[0] == '2')
       {
           ll x = 162;
           while (x <= 240)
           {
               mas.push_back(x);
               x++;
           }
           cout << endl;
           cout << "Бочки от который мог умереть 5-й в 2-й день ";
           for (ll i = 0; i < mas.size(); i++)
               cout << mas[i] << " ";
           mas.clear();
       }
       cout << endl;
       cout << "Отравленная бочка " << obratno(s);
        return 0;
}
