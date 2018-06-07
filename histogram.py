import matplotlib.pyplot as plt


files = ["datFiles/graphL12g10.dat"]

for file in files:
    with open(file) as data:
        degree = []
        amount = []
        generation = int(data.readline())
        exponent = float(data.readline())
        degrees = [2**i for i in range(1,generation+1,1)] #create k = 2**m where m = 1,2..,n
        
        for point in data.readlines():
            edge = point.split()
            degree.append(int(edge[0]))
            amount.append(int(edge[1]))

        #C = amount[0]/2**(-exponent)
        #teoAmount = [C*i**(-exponent) for i in degrees]
        u = int(file[15])
        v = int(file[16])
        teoAmount = [(u+v-2)*(u+v)**(generation-i) if i < generation else u+v for i in range(1,generation+1,1)]
        plt.grid(which='both',linestyle='-', linewidth=0.5, alpha = 0.5)
        plt.title(file[9:-4])
        plt.xlabel("Number of neighbours")
        plt.ylabel("occurance")
        plt.bar(degree, amount)
        plt.plot(degrees, teoAmount,'.r')
        #plt.plot(degree,amount,'.r')
        plt.savefig("wyniki/{}.pdf".format(file[8:-4]))
