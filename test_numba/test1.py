import time
from numba import jit

def criba_eratostenes():
    l =  [1] * 10000 
    for i in range(2,10000):
        for j in range(2,10000):
            if i*j < 10000:
                l[i*j] = 0
    l2 = [i for i in range(1,1000) if l[i] == 1]
    return l2

@jit(nopython=True)
def criba_eratostenes_compilada():
    l =  [1] * 10000
    for i in range(2,10000):
        for j in range(2,10000):
            if i*j < 10000:
                l[i*j] = 0
    l2 = [i for i in range(1,1000) if l[i] == 1]
    return l2

t1 = time.process_time()
criba_eratostenes()
t2 = time.process_time()
res = t2 - t1
print("")
print(res)
print("")

t1 = time.process_time()
criba_eratostenes_compilada()
t2 = time.process_time()
res2 = t2 - t1
print(res2)
print("")
print(res/res2)
