import numpy as np
xi = np.array([0.0, 1.0, 2.0, 3.0, 4.0])
pi = np.array([0.0, 0.41, 0.79, 1.13, 1.46, 1.76, 2.04, 2.3, 2.55, 2.79, 3.01])
K = 6
M = 3
P = 0.47
yi = np.array([2.0, 2.0, 2.0, 2.0, 2.0])
#yi = pi + np.power(-1, K) * M