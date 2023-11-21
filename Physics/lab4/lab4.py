import numpy as np
import matplotlib.pyplot as plt
import math as mth

# Date de exemplu (înlocuiți cu datele reale)
y_data = np.array([1.5974, 1.6424, 1.6884, 1.6482, 2.1286])
x_data = np.array([5.19, 5.494, 6.883, 7.412, 8.196])

# Realizarea regresiei liniare
# x și y sunt datele de intrare, iar m și c sunt parametrii regresiei (panta și intersectarea pe axa y)
m, c = np.polyfit(x_data, y_data, 1)

# Calcularea pantei și intersectării pe axa y
slope = m
intercept = c

# Generarea punctelor pentru linia de regresie
x_fit = np.linspace(min(x_data), max(x_data), 100)
y_fit = slope * x_fit + intercept
slope = slope * mth.pow(10,-14)
# Punctele pentru prelungirea liniei de regresie până la axa OY
x_intercept = -intercept / slope
y_intercept = 0

# Plotare datele originale și linia de regresie
plt.scatter(x_data, y_data)
plt.plot(x_fit, y_fit, color='red', label=f'Linie de Regresie (panta={slope:.2f})')
plt.xlabel('x = niu(10^14 Hz)')
plt.ylabel('y = U(V)')
plt.legend()
plt.title('Regresie Liniară')
plt.show()

# Afișarea pantei
print("Panta (V/Hz):", slope)
e = 1.6 * mth.pow(10,-19)
h = slope * e
print("h: (J*s)", h)
print("frecv de prag (Hz): ", x_intercept)
print("lucru mecanic de extractie (J): ", x_intercept * h)
