import numpy as np

x_data = np.array([1, 2, 3, 4, 5])
y_data = np.array([18.885, 34.93333333, 53.11666667, 71.64333333, 88.26166667])

m, c = np.polyfit(x_data, y_data, 1)

slope = m

evolts_energy = slope
joule_energy = 2.811179e-18
energy_3s = 2.742286e-18
energy_3p = 2.815505e-18
print("Energy in joules: ")
print(joule_energy)
print("Energy in evolts: ")
print(evolts_energy)
print("Energy in joules for 2s to 3s: ")
print(energy_3s)
print("Energy in joules for 2s to 3p: ")
print(energy_3p)
h = 6.6 * 10**(-34)
ct = 3 * 10**8
lamda = h * ct  / (energy_3p - energy_3s)
lamda2 = h * ct / energy_3s
print("Lungime unda (m): ")
print(lamda)
print("Lungime unda 2 (m): ")
print(lamda2)

