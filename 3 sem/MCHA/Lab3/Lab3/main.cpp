#include <bits/stdc++.h>
using namespace std;
#define ITERATIONS 1000
#define ll long long
#define ld long double
using namespace std;
ll binpow (ll a, ll n) {
    if (n == 0)
        return 1;
    if (n % 2 == 1)
        return binpow (a, n-1) * a;
    else {
        ll b = binpow (a, n/2);
        return b * b;
    }
}
struct Result {
    ld rootOfEq;
    ll iterations;
    Result(ld root = 0, ll iterations = 0) {
        this->rootOfEq = root;
        this->iterations = iterations;
    }
};
struct Segment {
    ld a;
    ld b;
    Segment(ld a = 0, ld b = 0) {
        this->a = a;
        this->b = b;
    }
};
class Polynomial {
private:
    ld a;
    ld b;
    ld c;
    //Задание 1
    ld f0(ld x) { return binpow(x, 3) + a * pow(x, 2) + b * x + c; }
    ld f1(ld x) { return 3 * binpow(x, 2) + 2 * a * x + b; }
    //Задание 2
    ld f2(ld x) { return ((2.0 / 9.0) * binpow(a, 2) * x - (2.0 / 3.0) * b * x + (1.0 / 9.0) * a * b - c); }
    //Задание 3
    ld f3(ld x) {
        ld numerator = 4 * pow(a, 3) * c - pow(a * b, 2) - 18 * a * b * c + 4 * pow(b, 3) + 27 * pow(c, 2);
        ld denominator = binpow(a * a - 3 * b, 2);
        return -(9.0 / 4.0) * (numerator / denominator);
    }
    // Метод Штурма
    ll N(ld x) {
        vector<ld> val(4);
        val[0] = f0(x);
        val[1] = f1(x);
        val[2] = f2(x);
        val[3] = f3(x);
        ll count = 0;
        for (ll i = 0; i < 3; i++)
            if (val[i] * val[i + 1] < 0)
                count++;
        return count;
    }
public:
    Polynomial(ld a, ld b, ld c) {
        this->a = a;
        this->b = b;
        this->c = c;
    }
    ll number_of_roots(Segment segment) {return N(segment.a) - N(segment.b);}
    vector<Segment> segment_with_roots(Segment segment, ld step) {
        vector<Segment> segments;
        for (ld x = segment.a; x < segment.b; x += step)
            if (f0(x) * f0(x + step) < 0)
                segments.emplace_back(x, x + step);
        vector<Segment> upd_segments;
        for (ll i = 0; i < segments.size(); i++) {
            // Если есть корни четной кратности
            if (number_of_roots(segments[i]) != 1)
                for (const auto& item : segment_with_roots(segments[i], step / 2))
                    upd_segments.push_back(item);
            else
                upd_segments.push_back(segments[i]);
        }
        return upd_segments;
    }
    Result half_division(Segment segment, ld eps) {
        // f(a) * f(b) меньше нуля или только 1 корень на промежутке
        if (!(f0(segment.a) * f0(segment.b) < 0) or number_of_roots(segment) != 1)
            return Result(-1, -1);
        ll iterations = 1;
        ld left = segment.a;
        ld right = segment.b;
        ld middle = (left + right) / 2;
        while (abs(f0(middle)) > eps && iterations < ITERATIONS) {
            //f(a)*f((a+b)/2)
            if (f0(left) * f0(middle) < 0)
            { right = middle; }
            else
            { left = middle; }
            middle = (left + right) / 2;
            iterations++;
        }
        return Result(middle, iterations);
    }
    Result chrod_method(Segment segment, ld eps) {
        // f(a) * f(b) меньше нуля или только 1 корень на промежутке
        if (!(f0(segment.a) * f0(segment.b) < 0) or number_of_roots(segment) != 1)
            return Result(-1, -1);
        ll iterations = 1;
        ld Xn_prev = 0;
        ld Xn_curr = 0;
        // выбор уравнения(f(b)*f''(b))
        if (f0(segment.b) * (2 * a + 6 * segment.b) > 0) {
            Xn_prev = segment.a;
            Xn_curr = Xn_prev - (f0(Xn_prev) / (f0(segment.b) - f0(Xn_prev))) * (segment.b - Xn_prev);
            while (fabs(Xn_curr - Xn_prev) > eps && iterations < ITERATIONS) {
                Xn_prev = Xn_curr;
                Xn_curr = Xn_prev - (f0(Xn_prev) / (f0(segment.b) - f0(Xn_prev))) * (segment.b - Xn_prev);
                iterations++;
            }
        }
        else {
            Xn_prev = segment.b;
            Xn_curr = Xn_prev - (f0(Xn_prev) / (f0(segment.a) - f0(Xn_prev))) * (segment.a - Xn_prev);
            while (fabs(Xn_curr - Xn_prev) > eps && iterations < ITERATIONS) {
                Xn_prev = Xn_curr;
                Xn_curr = Xn_prev - (f0(Xn_prev) / (f0(segment.a) - f0(Xn_prev))) * (segment.a - Xn_prev);
                iterations++;
            }
        }
        return Result(Xn_curr, iterations);
    }
    Result Newthon_method(Segment segment, ld eps) {
        // только 1 корень на промежутке
        if (number_of_roots(segment) != 1)
            return Result(-1, -1);
        ll iterations = 1;
        ld Xn_prev = 0;
        // выбор Xn
        if (f0(segment.b) >= 0)
            Xn_prev = segment.b;
        else
            Xn_prev = segment.a;
        // Xn - (f(Xn)/f'(Xn))
        ld Xn_curr = Xn_prev - f0(Xn_prev) / f1(Xn_prev);
        while (fabs(Xn_curr - Xn_prev) > eps && iterations < ITERATIONS) {
            Xn_prev = Xn_curr;
            // Xn+1 = Xn - (f(Xn)/f'(Xn))
            Xn_curr = Xn_prev - f0(Xn_prev) / f1(Xn_prev);
            iterations++;
        }
        if (segment.a < 0 and segment.b < 0 and Xn_curr>0)
            Xn_curr *= -1;
        return Result(Xn_curr, iterations);
    }
};
int main() {
    system("chcp 65001");
    ld leftSegment = -10;
    ld rightSegment = 10;
    ld a = -10.9991;
    ld b = -12.7595;
    ld c = 80.5320;
    Polynomial polynomial(a, b, c);
    //Eps
    ld eps = 0.0001;
    //Количество знаков после запятой
    ll signs = 4;
    //Отделять корни табличным методом с шагом
    ld step = 1;
    cout << "Первое задание:" << endl;
    //Вывод отрезка
    cout << "Отрезок: [" << setprecision(signs) << leftSegment << ", " << setprecision(signs) << rightSegment << "]" << endl;
    ll rootsNumber = polynomial.number_of_roots(Segment(leftSegment, rightSegment));
    //Кол-во корней
    cout << "Количество корней: " << rootsNumber << endl << endl;
    vector<Segment> segmentsWithRoots = polynomial.segment_with_roots(Segment(leftSegment, rightSegment), step);
    cout << "Второе задание:" << endl;
   //Если обнаружен корень чётной кратности, то нужно отделить корни вручную
    if (rootsNumber != segmentsWithRoots.size()) {
       cout << endl << "Обнаружен корень четной кратности." << endl;
        //Нужно отделить корни вручную
        cout << "Необходимо отделить корень вручную." << endl << endl;
        segmentsWithRoots.clear();
        segmentsWithRoots.resize(rootsNumber);
        for (ll i = 0; i < rootsNumber; i++) {
            //Отрезок с корнем
            cout << "Отрезок с корнем " << i + 1 << ": " << endl;
            cin >> segmentsWithRoots[i].a >> segmentsWithRoots[i].b;
        }
    }
    else {
        if (!segmentsWithRoots.empty()) {
            //Отрезки
            cout << "Отрезки: \n";
            for (const auto segment : segmentsWithRoots)
                cout << "[" << setprecision(signs) << segment.a << ", " << segment.b << "]" << endl;
        }
        else {
            cout << "Нет корней на отрезке [" << leftSegment << ", " << rightSegment << "]";
        }
    }
    cout << endl;
    cout << "Третье задание:";
    if (rootsNumber){
        //Метод половинного деления
        map<ll, string> methodsNames({ make_pair(0, "Метод половинного деления: "),
                                              //Метод хорд
                                        make_pair(1, "Метод хорд: "),
                                              //Метод Ньютона
                                        make_pair(2, "Метод Ньютона: ") });

        map<string, vector<Result>> results;
        for (ll i = 0; i < rootsNumber; i++) {
            results["Метод половинного деления: "].push_back(polynomial.half_division(segmentsWithRoots[i], eps));
            results["Метод хорд: "].push_back(polynomial.chrod_method(segmentsWithRoots[i], eps));
            results["Метод Ньютона: "].push_back(polynomial.Newthon_method(segmentsWithRoots[i], eps));
        }
        for (ll i = 0; i < rootsNumber; i++) {
            cout << endl << "Отрезок [" << setprecision(signs) << segmentsWithRoots[i].a
                 << ", " << setprecision(signs) << segmentsWithRoots[i].b << "]: " << endl;
            for (ll j = 0; j < 3; j++) {
                cout << setw(27) << right << methodsNames[j];
                cout << setw(signs + 3) << right << setprecision(signs) << results[methodsNames[j]][i].rootOfEq
                // Кол-во итераций
                     << " Количество итераций: " << results[methodsNames[j]][i].iterations << endl;
            }
        }
    }
    else {
        cout << endl <<"Нет корней на отрезке [" << leftSegment << ", " << rightSegment << "]" << endl;
    }
}