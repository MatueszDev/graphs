#ifndef MIXGRAPH_H_
#define MIXGRAPH_H_

#include <cmath>
#include <iostream>
#include <vector>
#include <list>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <iterator>
#include <cmath>
#include "random.hpp"
#include "functions.h"
#include <chrono>
#include <thread>
#include <iomanip>

class MixGraph{
private:
    unsigned short u;
    unsigned short v;
    unsigned numberOfEdges;
    unsigned short generation;
	mutable std::vector<std::list<unsigned>> net;
	std::string uniqueNetworkId = "";
    double probability;

    unsigned calculateDesiredNumberOfNodes(bool);
    void createChain(short length, unsigned&, unsigned, unsigned);
    void createNotHookedChain(unsigned short, unsigned&, unsigned);
    void generateUsingTreeMethod();
    void generateUsingFlowerMethod();
    void generateUsingTreeMethodV2(size_t&, std::list<unsigned>::iterator&);
    void generateUsingFlowerMethodV2(size_t&, std::list<unsigned>::iterator&);
    unsigned startWalking(unsigned, unsigned);
    bool checkInitialCondition(unsigned, unsigned);
    unsigned randomWalk(const unsigned&, const unsigned&,
                        std::vector<std::vector<unsigned>>&, const unsigned&);
    std::list<unsigned>::iterator _findNextNeighbour(const unsigned& node);

public:
    MixGraph(unsigned short, unsigned short, double);
	MixGraph(std::string);
    void printNetwork(int) const;
    void nextGeneration();
    void nextGenerationV2();
    std::vector<unsigned> startRandomWalk(unsigned, unsigned, unsigned);
    void generateRandomWalkCasesFile(std::vector<unsigned>, unsigned, unsigned);
    void createHistogramFile(std::string) const;
    std::vector<std::vector<double>> calculateTimeFromEachNodToHub(int,
                                                                   std::vector<std::vector<unsigned>>&,
                                                                   std::vector<std::vector<double>>&
                                                                  );
	void exportNetworkToFile(std::string ="") const;
	void exportRandomWalkResultToDataFile(std::vector<std::vector<double>>&,
                                          std::string =
                                          "D:\\agh\\semestr6\\pracaInz\\program\\randomWalkDat\\") const;
    int countOne();
    void printHubsIndexes();
    template<typename T>
    void generateDataFile(std::vector<std::vector<T>>&,
                             std::string, std::string);
    void generateFileToGraphVis(std::string path);
    std::vector<unsigned> calculateHubs() const;
};

template<typename T>
void MixGraph::generateDataFile(std::vector<std::vector<T>>& data,
	 							   std::string path, std::string prefix)
{
	size_t dataSize = data.size();
	size_t nodes = data[0].size();

	for(size_t hub = 0; hub < dataSize; ++hub )
	{
		std::ostringstream str;
		str << prefix << uniqueNetworkId << "p" << probability << "_" << hub << "_u" << u << "_v" << v <<".dat";
		std::string fileName = str.str();
		std::string filePath = path + fileName;
		std::ofstream file(filePath);
		if (!file.is_open())
		{
			std::cerr << "Can not open the file: " << filePath << "\n";
			return;
		}
		for(size_t nod = 0; nod < nodes ; ++nod)
		{
			file << hub << " "<< nod << " " << data[hub][nod] <<"\n";
		}
		file.close();
	}
}


#endif
