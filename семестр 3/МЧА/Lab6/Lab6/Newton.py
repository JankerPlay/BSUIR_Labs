import numpy as np
from task import xi, yi
def get_coefficients(xi):
    n = len(xi)
    coefficients = np.zeros((n, n))

    for i in range(n):
        coefficients[i][0] = yi[i]

    for j in range(1, n):
        for i in range(j, n):
            coefficients[i][j] = (coefficients[i][j - 1] - coefficients[i - 1][j - 1]) / (xi[i] - xi[i - j])

    return coefficients
def NewtonPolynomialValueInPoint(coefficients, xi, x):
    n = len(xi)
    result = coefficients[0][0]
    term = 1

    for i in range(1, n):
        term *= (x - xi[i - 1])
        result += coefficients[i][i] * term

    return result
def get_polynomial_newton(coefficients, xi):
    n = len(xi)
    polynomial = ""
    for i in range(n):
        term = str(coefficients[i][i])
        if i > 0:
            for j in range(i):
                term += f"*(x - {xi[j]})"
        polynomial += term
        if i < n - 1:
            polynomial += " + "

    return polynomial