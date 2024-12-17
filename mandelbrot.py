import matplotlib.pyplot as plt
import numpy as np

max_iterations = 100

x, y = np.ogrid[-2:1:1000j,-1.5:1.5:1000j]

c = x + y * 1j
z = 0

for i in range(100):
    z = z**2 + c

mb = np.abs(z) < max_iterations

plt.imshow(mb.T, extent=[-2,1,-1.5,1.5])
plt.show()
