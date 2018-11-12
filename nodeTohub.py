import glob
from pprint import pprint as pp
import matplotlib.pyplot as plt
import numpy as np
from collections import OrderedDict

networks = {}
prob = {}
index = {}
relative_path = 'regular\\*.dat'
for file in glob.glob(relative_path):
   
    if "traffic" in file or "net" in file or "sigma" in file:
        continue
    
    with open(file) as data:
        generation = data.readline()[:-1]
        u,v = data.readline().split()
        uniqueNetworkId = data.readline()[:-1]
        networks.setdefault(uniqueNetworkId,{})
        probability = data.readline()[:-1]
        prob.setdefault(uniqueNetworkId, probability)
        hub = data.readline().split()[2]
        index_id = data.readline().split()[2]
        networks[uniqueNetworkId].setdefault(hub,{})
        #index.setdefault(uniqueNetworkId,{})
        #index[uniqueNetworkId].setdefault(hub, index_id)
        for line in data.readlines():
            degree, time = line.split()
            networks[uniqueNetworkId][hub].setdefault(int(degree),[]).append(float(time))

plt.style.use('bmh')
summury_hub = {}
for name,net in networks.items():
    partial_sum = 0
    for hub in net.keys():
        ordered = OrderedDict(sorted(net[hub].items()))
        partial_sum += sum(ordered[next(reversed(ordered))])
        for degree, values in ordered.items():
            plt.plot([degree for i in values], values, '.')
        plt.xlabel("Degree of node")
        plt.ylabel("Time to hub")
        #plt.title("Random walk from each node to hub {} of {} with {} tree \n index {}".format(int(hub) + 1, len(net), prob[name], index[name][hub]))
        plt.title("Random walk from each node to hub {} of {} with {} tree".format(int(hub) + 1, len(net), prob[name]))
        plt.plot(list(ordered.keys()), [np.average(values) for values in ordered.values()])
        plt.savefig("regular/toPack/net22_g5_{}_p{}_{}.pdf".format(name,prob[name],int(hub) + 1 ))
        #plt.show()
        plt.clf()
    #summury_hub[prob[name]] = partial_sum
'''summury_hub = OrderedDict(sorted(summury_hub.items()))
plt.bar(range(len(summury_hub)), list(summury_hub.values()), align='center')
plt.xticks(range(len(summury_hub)), list(summury_hub.keys()))
plt.xlabel("Probability")
plt.ylabel("Sum of traffic on hubs")'''
plt.savefig("toPack/sumOfHubsG5.pdf")
