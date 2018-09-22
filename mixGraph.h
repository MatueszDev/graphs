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
#include "random.hpp"
#include "functions.h"

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
    std::vector<unsigned> calculateHubs() const;
    unsigned randomWalk(unsigned, unsigned) const;

public:
    MixGraph(unsigned short, unsigned short, double);
	MixGraph(std::string);
    void printNetwork(int) const;
    void nextGeneration();
    void nextGenerationV2();
    std::vector<unsigned> startRandomWalk(unsigned, unsigned, unsigned);
    void generateRandomWalkCasesFile(std::vector<unsigned>, unsigned, unsigned);
    void createHistogramFile() const;
    std::vector<std::vector<double>> calculateTimeFromEachNodToHub(int);
	void exportNetworkToFile() const;
	void exportRandomWalkResultToDataFile(std::vector<std::vector<double>>&) const;
    int countOne();
    void printHubsIndexes();
};

#endif
