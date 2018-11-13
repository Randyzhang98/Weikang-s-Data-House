import random
import os
import time
import sys

INT_MAX = 2**31
SIZE = [100000, 200000, 300000, 400000, 500000, 600000]
for cases in range(6):
    for ranges in range(3):
        filename = './test%r.%d'.format(cases) %(cases, ranges)
        dirname = os.path.dirname(filename)
        if not os.path.exists(dirname):
            os.makedirs(dirname)
        with open(filename, 'w') as w:
            n = SIZE[cases]
            w.write(str(n) + '\n')
            for i in range(n):
                w.write(str(random.randint(-INT_MAX, INT_MAX-1)) + '\n')
        print("Cases%r.Range%d".format(cases)) %(cases, ranges)