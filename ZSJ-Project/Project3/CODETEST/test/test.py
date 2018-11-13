import os
import time
import sys
import random


SIZE_OF_MAP = [1, 100, 500, 1000, 1500, 2000]

for cases in range(6):
    for i in range(5):
        filename = '../inputs/{}{}.in'.format(cases, i)
        with open(filename, 'w') as TARGET_FILE:
            n = SIZE_OF_MAP[cases]
            TARGET_FILE.write(str(n) + '\n' + str(n) + '\n')
            TARGET_FILE.write('0 0\n')
            TARGET_FILE.write(str(n-1) + ' ' + str(n-1) + '\n')
            for x in range(n):
                for y in range(n):
                    TARGET_FILE.write(str(random.randint(0, 499)) + ' ')
                TARGET_FILE.write('\n')
        print("{}{}".format(cases, i))





