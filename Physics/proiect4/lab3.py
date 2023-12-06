# Date de exemplu (înlocuiți cu datele reale)
x_data = np.array([0.5, 1, 1.5, 2, 2.5])
A_data = np.array([13938, 8848, 5494, 3455, 2170])

import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit

# Definirea funcției pentru regresia liniară
def linear_regression(x, a, b):
    return a * x + b

# Logaritmizare: A = A0 * exp(-miu * x) => ln(A) = ln(A0) - miu * x
ln_A_data = np.log(A_data)

# Regresie liniară
params, covariance = curve_fit(linear_regression, x_data, ln_A_data)

# Parametrii: a și b (pentru ecuația y = ax + b)
a, b = params

# Calcularea pantei
miu = -a

# Generare puncte pentru linia de regresie
x_fit = np.linspace(min(x_data), max(x_data), 100)
ln_A_fit = linear_regression(x_fit, a, b)

# Plotare datele originale și linia de regresie
plt.scatter(x_data, ln_A_data, label='Date Logaritmice')
plt.plot(x_fit, ln_A_fit, color='red', label='Linie de Regresie')
plt.xlabel('x cm')
plt.ylabel('ln(A) impulsuri')
plt.legend()
plt.title('Plumb, miu: 0.9320304997018676 cm^(-1)')
plt.show()

# Afișare panta (miu)
print("Panta (miu):", miu)
