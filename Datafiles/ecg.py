import matplotlib.pyplot as plt
import numpy as np

data = np.loadtxt('ecg.txt')
plt.plot(data)
plt.show()