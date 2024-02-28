import numpy as np
import math
import matplotlib.pyplot as plt

r = [0.05, 0.04, 0.03]
I3 = np.array([0.686, 0.927, 1.802, 2.107, 2.208, 2.350])
I4 = np.array([0.160, 0.202, 1.363, 1.555, 1.635, 1.764])
I5 = np.array([0.003, 0.003, 1.148, 1.261, 1.324, 1.404])
R = 0.2
U = np.array([100, 120, 140, 160, 180, 200])
n = 154
u = 4 * math.pi * 1e-7

epem5 = (125/32.0) * ((R**2) / ( u*2 * n*2)) * (U / ((r[0]*2) * (I5 * 2)))
epem4 = (125/32.0) * ((R*2) / ( u*2 * n*2)) * (U / ((r[1]*2) * (I4 * 2)))
epem3 = (125/32.0) * ((R*2) / ( u*2 * n*2)) * (U / ((r[2]*2) * (I3 * 2)))


# -------- r = 5cm
y5 = I5 ** 2
plt.scatter(U / (r[0] ** 2), y5)

coeffs5 = np.polyfit(U / (r[0] ** 2), y5, 1)

x5 = np.linspace(min(U / (r[0] * 2)), max(U / (r[0] * 2)), 100)
y5 = coeffs5[0] * x5 + coeffs5[1]

plt.plot(x5, y5, label='r = 5cm')

# -------- r = 4cm
y4 = I4 ** 2
plt.scatter(U / (r[1] ** 2), y4)

coeffs4 = np.polyfit(U / (r[1] ** 2), y4, 1)

x4 = np.linspace(min(U / (r[1] ** 2)), max(U / (r[1] ** 2)), 100)
y4 = coeffs4[0] * x4 + coeffs4[1]

plt.plot(x4, y4, label='r = 4cm')

# -------- r = 3cm
y3 = I3 ** 2
plt.scatter(U / (r[2] ** 2), y3)

coeffs3 = np.polyfit(U / (r[2] ** 2), y3, 1)

x3 = np.linspace(min(U / (r[2] * 2)), max(U / (r[2] * 2)), 100)
y3 = coeffs3[0] * x3 + coeffs3[1]

plt.plot(x3, y3, label='r = 3cm')


em5 = (125/32) * ((R**2) / (u * 2 * n*2)) * (1/coeffs5[0])
em4 = (125/32) * ((R**2) / (u * 2 * n*2)) * (1/coeffs4[0])
em3 = (125/32) * ((R**2) / (u * 2 * n*2)) * (1/coeffs3[0])

m = 9.109 * 1e-31


plt.xlabel("U/r^2   (V / m^2)")
plt.ylabel("I^2    (A^2)")

print('Sarcinile specifice obtinute:')
print(str(em5) + ' C/Kg')
print(str(em4) + ' C/Kg')
print(str(em3) + ' C/Kg')

plt.legend()

plt.show()