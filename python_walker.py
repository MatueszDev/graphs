import subprocess
import numpy as np
from decimal import Decimal
from time import time,sleep
import glob as g



path_to_file="*.py"


for file in g.glob(path_to_file.format(i)):
    if 'walker' not in file:
        print("python {}".format(file))
        subprocess.call("python {}".format(file))
