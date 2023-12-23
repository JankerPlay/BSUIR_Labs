import numpy as np
import matplotlib.pyplot as plt
def input_func():
    def f(x): return np.tanh(x)

    left_border, dots_count, right_border = 0, 6, 2

    dots = []
    for i in range(dots_count):
        x = left_border + (right_border - left_border) * i / (dots_count - 1)
        y = f(x)
        dots += [(x, y)]

    return dots, f
def three_diag_solve(A, b):
    A = A.copy()
    b = b.copy()
    n = len(A)
    A[0][1] /= A[0][0]
    for i in range(1, n - 1):
        A[i][i + 1] /= (A[i][i] - A[i][i - 1] * A[i - 1][i])
    b[0] /= A[0][0]
    for i in range(1, n):
        b[i] = (b[i] - A[i][i - 1] * b[i - 1]) / (A[i][i] - A[i][i - 1] * A[i - 1][i])
    x = np.zeros(n)
    x[-1] = b[-1]
    for i in range(n - 2, -1, -1):
        x[i] = b[i] - A[i][i + 1] * x[i + 1]
    return x
def spline_built(dots):
    n = len(dots) - 1
    (x, y) = map(list, zip(*dots))
    h = [None]
    for i in range(1, n + 1):
        h += [x[i] - x[i - 1]]
    A = [[None] * n for i in range(n)]
    for i in range(1, n):
        for j in range(1, n):
            A[i][j] = 0.0
    for i in range(1, n - 1):
        A[i + 1][i] = h[i + 1]
    for i in range(1, n):
        A[i][i] = 2 * (h[i] + h[i + 1])
    for i in range(1, n - 1):
        A[i][i + 1] = h[i + 1]
    F = []
    for i in range(1, n):
        F += [3 * ((y[i + 1] - y[i]) / h[i + 1] - (y[i] - y[i - 1]) / h[i])]
    A = [A[i][1:] for i in range(len(A)) if i]
    c = three_diag_solve(A, F)
    c = [0.0] + list(c) + [0.0]
    def evaluate(xdot):
        for i in range(1, len(x)):
            if x[i - 1] <= xdot <= x[i]:
                val = 0
                val += y[i]
                b = (y[i] - y[i - 1]) / h[i] + (2 * c[i] + c[i - 1]) * h[i] / 3
                val += b * (xdot - x[i])
                val += c[i] * ((xdot - x[i]) ** 2)
                d = (c[i] - c[i - 1]) / (3 * h[i])
                val += d * ((xdot - x[i]) ** 3)
                return val
        return None
    def output():
        print("Кубический сплайн:", '\n')
        for i in range(1, len(x)):
            b = (y[i] - y[i - 1]) / h[i] + (2 * c[i] + c[i - 1]) * h[i] / 3
            d = (c[i] - c[i - 1]) / (3 * h[i])
            print(x[i - 1], x[i], "->")
            print(np.poly1d([d, c[i], b, y[i]]), '\n')
    return evaluate, output
print("Cubic spline interpolation \n")
plot_dots = 10 ** 4
dots, f = input_func()
(x, y) = map(list, zip(*dots))
print("(x,y) =", dots, '\n')
plt.plot(x, y, 'og')
x_plot = np.linspace(min(x), max(x), plot_dots)
y_plot = [f(xdot) for xdot in x_plot]
plt.plot(x_plot, y_plot)
spl, output = spline_built(dots)
y_plot = [spl(xdot) for xdot in x_plot]
plt.plot(x_plot, y_plot)
output()
xdot = 1                 #тут
print(f"          f({xdot}) =", f(xdot))
print(f"Кубический сплайн({xdot}) =", spl(xdot))
print(f"      Дельта({xdot}) =", abs(f(xdot) - spl(xdot)))
plt.show()