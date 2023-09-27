import matplotlib.pyplot as plt
import numpy as np

fig = plt.figure()
x = [1, 2, 5, 10, 20, 32, 40]
#y1 = [7267455, 4646146.2, 4928477, 5702397.2, 8259858.8, 11193997, 13324975.6]
y2 = [15394860, 5407519.2, 4453344.2, 3693486.4, 3502544, 3602207.2, 3768943.4]
y3 = [39955329.8, 21274143.6, 14044687, 8124658.8, 6077817.2, 4932269.6, 4665925]
y4 = [44289430.6, 24612854.2, 18730572.6, 17529318.4, 16980918.2, 17291915.2, 17043628.8]
#plt.plot(x, y1, label = "100k")
plt.plot(x, y2, label = "1m")
plt.plot(x, y3, label = "10m")
plt.plot(x, y4, label = "100m")
plt.xlabel("Threads")
plt.ylabel("μs")
plt.title("Threads vs computation time")
plt.legend()
plt.show()
