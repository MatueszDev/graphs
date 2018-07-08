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
    std::cout << "generation: " << generation << "\n";
    for(size_t i = 0; i < rows; i++)
    {
        for(size_t j = 0; j < i; j++)
        {
            if(net[i][j])
            {
                std::cout << "edge: " << i << " " << j <<"\n";
                if(u > 1)
                {
                    net[i][j] = 0;
                    net[shift][i] = 1;
                    for(size_t k = 2; k < u; k++ )
                    {
                        net[shift + 1][shift] = 1;
                        ++shift;
                    }
                    net[shift][j] = 1;
                }

                net[++shift][i] = 1;
                for(size_t k = 1; k < v/2; ++k)
                {
                    net[shift + 1][shift] = 1;
                    ++shift;
                }
                net[++shift][j] = 1;
                for(size_t k = 1; k < v/2; ++k)
                {
                    net[shift + 1][shift] = 1;
                    ++shift;
                }
                ++shift;
            }
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
{
    std::vector<unsigned> values;
    unsigned max = 0;
    unsigned sum;

    for(auto& row:net)
    {
        for(auto& col:row)
            sum += col;
        if(sum > max)
            max = sum;
        values.push_back(sum);
        sum=0;
    }

    unsigned* counterTable = new unsigned[max + 1]{0};
    for(auto& el:values)
    {
        counterTable[el]++;
    }

    std::stringstream ss ;
    ss << "datFiles/graphMT" <<  u << v << "g"<<generation << ".dat";
    std::string fileName = ss.str();

    std::ofstream file;
    file.open(fileName);
    file << generation << "\n";
    file << calculateTeoreticalExponent() << "\n";
    for(size_t t = 0; t < max + 1; t++)
    {
        if(counterTable[t])
            file << t <<" "<< counterTable[t] << "\n";
    }
    file.close();

    delete [] counterTable;
}


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
    if(version == 1)
    {
        size_t rows = net.size();
        for(size_t i = 0; i < rows; i++)
        {
            for(size_t j = 0; j < rows; j++)
            {
                if(net[i][j])
                    std::cout << i <<" "<< j << "\n";

            }
        }
    }
    if(version == 3)
    {
        size_t rows = net.size();
        for(size_t i = 0; i < rows; i++)
        {
            for(size_t j = 0; j < i; j++)
            {
                if(net[i][j])
                    std::cout << i <<" "<< j << "\n";

            }
        }
    }
}

unsigned GraphMT::calcualteNumberOfNodes(unsigned gener)  const
{
    return std::pow(u+v, gener) + 1;
}

void GraphMT::makeSymmetry()
{
  size_t rows = net.size();

  for(size_t i = 0; i < rows; i++)
      for(size_t j = 0; j < i; j++)
          net[j][i] = net[i][j];
}
