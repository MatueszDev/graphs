#include "mixGraph"

using Random = effolkronium::random_static;

MixGraph::MixGraph(unsigned short u, unsigned short v): u{u}, v{v}, numberOfEdges{1}, generation{0}{
    if(u > v)
    {
        throw -5;
    }
    net.resize(2);
    net[0] = {1};
    net[1] = {0};
}

void MixGraph::nextGeneration(){
    generation++;
    auto chocie = Random::get<bool>();
    if(chocie)
    {
        generateUsingTreeMethod();
    }
    else
        generateUsingFlowerMethod();
}

void MixGraph::generateUsingTreeMethod(){
    unsigned numberOfnewNodes = calculateDesiredNumberOfNodes(true);
    size_t rows = net.size();
    unsigned shift = rows;
    net.resize(rows + numberOfnewNodes);

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
    unsigned numberOfnewNodes = calculateDesiredNumberOfNodes(false);
    size_t rows = net.size();
    unsigned shift = rows;
    net.resize(rows + numberOfnewNodes);

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
        unsigned numberOfnewNodes = (2*(v/2) + u - 1) * numberOfEdges;
        numberOfEdges *= (2*(v/2) + u);
        return numberOfnewNodes;
    }
    else{
        unsigned numberOfnewNodes = (v-1 + u-1) * numberOfEdges;
        numberOfEdges *= (u + v);
        return numberOfnewNodes;
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
    ss << "datFiles/walkCases"<< u << v << "_" << data.size()<< "_s"<<point <<"_d"<<endCondition << ".dat";
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
                    bool caseTree = Random::get<bool>();
                    if(caseTree)
                    {
                        generateUsingTreeMethodV2(i, neighbour);
                    }
                    else{
                        generateUsingFlowerMethodV2(i, neighbour);
                    }

                }
                
                    neighbour++;
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
