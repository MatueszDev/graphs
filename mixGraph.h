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
    std::vector<std::list<unsigned>> net;

    unsigned calculateDesiredNumberOfNodes(bool tree);
    void createChain(short length, unsigned& freeSpace,unsigned first, unsigned last);
    void createNotHookedChain(unsigned short length, unsigned& freeSpace,unsigned first);
    void generateUsingTreeMethod();
    void generateUsingFlowerMethod();
    void generateUsingTreeMethodV2(size_t& row, std::list<unsigned>::iterator& neighbour);
    void generateUsingFlowerMethodV2(size_t& row, std::list<unsigned>::iterator& neighbour);
    unsigned startWalking(unsigned, unsigned);
    bool checkInitialCondition(unsigned point, unsigned endCondition);
    std::vector<unsigned> calculateHubs();
    unsigned randomWalk(unsigned startNode, unsigned endNode);

public:
    MixGraph(unsigned short, unsigned short);
	MixGraph(std::string);
    void printNetwork(int) const;
    void nextGeneration();
    void nextGenerationV2();
    std::vector<unsigned> startRandomWalk(unsigned, unsigned, unsigned);
    void generateRandomWalkCasesFile(std::vector<unsigned> data, unsigned point, unsigned endCondition);
    void createHistogramFile() const;
    std::vector<std::vector<unsigned>> calculateTimeFromEachNodToHub();
	void exportNetworkToFile();
};

#endif
