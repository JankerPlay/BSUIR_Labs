import numpy as np
def jacobi_eigenvalue_algorithm(A, tolerance): #Решение методом Якоби
    if not check_equal_dim(A):
        raise ValueError("Matrix isn't n, n dimension")
    n = A.shape[0]
    eigenvalues = np.diag(A)
    eigenvectors = np.eye(n)
    max_iterations = 1000
    iteration = 0
        # Вычисление максимального недиагонального элемента
    off_diag = np.abs(A - np.diag(eigenvalues)).max()
    while off_diag > tolerance and iteration < max_iterations:
        # Находим индексы максимального недиагонального элемента
        indices = np.argmax(np.abs(A - np.diag(eigenvalues)))
        i = indices // n
        j = indices % n
        # Вычисляем угол поворотаw
        if A[i, i] == A[j, j]:
            theta = np.pi / 4
        else:
            theta = 0.5 * np.arctan(2 * A[i, j] / (A[i, i] - A[j, j]))
        # Создаем матрицу вращения
        rotation_matrix = np.eye(n)
        rotation_matrix[i, i] = rotation_matrix[j, j] = np.cos(theta)
        rotation_matrix[i, j] = -np.sin(theta)
        rotation_matrix[j, i] = np.sin(theta)
        # Применяем матрицу вращения к матрице A
        A = rotation_matrix.T @ A @ rotation_matrix

        # Применяем матрицу вращения к матрице собственных векторов
        eigenvectors = eigenvectors @ rotation_matrix
        # Обновляем собственные значения и проверяем условие остановки
        eigenvalues = np.diag(A)
        off_diag = np.abs(A - np.diag(eigenvalues)).max()
        iteration += 1
    return eigenvalues, eigenvectors, iteration
def meth_danil(matrix, tol=0.0001, verbose=0): #Решение методом Данилевского
    # Проверяется, является ли матрица matrix квадратной
    # (check_equal_dim - функция, которая проверяет равенство числа строк и столбцов матрицы).
    if not check_equal_dim(matrix):
        raise ValueError("Matrix isn't n, n dimension")
    if verbose == 1:
        print("Computing eigenvalues...")
    a = matrix.copy()
    f = matrix.copy()
    n = a.shape[0]
    s = np.eye(n)
    for i in range(n - 1):
        m = np.eye(n)
        # Cоздается матрица m, которая является единичной, кроме строки n - 2 - i, которая заменяется на f[n - 1 - i].
        m[n - 2 - i][:] = f[n - 1 - i][:]
        f = np.dot(m, f)  # умножаем A на M^(-1) слева
        f = np.dot(f, np.linalg.inv(m))  # умножаем A на M справа
        s = np.dot(s, np.linalg.inv(m))  # находим S
    p = f[0]  # выделяем p
    p = p * (-1)
    p = np.insert(p, 0, 1)
    eig_val = np.roots(p)
    eig_vec = np.zeros(shape=(eig_val.shape[0], n))
    for j in range(0, eig_val.shape[0]):
        y = np.zeros(shape=(n, 1))
        for i in range(0, n):
            y[n-1-i] = eig_val[j]**i
        x = np.dot(s, y)  # находим собственный вектор
        norm = np.linalg.norm(x)
        for i in range(0, n):
            eig_vec[i][j] = x[i][0]/norm
    return eig_val, eig_vec

def is_matrix_symmetric(matrix, eps) -> bool:
    for i in range(1, len(matrix)):
        for j in range(i):
            if matrix[i][j] - matrix[j][i] >= eps:
                return False
    return True
def check_equal_dim(matrix):
    if matrix.shape[0] != matrix.shape[1]:
        return False
    return True
C = np.array([[0.2, 0, 0.2, 0, 0],
              [0, 0.2, 0, 0.2, 0],
              [0.2, 0, 0.2, 0, 0.2],
              [0, 0.2, 0, 0.2, 0],
              [0, 0, 0.2, 0, 0.2]])
D = np.array([[2.33, 0.81, 0.67, 0.92, -0.53],
              [0.81, 2.33, 0.81, 0.67, 0.92],
              [0.67, 0.81, 2.33, 0.81, 0.92],
              [0.92, 0.67, 0.81, 2.33, -0.53],
              [-0.53, 0.92, 0.92, -0.53, 2.33]])
A = 13 * C + D
print("Изначальная матрица: ")
print(A)
print("Решение методом Якоби: ")
eigenvalues, eigenvectors, iteration = jacobi_eigenvalue_algorithm(A, 0.0001)
print("Матрица собственных значений: ")
print(eigenvalues)
print("Собственные векторы: ")
print(eigenvectors)
print("Количество итераций: ", iteration)
print()
print("Решение методом Данилевского: ")
eigenvalues, eigenvectors = meth_danil(A)
print("Матрица собственных значений: ")
print(eigenvalues)
print("Собственные векторы: ")
print(eigenvectors)