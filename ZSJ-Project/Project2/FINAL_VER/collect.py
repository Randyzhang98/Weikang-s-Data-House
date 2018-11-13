import matplotlib.pyplot as plt 
from scipy.stats import t 
import numpy as np 
import random
import os
import time
import sys

MAX = 6
size = [100000, 200000, 300000, 400000, 500000, 600000]
plt.figure(figsize=(12,7)) 
for types in range(3): 
    for leng in range(6):
        for cases in range(3):
            mean = 0.0
            big = 0.0
            small = 2.0
            i = 0
            infilename = './outs/%r.%d.%s.out'.format(cases) %(types, leng, cases)
            indir = os.path.dirname(infilename)
            if not os.path.exists(indir):
                os.makedirs(indir)
            with open(infilename, 'r') as f:
                for i in range(1000):
                    data = f.readline()
                    num = float(data)
                    if (num > big):
                        big = num
                    if (num < small):
                        small = num
                    mean = (mean*(i) + num) / (i+1)    
                # print("Type%r.Size%s.Case%d") %(types, leng, cases)
                # print(mean)
                #print('big - small')
                print(big -small)
            
                    