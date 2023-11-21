import matplotlib.pyplot as plt
import numpy as np

# Datele de lungime de undă și pozițiile măsurate
lungimi_unda = [612.7, 607.3, 579, 585.9, 546.1, 496, 491.6, 435.8, 407.8, 404.7]
divizuni = [296.37, 296.81, 297.24, 297.29, 297.62, 298.39, 298.5, 299.77, 301.87, 301.92]
divizuni2 = [296.53, 297.92, 298.59, 298.88, 298.96]
plt.figure(figsize=(8, 6))
plt.scatter(divizuni, lungimi_unda, color='red', label='Puncte măsurate')
np.polyfit(divizuni, lungimi_unda, 2)

div_fit = np.linspace(min(divizuni), max(divizuni), 100)
div_fit_2 = np.linspace(min(divizuni2), max(divizuni2), 100)
lungimi_unda_fit = np.polyval(np.polyfit(divizuni, lungimi_unda, 2), div_fit)
plt.plot(div_fit, lungimi_unda_fit, label='Curba de etalonare')
lungimi_unda_fit_2 = np.polyval(np.polyfit(divizuni, lungimi_unda, 2), divizuni2)
plt.scatter(divizuni2, lungimi_unda_fit_2, label='Puncte lampa UV')
for lun in lungimi_unda_fit_2:
    print(lun)
plt.xlabel('Poziții măsurate')
plt.ylabel('Lungimi de undă')
plt.title('Curba de etalonare a spectroscopului')
plt.legend()
plt.grid(True)
plt.show()