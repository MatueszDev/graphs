#include "mixGraph.h"

using Random = effolkronium::random_static;
const char letters[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'o', 'p', 'r' };

void generateRandomString(std::string& str, int length)
{
	for (int len = 0; len < length; ++len)
		str.push_back(*Random::get(letters));
}


MixGraph::MixGraph(unsigned short u, unsigned short v, double probability=0.5):
 				   u{u}, v{v}, numberOfEdges{1}, generation{0}, probability{probability}
{
    if(u > v)
    {
        throw -5;
    }
    net.resize(2);
    net[0] = {1};
    net[1] = {0};

	generateRandomString(uniqueNetworkId, 4);
}

MixGraph::MixGraph(std::string file): numberOfEdges{0}
{

	std::ifstream networkFile;
	networkFile.open(file);

	if (!networkFile.is_open())
	{
		std::cerr << "Can not open " << file << "\n";
		return;
	}
	size_t netSize;
	networkFile >> generation;
	networkFile >> u >> v;
	networkFile >> uniqueNetworkId;
	networkFile >> probability;
	networkFile >> netSize;
	net.resize(netSize);
	unsigned node, neighbour;

	while(networkFile >> node >> neighbour)
	{
		net[node].push_back(neighbour);
		numberOfEdges += 1;
	}
	numberOfEdges >>= 1;
}

void MixGraph::nextGeneration(){
    generation++;
    auto choice = Random::get<bool>(probability);
    if(choice)
    {
        generateUsingTreeMethod();
    }
    else
        generateUsingFlowerMethod();
}

void MixGraph::generateUsingTreeMethod(){
    unsigned numberOfNewNodes = calculateDesiredNumberOfNodes(true);
    size_t rows = net.size();
    unsigned shift = rows;
    net.resize(rows + numberOfNewNodes);

    for(size_t i = 0; i < rows; i++)
    {
        auto neighbour = net[i].begin();
        while(neighbour != net[i].end())
        {
                if(*neighbour > i && *neighbour < rows)
                {

                    createNotHookedChain(v/2, shift, i);
                    createNotHookedChain(v/2, shift, *neighbour);


                    if(u>1)
                    {
                        createChain(u,shift,i,*neighbour);
                        unsigned temp = *neighbour;
                        neighbour++;
                        net[temp].remove(i);
                        net[i].remove(temp);
                        continue;
                    }

                }
                    neighbour++;
        }
    }
}

void MixGraph::generateUsingFlowerMethod(){
    unsigned numberOfNewNodes = calculateDesiredNumberOfNodes(false);
    size_t rows = net.size();
    unsigned shift = rows;
    net.resize(rows + numberOfNewNodes);

    for(size_t i = 0; i < rows; i++)
    {
        auto neighbour = net[i].begin();
        while(neighbour != net[i].end())
        {

                if(*neighbour > i && *neighbour < rows)
                {

                    createChain(v,shift,i,*neighbour);


                    if(u>1)
                    {
                        createChain(u,shift,i,*neighbour);

                        unsigned temp = *neighbour;
                        neighbour++;
                        net[temp].remove(i);
                        net[i].remove(temp);
                        continue;
                    }
                }
                neighbour++;
        }
    }
}

unsigned MixGraph::calculateDesiredNumberOfNodes(bool tree){
    if(tree){
        unsigned numberOfNewNodes = (2*(v/2) + u - 1) * numberOfEdges;
        numberOfEdges *= (2*(v/2) + u);
        return numberOfNewNodes;
    }
    else{
        unsigned numberOfNewNodes = (v-1 + u-1) * numberOfEdges;
        numberOfEdges *= (u + v);
        return numberOfNewNodes;
    }
}

void MixGraph::createChain(short length, unsigned& freeSpace, unsigned first, unsigned last)
{
    net[freeSpace].push_back(first);
    net[first].push_back(freeSpace);
    for(short node = 0; node < length - 2; node++)
    {
        net[freeSpace].push_back(freeSpace + 1);
        net[freeSpace + 1].push_back(freeSpace);
        ++freeSpace;
    }
    net[last].push_back(freeSpace);
    net[freeSpace].push_back(last);
    freeSpace++;
}

void MixGraph::createNotHookedChain(unsigned short length, unsigned& freeSpace, unsigned first)
{
    net[freeSpace].push_back(first);
    net[first].push_back(freeSpace);
    for(size_t t = 1; t < length; t++)
    {
        net[freeSpace].push_back(freeSpace + 1);
        net[freeSpace + 1].push_back(freeSpace);
        ++freeSpace;
    }
    ++freeSpace;
}

void MixGraph::printNetwork(int version) const
{
    if(version == 1)
    {
        for(size_t t = 0; t < net.size(); t++)
        {
            std::cout << t << " : ";
            for(auto neighbour:net[t])
            {
                std::cout << neighbour << " ";
            }
            std::cout << "\n";
        }
    }
    else if(version == 2)
    {
        for(size_t t = 0; t < net.size(); t++)
        {
            for(auto neighbour:net[t])
            {
                std::cout << t <<" "<< neighbour << "\n";
            }
        }
    }
}

std::vector<unsigned>  MixGraph::startRandomWalk(unsigned point, unsigned endCondition, unsigned repetittion)
{

    bool permison = checkInitialCondition(point, endCondition);
    std::vector<unsigned> results;

    if(permison)
    {
        for(unsigned i = 0; i < repetittion; i++)
            results.push_back(startWalking(point, endCondition));
    }
    return results;
}

unsigned MixGraph::startWalking(unsigned point, unsigned endCondition)
{
        unsigned time = 0;
        unsigned numberOfNeighbours = net[point].size();


        while(numberOfNeighbours != endCondition)
        {
            ++time;
            std::list<unsigned>::iterator nextNode = Random::get(net[point].begin(), net[point].end());
            point = *nextNode;
            numberOfNeighbours = net[point].size();
        }
        return time;
}

bool MixGraph::checkInitialCondition(unsigned point, unsigned endCondition)
{
    if(point >= net.size())
    {
        std::cout << "This node does not exists in current net.\n";
        return false;
    }

    unsigned numberOfNeighbours = net[point].size();
    if(numberOfNeighbours == endCondition)
    {
        std::cout << "Picked node has endCondition number of neighbours.\n";
        return false;
    }

    for(auto list:net)
    {
        if(list.size() == endCondition)
        {
            return true;
        }
    }
    std::cout << "This netwok does not contain node with " << endCondition << " neighbours.\n";
    return false;
}

void MixGraph::generateRandomWalkCasesFile(std::vector<unsigned> data, unsigned point, unsigned endCondition)
{
    std::stringstream ss ;
    ss << "D:\\agh\\semestr 6\\pracaInz\\programdatFiles\\walkCases"<< u << v << "_" << data.size()<< "_s"<<point <<"_d"<<endCondition << ".dat";
    std::string fileName = ss.str();

    std::ofstream file;
    file.open(fileName);
    file << generation << "\n";
    for(auto el:data)
    {
        file << el <<"\n";
    }
    file.close();

}

void MixGraph::nextGenerationV2()
{
    generation++;
    size_t rows = net.size();
    for(size_t i = 0; i < rows; ++i)
    {
        auto neighbour = net[i].begin();
        while(neighbour != net[i].end())
        {

                if(*neighbour > i && *neighbour < rows)
                {
                    bool caseTree = Random::get<bool>(probability);
                    if(caseTree)
                    {
                        generateUsingTreeMethodV2(i, neighbour);
                    }
                    else{
                        generateUsingFlowerMethodV2(i, neighbour);
                    }
                    /*
                    double caseTree = Random::get<>(); // various probalility
                    if(caseTree < 0.75)
                    {
                        generateUsingTreeMethodV2(i, neighbour);
                    }
                    else{
                        generateUsingFlowerMethodV2(i, neighbour);
                    }

                    */

                }
                if((u == 1 || *neighbour >= rows) || (*neighbour <= i))
                {
                  neighbour++;
                }
        }

    }
}

void MixGraph::generateUsingTreeMethodV2(size_t& row, std::list<unsigned>::iterator& neighbour)
{
    size_t netSize = net.size();
    size_t newNodes = u - 1 + (v/2)*2;
    net.resize(newNodes + netSize);
    unsigned freeSpace = netSize;

    createNotHookedChain(v/2, freeSpace, row);
    createNotHookedChain(v/2, freeSpace, *neighbour);

    if(u>1)
    {
        createChain(u, freeSpace, row, *neighbour);
        unsigned temp = *neighbour;
        neighbour++;
        net[temp].remove(row);
        net[row].remove(temp);
    }

}

void MixGraph::generateUsingFlowerMethodV2(size_t& row, std::list<unsigned>::iterator& neighbour)
{
    size_t netSize = net.size();
    size_t newNodes = u - 1 + v - 1;
    net.resize(newNodes + netSize);
    unsigned freeSpace = netSize;

    createChain(v, freeSpace, row, *neighbour);


    if(u>1)
    {
        createChain(u, freeSpace, row, *neighbour);

        unsigned temp = *neighbour;
        neighbour++;
        net[temp].remove(row);
        net[row].remove(temp);
    }
}

void MixGraph::createHistogramFile() const
{
    unsigned maxDegree = net[0].size();
    for(auto& row:net)
    {
        if(row.size() > maxDegree)
            {
                maxDegree = row.size();
            }
    }

    unsigned* counterTable = new unsigned[maxDegree + 1]{0};

    //std::map<unsigned,unsigned> counterTable;

    for(auto& row:net)
    {
        counterTable[row.size()]++;
    }

    std::stringstream ss ;
    ss << "D:\\agh\\semestr6\\pracaInz\\program\\datFiles\\graphLT" <<  u << v << "g"<<generation << ".dat";
    std::string fileName = ss.str();

    std::ofstream file;
    file.open(fileName);
	if (!file.is_open())
	{
		std::cerr << "Can not open: " << fileName << " for histogram\n";
		return;
	}
    file << generation << "\n";
    for(size_t t = 0; t < maxDegree + 1; t++)
    {
        if(counterTable[t])
            file << t <<" "<< counterTable[t] << "\n";
    }
    file.close();

    delete [] counterTable;
}

std::vector<std::vector<double>> MixGraph::calculateTimeFromEachNodToHub(int numberOfRepetition)
{
    std::vector<unsigned> hubs = calculateHubs();
    std::vector<std::vector<double>> results (hubs.size());

    size_t hubsSize = hubs.size();
    size_t netSize = net.size();

    for(size_t i = 0; i < hubsSize; i++)
		results[i].resize(netSize, 0);

	for(int repetition = 0; repetition < numberOfRepetition; ++repetition)
	{
		std::cout << "Repetition number: "<< repetition + 1 << ".\n";
		for(size_t j = 0; j < hubsSize; ++j)
			for(size_t i = 0; i < netSize; ++i)
				results[j][i] += randomWalk(i,hubs[j]);
	}

	for (size_t j = 0; j < hubsSize; ++j)
		for (size_t i = 0; i < netSize; ++i)
			results[j][i] /= numberOfRepetition;

    return results;
}

void MixGraph::exportNetworkToFile() const
{
	std::stringstream ss;
	ss << "net" << u << v << "g" << generation << uniqueNetworkId << ".dat";
	std::string fileName = ss.str();

	std::ofstream file;
	file.open(fileName);
	if (!file.is_open())
	{
		std::cerr << "Can not open file: " << fileName << std::endl;
	}
	file << generation << "\n";
	file << u << " " << v << "\n";
	file << uniqueNetworkId << "\n";
	file << probability << "\n";
	file << net.size() << "\n";
	for (size_t t = 0; t < net.size(); t++)
	{
		for (auto neighbour : net[t])
		{
			file << t << " " << neighbour << "\n";
		}
	}

	file.close();
}

unsigned MixGraph::randomWalk(unsigned startNode, unsigned endNode) const
{
    unsigned time = 0;
    unsigned currentNode = startNode;

    while(currentNode != endNode)
    {
        ++time;
        std::list<unsigned>::iterator nextNode = Random::get(net[currentNode].begin(), net[currentNode].end());
        currentNode = *nextNode;
    }
    return time;
}

void MixGraph::exportRandomWalkResultToDataFile(std::vector <std::vector<double>> &data) const
{
	int* nodeDegree = new int[net.size()];
	for (size_t i = 0; i < net.size(); ++i)
	{
		nodeDegree[i] = net[i].size();
	}

	for (size_t i = 0; i < data.size(); i++)
	{
		std::string fileName = "";
		generateRandomString(fileName, 6);
		std::string filePath = "D:\\agh\\semestr6\\pracaInz\\program\\randomWalkDat\\" + fileName + ".dat";

		std::ofstream file(filePath);
		if (!file.is_open())
		{
			std::cerr << "Can not open the file: " << filePath << "\n";
			return;
		}
		file << generation << "\n";
		file << u << " " << v << "\n";
		file << uniqueNetworkId << "\n";
		file << probability << "\n";
		file << "Hub number " << i << "\n";
		for (size_t j = 0; j < net.size(); ++j)
			file << nodeDegree[j] << " " << data[i][j] << "\n";
		file.close();
	}
}

std::vector<unsigned> MixGraph::calculateHubs()
{
    unsigned maxDegree = net[0].size();
    std::vector<unsigned> hubs = {0} ;
    size_t netSize = net.size();

    for(size_t node = 1; node < netSize; ++node)
    {
        unsigned currentDegree = net[node].size();
        if(currentDegree == maxDegree)
            hubs.push_back(node);
        else if ( currentDegree > maxDegree)
        {
            maxDegree = currentDegree;
            hubs.clear();
            hubs.push_back(node);
        }
    }

    return hubs;
}

int MixGraph::countOne()
{
	int counter = 0;
	for(auto& node:net)
	{
		if(node.size() == 1)
			counter++;
	}
	return counter;
}
