import glob
from pprint import pprint as pp
import matplotlib.pyplot as plt
import numpy as np

networks = {}

for file in glob.glob('randomWalkDat/*.dat'):
    with open(file) as data:
        generation = data.readline()[:-1]
        u,v = data.readline().split()
        uniqueNetworkId = data.readline()[:-1]
        hub = data.readline().split()[2]
        networks.setdefault(uniqueNetworkId,{})
        networks[uniqueNetworkId].setdefault(hub,{})
        for line in data.readlines():
            degree, time = line.split()
            networks[uniqueNetworkId][hub].setdefault(int(degree),[]).append(float(time))

plt.style.use('bmh')
for net in networks.values():
    for hub in net.keys():
        for degree, values in net[hub].items():
            plt.plot([degree for i in values], values, '.')
        plt.xlabel("Degree of node")
        plt.ylabel("Time to hub")
        plt.title("Random walk from each node to hub {} of {}".format(int(hub) + 1, len(net)))
        plt.plot(list(net[hub].keys()), [np.average(values) for values in net[hub].values()])
        plt.show()
        break
