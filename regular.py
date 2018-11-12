from numpy.random import choice

net = {}
num_of_nodes = 100
neighbours = 10
i = 0

def checkOccurance(value):
    counter = 0
    for values in net.values():
        if value in values:
            counter += 1
    return False if counter >= neighbours else True




while i < num_of_nodes:
    net.setdefault(i, [])
    choices = [d for d in range(num_of_nodes)]

    while len(net[i]) != neighbours:
        try:
            random_value = choice(choices)
        except Exception:
            net = {}
            i = 0
            net[i] = []
            choices = [d for d in range(num_of_nodes)]
            continue

        if random_value not in net[i] and random_value != i and checkOccurance(random_value):
            if not net.get(random_value, None):
                net[i].append(random_value)
                net.setdefault(random_value, []).append(i)
            elif len(net[random_value]) < neighbours:
                net[i].append(random_value)
                net[random_value].append(i)

        del choices[choices.index(random_value)]


    i += 1

net = sorted(net.items(), key=lambda kv: kv[0])

with open('dane.dat', 'w') as file:
    for index, values in net:
        for el in values:
            file.write("{} {}\n".format(index, el))
