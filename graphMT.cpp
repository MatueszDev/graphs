#include "graphMT"

GraphMT::GraphMT(short u, short v):Graph(u,v)
{
    net = {{0, 1},{1,0}};
}


void GraphMT::nextGeneration()
{
    size_t rows = net.size();

    ++generation;
    unsigned nodes = calcualteNumberOfNodes(generation);

    unsigned shift = rows;
    net.resize(nodes);


    for(std::vector<unsigned>& row:net)
    {
        row.resize(nodes);
    }

    for(size_t i = 0; i < rows; i++)
    {
        unsigned neighbours = sumRow(i);
        for(size_t j = 0; j < neighbours; j++)
        {
            net[shift][i] = 1;
            shift++;
        }
    }

}

unsigned GraphMT::sumRow(unsigned row) const
{
    unsigned sum = 0;
    for(auto& el:net[row])
        sum += el;
    return sum;
}


unsigned GraphMT::sumAllEdges() const
{return 0;}
void  GraphMT::createHistogramFile() const
{}


void GraphMT::printNetwork(int version) const
{
    if(version == 2)
    {
        size_t rows = net.size();
        for(size_t i = 0; i < rows; i++)
        {
            std::cout << i << " : ";
            for(size_t j = 0; j < rows; j++)
            {
                if(net[i][j])
                    std::cout << j << " ";

            }
            std::cout << "\n";
        }
    }
}

void GraphMT::makeSymmetry()
{
  size_t rows = net.size();

  for(size_t i = 0; i < rows; i++)
      for(size_t j = 0; j < i; j++)
          net[j][i] = net[i][j];
}
