from Lagrange import get_polynomial_lagrange, LagrangePolynomialValueInPoint
from Newton import get_polynomial_newton, get_coefficients, NewtonPolynomialValueInPoint
from task import xi, yi, P
import matplotlib.pyplot as plt
import numpy as np

print("Интерполяционный многочлен Лагранжа:")
print(get_polynomial_lagrange(xi, yi), "\n")
print(f"Значение многочлена в точке {P}:")
print(LagrangePolynomialValueInPoint(P))

coefficients = get_coefficients(xi)
print("\nИнтерполяционный многочлен Ньютона:")
print(get_polynomial_newton(coefficients, xi), "\n")
print(f"Значение многочлена в точке {P}:")
print((NewtonPolynomialValueInPoint(coefficients, xi, P)))

print("\nЗначение в точке, вычисленное с помощью пакета numpy:")
print(np.interp(P, xi, yi))
x_values = np.linspace(100, 10000, 100)
lagrange_y = [LagrangePolynomialValueInPoint(x_val) for x_val in x_values]
newton_y = [NewtonPolynomialValueInPoint(coefficients, xi, x_val) for x_val in x_values]
plt.plot(x_values, lagrange_y, label='Polynom', color='blue')

plt.legend()
plt.xlabel('x')
plt.ylabel('y')
plt.title('Polynom')
plt.grid()
plt.show()