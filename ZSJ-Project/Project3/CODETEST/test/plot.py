#!/usr/bin/env python
# coding: utf-8

# In[1]:


import matplotlib.pyplot as plt
from scipy.stats import t
import numpy as np


# In[3]:


TEST_SIZE = 6
PER_SIZE = 5
INT_MAX = 100;
size = [1, 100, 500, 1000, 1500, 2000]
im = ['u', 'b', 'f']
plt.figure(figsize=(12,7))

for flag in range(3):
    y=np.array([])
    conf_interval=np.array([])
    for cases in range(TEST_SIZE):
        time=np.array([])
        # get time array per size per implementation
        for i in range(PER_SIZE):
            with open('../outputs/' + im[flag] + '{}{}.out'.format(cases, i), 'r') as f:
                data=f.read();
                data = data.split('\n')
                time = np.append(time, float(data[0]))
                
        y = np.append(y, np.mean(time))  # one point on one line
        conf_interval = np.append(conf_interval, np.std(y))
    plt.errorbar(size, y, yerr = conf_interval, fmt = '-o')

plt.legend(['Unsorted_Heap', 'Binary_Heap', 'Fibonacci_Heap'], loc = 'upper left')
plt.xlabel('The edge length of Square Map')
plt.ylabel('Runtime (s)')
plt.title('Priority Queues Implentation')
plt.savefig('res.png')
plt.show()


# In[ ]:




