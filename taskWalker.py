import subprocess
import numpy as np
from decimal import Decimal
from time import time


probability = 1
path = "D:\\agh\\semestr6\\pracaInz\\program\\main.exe"
path_to_file="D:\\agh\\semestr6\\pracaInz\\program\\randomWalkDat_t\\g5_u1_v2\\p10\\"
u,v = 1,2
repetition = 50
generation = 5
arguments = [u, v, probability, repetition, generation, path_to_file]
times = []
for i in np.arange(0, 0.6, 0.1):
    args = "-u {} -v {} -p {} -rep {} -g {} -path {} -n".format(*arguments)
    print(path,args)
    command = "{} {}".format(path, args)
    start = time()
    subprocess.call(command)
    end = time()
    times.append(end - start)

print(times)
