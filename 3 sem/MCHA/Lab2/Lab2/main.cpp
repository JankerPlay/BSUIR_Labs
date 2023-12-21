#include <bits/stdc++.h>

class Matrix {
private:
    int V;

    double A[5][5];
    double A_2[5][6];
    double C[5][5]
    {
        {1.0 / 100, 0, -2.0 / 100, 0, 0},
        {1.0 / 100, 1.0 / 100, -2.0 / 100, 0, 0},
        {0, 1.0 / 100, 1.0 / 100, 0, -2.0 / 100},
        {0, 0, 1.0 / 100, 1.0 / 100, 0},
        {0, 0, 0, 1.0 / 100, 1.0 / 100}
    };

    double D[5][5]
    {
        {133.0 / 100, 21.0 / 100, 17.0 / 100, 12.0 / 100, -13.0 / 100},
        {-13.0 / 100, -133.0 / 100, 11.0 / 100, 17.0 / 100, 12.0 / 100},
        {12.0 / 100, -13.0 / 100, -133.0 / 100, 11.0 / 100, 17.0 / 100},
        {17.0 / 100, 12.0 / 100, -13.0 / 100, -133.0 / 100, 11.0 / 100},
        {11.0 / 100, 67.0 / 100, 12.0 / 100, -13.0 / 100, -133.0 / 100}
    };

    double b[5]{ 15.0 / 10, 22.0 / 10, 40.0 / 10, 0, -12.0 / 10 };
    double roots[5]{ 0, 0, 0, 0, 0 };

public:
    Matrix(const int V) : V(V) {
        std::cout << std::fixed << std::setprecision(4);
        compute_A();
        compute_A_2();
    }

    void compute_A() {
        for (int i = 0; i < 5; i++)
            for (int j = 0; j < 5; j++)
                A[i][j] = V * C[i][j] + D[i][j];
    }

    void compute_A_2() {
        for (int i = 0; i < 5; i++)
            for (int j = 0; j < 5; j++)
                A_2[i][j] = A[i][j];

        A_2[0][5] = 12.0 / 10;
        A_2[1][5] = 22.0 / 10;
        A_2[2][5] = 40.0 / 10;
        A_2[3][5] = 0;
        A_2[4][5] = -12.0 / 10;
    }

    void print_A() {
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++)
                std::cout << std::setw(10) << A[i][j];

            std::cout << std::setw(5) << '|' << std::setw(5) << b[i] << std::endl;
        }
    }

    void print_A_2() {
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++)
                std::cout << std::setw(10) << A_2[i][j];

            std::cout << std::setw(5) << '|' << std::setw(5) << A_2[i][5] << std::endl;
        }
    }


    std::vector<double> simpleIterations(int& iterations) {

        // Размер матрицы
        int size = 5;

        // Неизвестные на предыдущей итерации
        std::vector <double> prev_X(size, 0.0);

        // Пока не будет достигнута точность
        bool stop = false;
        while (!stop) {

            ++iterations;
            // Неизвестные на текущей итерации
            std::vector <double> current_X(size);

            for (int i = 0; i < size; i++) {
                // x_i = b_i
                current_X[i] = A_2[i][size];

                // Вычитаем сумму по всем отличным от i-ой неизвестным
                for (int j = 0; j < size; j++)
                    // С прошлой итерации
                    if (j != i)
                        current_X[i] -= A_2[i][j] * prev_X[j];

                // x_i /= b_i
                current_X[i] /= A_2[i][i];
            }

            // Максимальная погрешность
            long double max_error = 0.0;
            for (int i = 0; i < size; i++) {
                double new_max_error = abs(current_X[i] - prev_X[i]);
                max_error = new_max_error > max_error ? new_max_error :max_error;
            }

            // Дотигнута ли точность
            if (max_error < 0.0001)
                stop = true;

            // Переход к следующей итерации
            prev_X = current_X;
        }
        return prev_X;
    }

    std::vector<double> seidelMethod(int& iterations) {

        // Размер матрицы
        int size = 5;

        // Неизвестные на предыдущей итерации
        std::vector <double> prev_X(size, 0.0);

        // Пока не будет достигнута точность
        bool stop = false;
        while (!stop) {

            ++iterations;
            // Неизвестные на текущей итерации
            std::vector <double> current_X(size);

            for (int i = 0; i < size; i++) {

                // x_i = b_i
                current_X[i] = A_2[i][size];

                // Вычитаем сумму по всем отличным от i-ой неизвестным
                for (int j = 0; j < size; j++) {

                    // С этой итерации
                    if (j < i)
                        current_X[i] -= A_2[i][j] * current_X[j];

                    // С прошой итерации
                    if (j > i)
                        current_X[i] -= A_2[i][j] * prev_X[j];

                }
                // x_i /= b_i
                current_X[i] /= A_2[i][i];
            }

            // Максимальная погрешность
            long double max_error = 0.0;
            for (int i = 0; i < size; i++) {
                double new_max_error = abs(current_X[i] - prev_X[i]);
                max_error = new_max_error > max_error ? new_max_error :max_error;
            }

            // Дотигнута ли точность
            if (max_error < 0.0001)
                stop = true;

            // Переход к следующей итерации
            prev_X = current_X;
        }
        return prev_X;
    }


    int rang() {

        int rang = 5;
        //std::cout << "\nf_rang = " << rang << std::endl;
        double sum = 0;

        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 5; j++)
                sum += A[i][j];

            //std::cout << "sum  = " << sum << std::endl;
            if (sum == 0)
                rang = rang - 1;

            //std::cout << "rang " << i << "  = " << rang << std::endl;
            sum = 0;
        }
        //std::cout << "end rang = " << rang << std::endl;
        return rang;
    }

    int rang_2() {

        int rang = 6;
        //std::cout << "\nf_rang = " << rang << std::endl;
        double sum = 0;

        for (int i = 0; i < 6; i++)
        {
            for (int j = 0; j < 6; j++)
                sum += A_2[i][j];

            //std::cout << "sum  = " << sum << std::endl;
            if (sum == 0)
                rang = rang - 1;

            //std::cout << "rang " << i << "  = " << rang << std::endl;
            sum = 0;
        }
        return rang;
    }

    bool diagonal() {

        int i, j, k = 1;
        double sum;

        for (i = 0; i < 5; i++)
        {
            sum = 0;
            for (j = 0; j < 5; j++)
                sum += A[i][j];

            sum -= A[i][i];
            if (sum < A[i][i])
                return 0;
        }
        return (k == 1);
    }
};

int main()
{
    system("chcp 65001");

    Matrix matr(13);

    if (matr.rang() != matr.rang_2()) {
        std::cout << "Ранг исходной матрицы не равен рангу расширенной матрицы.\nСЛАУ не имеет решений.";
        return 0;
    }
    if (matr.rang() < 5) {
        std::cout << "Ранги матрицы равны или меньше числа неизвестных системы.\nСЛАУ имеет бесконечное множество решений.";
        return 0;
    }
    if (matr.diagonal()) {
        std::cout << "Исходная матрица не обладает свойством диагонального преобладания.\nРешение методом итераций/Зейделя невозможен.";
        return 0;
    }

    std::cout << matr.rang() << ", " << matr.rang_2();

    std::cout << "\t\t\tМетод итераций:" << std::endl << std::endl;
    std::cout << "\tИсходная матрица:" << std::endl;

    matr.print_A_2();
    int iterations = 0;
    std::vector<double> vect = matr.seidelMethod(iterations);

    std::cout << iterations << "\n";
    int t = 0;
    for (auto i : vect) {
        std::cout << ++t << ". " << i << "\n";
    }

    std::cout << "\n\n\t\t\tМетод Зейделя" << std::endl << std::endl;
    std::cout << "\tИсходная матрица:" << std::endl;
    matr.compute_A();
    matr.compute_A_2();
    matr.print_A_2();


    iterations = 0;
    vect = matr.simpleIterations(iterations);

    std::cout << iterations << "\n";

    for (auto i : vect) {
        std::cout << ++t << ". " << i << "\n";
    }
}
