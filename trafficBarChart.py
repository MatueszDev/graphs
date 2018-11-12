import glob
from pprint import pprint as pp
import matplotlib.pyplot as plt
import numpy as np
from collections import OrderedDict

networks = {}
relative_path = 'regular_3\*.dat'

for file in glob.glob(relative_path):
    if "traffic" in file:
        name = file.split('_')
        unique_id = name[1]
        networks.setdefault(unique_id, {})
        with open(file) as data:
            first = data.readline().split()
            hub = first[0]
            networks[unique_id].setdefault(hub, [])
            networks[unique_id][hub].append(float(first[2]))
            networks[unique_id][hub] = [int(line.split()[2]) for line in data.readlines()]

plt.style.use('bmh')
for name, hubs in networks.items():
    indexes = [i for i in range(len(hubs["0"]))]
    sum_of_nodes = [0 for i in range(len(hubs["0"]))]
    for i in range(len(hubs["0"])):
        for value in hubs.values():
            sum_of_nodes[i] += value[i]
    plt.plot(indexes, sum_of_nodes, '.')
    plt.xlabel("Number of node")
    plt.ylabel("Traffic")
    plt.title("Probability {}".format(name[-3:]))
    #plt.savefig("randomWalkDat/g5_03/numerical/net22_g5_{}.pdf".format(name[:-3]))
    plt.show()
    plt.clf()

