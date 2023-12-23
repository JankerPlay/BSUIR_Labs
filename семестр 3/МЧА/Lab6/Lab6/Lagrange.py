import numpy as np
from task import xi, yi
def get_coefficients(_pl: int, _xi: np.ndarray):
    n = int(_xi.shape[0])
    coefficients = np.empty((n, 2), dtype=float)
    for i in range(n):
        if i == _pl:
            coefficients[i][0] = float('inf')
            coefficients[i][1] = float('inf')
        else:
            coefficients[i][0] = 1 / (_xi[_pl] - _xi[i])
            coefficients[i][1] = -_xi[i] / (_xi[_pl] - _xi[i])
    filtered_coefficients = np.empty((n - 1, 2), dtype=float)
    j = 0
    for i in range(n):
        if coefficients[i][0] != float('inf'):
            # изменение последовательности, степень увеличивается
            filtered_coefficients[j][0] = coefficients[i][1]
            filtered_coefficients[j][1] = coefficients[i][0]
            j += 1
    return filtered_coefficients
def get_polynomial_l(_xi: np.ndarray):
    n = int(_xi.shape[0])
    pli = np.zeros((n, n), dtype=float)
    for pl in range(n):
        coefficients = get_coefficients(pl, _xi)
        for i in range(1, n - 1):  # проходим по массиву coefficients
            if i == 1:  # на второй итерации занимаются 0-2 степени
                pli[pl][0] = coefficients[i - 1][0] * coefficients[i][0]
                pli[pl][1] = coefficients[i - 1][1] * coefficients[i][0] + coefficients[i][1] * coefficients[i - 1][0]
                pli[pl][2] = coefficients[i - 1][1] * coefficients[i][1]
            else:
                clone_pli = np.zeros(n, dtype=float)
                for val in range(n):
                    clone_pli[val] = pli[pl][val]
                zeros_pli = np.zeros(n, dtype=float)
                for j in range(n-1):  # проходим по строке pl массива pli
                    product_1 = clone_pli[j] * coefficients[i][0]
                    product_2 = clone_pli[j] * coefficients[i][1]
                    zeros_pli[j] += product_1
                    zeros_pli[j+1] += product_2
                for val in range(n):
                    pli[pl][val] = zeros_pli[val]
    return pli
def get_polynomial_lagrange(_xi: np.ndarray, _yi: np.ndarray):
    n = int(_xi.shape[0])
    polynomial_l = get_polynomial_l(_xi)
    for i in range(n):
        for j in range(n):
            polynomial_l[i][j] *= _yi[i]
    L = np.zeros(n, dtype=float)
    for i in range(n):
        for j in range(n):
            L[i] += polynomial_l[j][i]
    for i in range(L.size):
        if L[i] != 0:
            if i != 1:
                if i == 0:
                    buff = f"{L[i]}"
                    ind = i + 1
                    break
                else:
                    buff = f"{L[i]}x^{i}"
                    ind = i + 1
                    break
            else:
                buff = f"{L[i]}x"
                ind = i + 1
                break
    for i in range(ind, L.size - 1):
        if L[i] != 0:
            if L[i] > 0:
                if i == 1:
                    buff += f" + {L[i]}x"
                else:
                    buff += f" + {L[i]}x^{i}"
            else:
                if i == 1:
                    buff += f" - {abs(L[i + 1])}x"
                else:
                    buff += f" - {abs(L[i + 1])}x^{i}"
    return buff
def omega(x_var, j):
    return np.array([x_var - x_j for x_j in xi if x_j != xi[j]]).prod()
def l_div_seq(x_i, j):
    return omega(x_i, j) / omega(xi[j], j)
def LagrangePolynomialValueInPoint(x_var):
    return sum([l_div_seq(x_var, j) * yi[j] for j in range(len(xi))])