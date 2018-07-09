#include "graphL"


GraphL::GraphL(unsigned short u,unsigned short v): Graph(u,v)
{
    net.resize(2);
    net[0] = {1};
    net[1] = {0};
}


void GraphL::nextGeneration()
{
    size_t rows = net.size();
    ++(this->generation);
    unsigned nodes = calcualteNumberOfNodes(this->generation);

    unsigned shift = rows; // index of first free node

    net.resize(nodes);
    for(size_t i = 0; i < rows; i++)
    {
        for(auto neighbour = net[i].begin(); neighbour != net[i].end(); neighbour++ )
        {
                if(*neighbour > i && *neighbour < rows)
                {

                    createChain(v,shift,i,*neighbour);


                    if(u>1)
                    {
                        createChain(u,shift,i,*neighbour);

                        net[*neighbour].remove(i);
                        net[i].remove(*neighbour);
                        neighbour--;



                    }
                }
        }
    }

}

void GraphL::printNetwork(int version) const
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

bool GraphL::checkIfNeighbourExists(const std::list<unsigned>& list, const unsigned& neighbour) const
{
    bool flag = false;
    for(auto it = list.begin(); it != list.end(); ++it)
    {
        if(*it == neighbour)
        {
            flag = true;
            return flag;
        }
    }
    return flag;
}


unsigned GraphL::sumAllEdges() const
{
    unsigned edges = 0;
    for(auto& row:net)
    {
        edges += row.size();
    }
    return edges;
}

void GraphL::createHistogramFile() const
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
    ss << "datFiles/graphL" <<  u << v << "g"<<generation << ".dat";
    std::string fileName = ss.str();

    std::ofstream file;
    file.open(fileName);
    file << generation << "\n";
    file << calculateTeoreticalExponent() << "\n";
    for(size_t t = 0; t < maxDegree + 1; t++)
    {
        if(counterTable[t])
            file << t <<" "<< counterTable[t] << "\n";
    }
    file.close();

    delete [] counterTable;
}

void GraphL::createChain(short length, unsigned& freeSpace, unsigned first, unsigned last)
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
