import matplotlib.pyplot as plt
import numpy as np

V = 12.0
Rs = np.linspace(1, 5, 100)

def I(R):
    return V / R

def P(R):
    return V * I(R)

plt.plot(Rs, P(Rs))
plt.xlabel('Resistance (Ohms)')
plt.ylabel('Power (Watts)')
plt.show()