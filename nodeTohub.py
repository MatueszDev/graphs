import glob
import pprint
import matplotlib.pyplot as plt

networks = {}

for file in glob.glob('randomWalkDat/*.dat'):
    with open(file) as data:
        generation = data.readline()[:-1]
        u,v = data.readline().split()
        uniqueNetworkId = data.readline()[:-1]
        hub = data.readline().split()[2]
        networks.setdefault(uniqueNetworkId,{})
        networks[uniqueNetworkId].setdefault(hub,{})
        print(generation,u,v,uniqueNetworkId,hub)
        for line in data.readlines():
            degree, time = line.split()
            networks[uniqueNetworkId][hub].setdefault(degree,[]).append(float(time))
pprint.pprint(networks)
