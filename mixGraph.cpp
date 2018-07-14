#include "mixGraph"



MixGraph::MixGraph(unsigned short u, unsigned short v): u{u}, v{v}, numberOfEdges{1}, generation{0}{
    if(u > v){
        throw -5;
    }
    net.resize(2);
    net[0] = {1};
    net[1] = {0};
}

void MixGraph::nextGeneration(){
    generation++;
    using Random = effolkronium::random_static;
    auto chocie = Random::get<bool>();
    if(chocie){
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
                        int temp = *neighbour;
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

                        int temp = *neighbour;
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
