import math
import numpy as np
import matplotlib.pyplot as plt
def calculate_result(input_array):
    omegape4pi = []
    for value in input_array:
        result = 0.5 - (1 / math.sqrt(4 + (2 / value) ** 2))
        omegape4pi.append(result)
    return omegape4pi

x = [1.2, 4.6, 8, 11.3]
omega_pe_4pi = calculate_result(x)
print("valori in cm", x)
print("omega/ 4pi", omega_pe_4pi)
print("\n")

x_data = np.array([0.11588936, 0.011411818, 0.003861062, 0.001946442])
y_data = np.array([382.575, 59.91666667, 27.23888889, 15.87916667])

m, c = np.polyfit(x_data, y_data, 1)

slope = m
intercept = c

# Generarea punctelor pentru linia de regresie
x_fit = np.linspace(min(x_data), max(x_data), 100)
y_fit = slope * x_fit + intercept

plt.scatter(x_data, y_data, label=' ')
plt.plot(x_fit, y_fit, color='red')
plt.xlabel('$\\frac{\\Omega}{4\\pi}$')
plt.ylabel('n (impulsuri/ s)')
plt.legend()
plt.title('Regresie Liniară')
plt.show()

# Afișarea pantei
print("Panta (impulsuri/ s):", slope)
e = 0.2
S = 2
Lambda = slope / (e * S)

# Afisare lambda
print("Valoarea activitatii absolute (impulsuri/ s): ", Lambda)
