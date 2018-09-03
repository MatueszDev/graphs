import glob
from pprint import pprint as pp
import matplotlib.pyplot as plt
import numpy as np
from collections import OrderedDict

networks = {}

for file in glob.glob('randomWalkDat/*.dat'):
    with open(file) as data:
        generation = data.readline()[:-1]
        u,v = data.readline().split()
        uniqueNetworkId = data.readline()[:-1]
        probability = data.readline()[:-1]
        hub = data.readline().split()[2]
        networks.setdefault(uniqueNetworkId,{})
        networks[uniqueNetworkId].setdefault(hub,{})
        for line in data.readlines():
            degree, time = line.split()
            networks[uniqueNetworkId][hub].setdefault(int(degree),[]).append(float(time))

plt.style.use('bmh')
for net in networks.values():
    for hub in net.keys():
        ordered = OrderedDict(sorted(net[hub].items()))
        for degree, values in ordered.items():
            plt.plot([degree for i in values], values, '.')
        plt.xlabel("Degree of node")
        plt.ylabel("Time to hub")
        plt.title("Random walk from each node to hub {} of {} with {} tree".format(int(hub) + 1, len(net), probability))
        plt.plot(list(ordered.keys()), [np.average(values) for values in ordered.values()])
        plt.show()
        plt.clf()
