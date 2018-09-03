import matplotlib.pyplot as plt

plt.clf()
files = ["datFiles\graphLT22g5.dat"]

for file in files:
    with open(file) as data:
        degree = []
        amount = []
        generation = int(data.readline())
        degrees = [2**i for i in range(1,generation+1,1)] #create k = 2**m where m = 1,2..,n
        
        for point in data.readlines():
            edge = point.split()
            degree.append(int(edge[0]))
            amount.append(int(edge[1]))

        #C = amount[0]/2**(-exponent)
        #teoAmount = [C*i**(-exponent) for i in degrees]
        num = [a  for a in [k for k in file] if a.isdigit()]
        #print(num)
        u = int(num[0])
        v = int(num[1])
        #teoAmount = [(u+v-2)*(u+v)**(generation-i) if i < generation else u+v for i in range(1,generation+1,1)]
        plt.grid(which='both',linestyle='-', linewidth=0.5, alpha = 0.5)
        plt.title(file[9:-4])
        plt.xlabel("Number of neighbours")
        plt.ylabel("occurance")
        #plt.bar(degree, amount)
     
        #plt.loglog(degree, amount,'.r')
        plt.plot(degree,amount,'.r')
        plt.savefig("wyniki/{}.pdf".format(file[8:-4]))
        plt.clf()
