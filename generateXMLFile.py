import glob
pot = 0.5


def rgb(minimum, maximum, value):
    minimum, maximum = float(minimum), float(maximum)
    ratio = 2 * (value**pot - minimum**pot)/( maximum**pot -  minimum**pot)
    b = int(max(0, 255*(1 - ratio)))
    r = int(max(0, 255*(ratio - 1)))
    g = 255 - b - r
    return r, g, b

header = """<?xml version="1.0" encoding="UTF-8"?>
<graphml xmlns="http://graphml.graphdrawing.org/xmlns/graphml"
xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"  
xsi:schemaLocation="http://graphml.graphdrawing.org/xmlns/graphml">
<key id="edgeThickness" for="graph"/>
<key id="vertexPickedColor" for="graph"/>
<key id="backgroundColor" for="graph"/>
<key id="labelSize" for="graph"/>
<key id="labelPosition" for="graph"/>
<key id="cluster_0" for="graph"/>
<key id="clustersCount" for="graph"/>
<key id="edgeStyle" for="graph"/>
<key id="labelFillColor" for="graph"/>
<key id="labelPickedColor" for="graph"/>
<key id="vertexRadius" for="graph"/>
<key id="color" for="node">
<default>192;192;192</default>
</key>
<key id="shape" for="node"/>
<key id="clusterY" for="node"/>
<key id="clusterX" for="node"/>
<key id="fillStyle" for="node"/>
<key id="clusterId" for="node"/>
<key id="label" for="node">
<default></default>
</key>
<key id="color" for="edge">
<default>50;50;50</default>
</key>
<key id="weight" for="edge"/>
<key id="label" for="edge"/>
<graph edgedefault="undirected">
<data key="edgeThickness">1.0</data>
<data key="vertexPickedColor">240;230;140</data>
<data key="backgroundColor">230;230;230</data>
<data key="labelSize">14</data>
<data key="labelPosition">AUTO</data>
<data key="cluster_0">Default;220.0;220.0;350;350</data>
<data key="clustersCount">1</data>
<data key="edgeStyle">Line</data>
<data key="labelFillColor">255;255;255</data>
<data key="labelPickedColor">240;230;140</data>
<data key="vertexRadius">15.0</data>
"""

node_template = '''<node id="{}">
<data key="color">{};{};{}</data>
<data key="shape">Circle</data>
<data key="clusterY">{}</data>
<data key="clusterX">{}</data>
<data key="fillStyle">Stroke color</data>
<data key="clusterId">0</data>
<data key="label"></data>
</node>
'''

edge_template = '''<edge source="{}" target="{}">
<data key="color">192;192;192</data>
<data key="weight"></data>
<data key="label"></data>
</edge>
'''

xml_file = header

hubs = {}
edges = []
relative_path = 'regular_3\*.dat'
for file in glob.glob(relative_path):
    if "net" in file:
        with open(file) as file:
            edges = [line.split() for line in file.readlines()[5:]]
    elif "traffic" in file:
        name = file.split('_')
        unique_id = name[2]
        with open(file) as data:
            first = data.readline().split()
            hub = first[0]
            hubs.setdefault(hub, [])
            hubs[hub].append(int(first[2]))
            hubs[hub].extend([int(line.split()[2]) for line in data.readlines()])

net_size = len(hubs["0"])
sum_of_nodes = [0 for i in range(net_size)]
for i in range(net_size):
        for value in hubs.values():
            sum_of_nodes[i] += value[i]

maxim = max(sum_of_nodes)
minim = min(sum_of_nodes)

#sum_of_nodes = list(map(lambda x: x/maxim, sum_of_nodes))

posX = 0
posY = 0
for i in range(net_size):
    if not (i % 10):
        posX = 0
        posY += 25
    r, g ,b = rgb(minim, maxim, sum_of_nodes[i])
    xml_file += node_template.format(i, r, g, b, posY, posX )
    posX += 25

edge_size = len(edges)
for i in range(edge_size):
    xml_file += edge_template.format(*edges[i])
    
xml_file += '''</graph>
</graphml>'''

with open('cos.gv', 'w') as f:
    f.write(xml_file)

          
