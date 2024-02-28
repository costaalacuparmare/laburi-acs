from numpy import sqrt
import numpy as np
import matplotlib.pyplot as plt
d1 = 2.13 * 10 ** (-12)
d2 = 1.23 * 10 ** (-12)
L = 13.5
D1 = [5.1, 4.7, 4.4, 4.1, 3.9]
D2 = [2.9, 2.8, 2.7, 2.4, 2.3]
U = [3000, 3500, 4000, 4500, 5000]
j = 0
for i in D1:
    print((d1 / 2 * L) * i * 10000000000)
print()
for i in D2:
    print((d2 / 2 * L) * i * 10000000000)
print()

e = 1.602 * 10 ** (-19)
m = 9.109 * 10 ** (-31)
h = 6.625 * 10 ** (-34)
for i in U:
    print(h / sqrt(2 * m * e * i) * 10 ** 10.5)

radU = [0.577350269, 0.534522484, 0.5, 0.471404521, 0.447213595]

x_data = np.array(radU)
y_data = np.array(D1)
y_data2 = np.array(D2)

m, c = np.polyfit(x_data, y_data, 1)

slope = m
intercept = c

m, c = np.polyfit(x_data, y_data2, 1)

slope2 = m
intercep2 = c

# Generarea punctelor pentru linia de regresie
x_fit = np.linspace(min(x_data), max(x_data), 100)

y_fit = slope * x_fit + intercept
y_fit2 = slope2 * x_fit + intercep2
plt.scatter(x_data, y_data)
plt.scatter(x_data, y_data2)
plt.plot(x_fit, y_fit, color='blue')
plt.plot(x_fit, y_fit2, color='red')
plt.plot()
plt.xlabel('1 / sqrt(U) (kV la minus 1 pe 2)')
plt.ylabel('Diametru (cm)')
plt.legend()
plt.title('Regresie Liniară')
plt.show()
e = 1.602 * 10 ** (-19)
m = 9.109 * 10 ** (-31)
h = 6.625 * 10 ** (-34)
L = 13.5
print(slope)
print(slope2)
print((2 * h * L) / (slope * 10 * sqrt(10) * sqrt(2 * m * e)))
print((2 * h * L) / (slope2 * 10 * sqrt(10) * sqrt(2 * m * e)))
