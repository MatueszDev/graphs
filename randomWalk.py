import matplotlib.pyplot as plt

plt.clf()
files = ["datFiles/walkCases34_10000_s461_d16.dat"]

for file in files:
    with open(file) as data:
        dat = {}
        generation = int(data.readline())
        
        for value in data.readlines():
            dat.setdefault(int(value), []).append(1)

       
        plt.grid(which='both',linestyle='-', linewidth=0.5, alpha = 0.5)
        plt.title(file[9:-4])
        plt.ylabel("Number of occurance")
        plt.xlabel("Time to picked desired node")
        #plt.bar(degree, amount)
        values = map(lambda x:sum(x), dat.values())
        keys = list(dat.keys())
        values = list(values)
        plt.plot(keys, values,'.r')
        plt.show()
        plt.savefig("wyniki/{}.pdf".format(file[8:-4]))
        plt.clf()
