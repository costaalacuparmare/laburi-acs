import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit

def exponential_cubic_regression(x, a, b, c, d):
    return a * np.exp(b * x) + c * x**3 + d * x**2

# Example data (replace with your actual data)
x_data = np.array([0.5, 1, 1.5, 2, 2.5])
y_data = np.array([13938, 8848, 5494, 3455, 2170])

# Perform the regression
params, covariance = curve_fit(exponential_cubic_regression, x_data, y_data)

# Parameters: a, b, c, d
a, b, c, d = params

# Calculate the slope at x=2
x_value = 2
slope = (a * b * np.exp(b * x_value)) + (3 * c * x_value**2) + (2 * d * x_value)
print("Panta pentru plumb:", slope)

# Generate points for the regression curve
x_fit = np.linspace(min(x_data), max(x_data), 100)
y_fit = exponential_cubic_regression(x_fit, a, b, c, d)

# Plot original data and regression curve
plt.scatter(x_data, y_data, label='Impulsuri')
plt.plot(x_fit, y_fit, color='red', label='Functia de regresie')
plt.xlabel('X')
plt.ylabel('Y')
plt.legend()
plt.title('Plumb, Panta pentru Plumb: -3256.6391003127974')
plt.show()

# Print the parameters
print("a =", a)
print("b =", b)
print("c =", c)
print("d =", d)
