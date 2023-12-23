degree = 9 #Степень многочлена

def poly_func(x, *coeffs):  #Сумма квадратов разностей между знач функции и знач многочлена
    return sum(c * x**i for i, c in enumerate(coeffs))

def format_polynomial(coeffs):
    terms = []
    for i, c in enumerate(coeffs):
        if i == 0:
            terms.append(f"{c:.10f}")
        else:
            terms.append(f"{c:.10f}x^{i}")
    return " + ".join(terms)