import os
import random

M, N = 12471, 3333
tar = M*N

with open('input3.txt', 'w') as f:
    f.write(str(M)+" "+str(N)+'\n')
    for i in range(tar):
        if i%100000 == 0: print("{}%".format(100*i/tar))
        f.write(str(random.randint(-25400,25400))+" ")