import subprocess
import numpy as np
from decimal import Decimal
from time import time

path = "D:\\agh\\semestr6\\pracaInz\\program\\graph.exe"
u,v = 2,2
probability = 0
repetition = 50
arguments = [u, v, probability, repetition]
times = []
for i in np.arange(0.4, 0.9, 0.1):
    arguments[2]= i
    args = "{} {} {:.1f} {}".format(*arguments)
    print(path,args)
    command = "{} {}".format(path, args)
    start = time()
    subprocess.call(command)
    end = time()
    times.append(end - start)

print(times)
with open("time.dat" ,'w') as file:
    for time in times:
        file.write("{}\n".format(time))
